import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;
import java.util.TimerTask;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;
import java.io.*;
import java.net.DatagramSocket;
import java.time.*;

public class Sender {
	static final int MAX_DATA_LENGTH = 500;
	static final int SEQ_NUM_MODULO = 32;
	static final int WINDOW_SIZE = 10;

	static boolean isValid(int receivedSeqNum, int currentSeqNum, int nextSeqNum) {
		assert (0 <= receivedSeqNum && receivedSeqNum < SEQ_NUM_MODULO);
		assert (0 <= currentSeqNum && currentSeqNum < SEQ_NUM_MODULO);
		assert (0 <= nextSeqNum && nextSeqNum < SEQ_NUM_MODULO);
		if (nextSeqNum >= WINDOW_SIZE - 1) {
			// no wrapping happens
			if (currentSeqNum <= receivedSeqNum) {
				return true;
			}
		} else {
			// wrapping happens
			nextSeqNum += SEQ_NUM_MODULO;
			if (receivedSeqNum < WINDOW_SIZE) {
				receivedSeqNum += SEQ_NUM_MODULO;
			}
			if (currentSeqNum < WINDOW_SIZE) {
				currentSeqNum += SEQ_NUM_MODULO;
			}
			if (currentSeqNum <= receivedSeqNum) {
				return true;
			}
		}

		return false;
	}

	public static void main(String[] args) {
		String targetAddress = args[0];
		int targetPort = Integer.parseInt(args[1]);
		int localPort = Integer.parseInt(args[2]);
		String fileName = args[3];
		int timeOutDelay = 2000;
		int seqNum = 0;
		boolean isEOF = false;
		Instant startInstant = null;
		Instant endInstant = null;

		// Stores latest WINDOW_SIZE(10) packets that have been previously sent.
		LinkedList<packet> packetWindowBuffer = new LinkedList<packet>();
		try (BufferedReader fileReader = new BufferedReader(new FileReader(fileName));
				BufferedWriter seqnumLogWriter = new BufferedWriter(new FileWriter("seqnum.log"));
				BufferedWriter ackLogWriter = new BufferedWriter(new FileWriter("ack.log"));
				BufferedWriter timeLogWriter = new BufferedWriter(new FileWriter("time.log"));
				DatagramSocket localSocket = new DatagramSocket(localPort);) {
			// If there is a time out, send all packets in the current window.
			ScheduledExecutorService newTimerPool = Executors.newScheduledThreadPool(20);
			Set<ScheduledFuture<?>> scheduledTasks = new HashSet<ScheduledFuture<?>>();
			TimerTask resendAll = new TimerTask() {
				public void run() {

					scheduledTasks.forEach((task) -> task.cancel(true));
					scheduledTasks.add(newTimerPool.schedule(this, timeOutDelay, TimeUnit.MILLISECONDS));
					packetWindowBuffer.forEach((p) -> {
						try {
							p.sendPacketTo(targetAddress, targetPort, localSocket);
							seqnumLogWriter.write(String.valueOf(p.getSeqNum()));
							seqnumLogWriter.newLine();
						} catch (Exception e) {
							e.printStackTrace();
						}
					});
				}
			};
			while (true) {
				// sending packets
				while (!isEOF && packetWindowBuffer.size() < WINDOW_SIZE) {
					// add a packet into the window and send it.
					char[] charArray = new char[MAX_DATA_LENGTH];
					int charsRead = fileReader.read(charArray, 0, charArray.length);
					if (charsRead == -1) {
						isEOF = true;
					} else {
						packetWindowBuffer.add(packet.createPacket(seqNum, new String(charArray, 0, charsRead)));
					}
					if (startInstant == null) {
						startInstant = Instant.now();
					}
					packetWindowBuffer.getLast().sendPacketTo(targetAddress, targetPort, localSocket);
					seqnumLogWriter.write(String.valueOf(packetWindowBuffer.getLast().getSeqNum()));
					seqnumLogWriter.newLine();
					if (scheduledTasks.size() == 0) {
						scheduledTasks.add(newTimerPool.schedule(resendAll, timeOutDelay, TimeUnit.MILLISECONDS));
					}
					seqNum = (seqNum + 1) % SEQ_NUM_MODULO;
				}
				if (isEOF && packetWindowBuffer.isEmpty()) {
					seqNum = (seqNum - 1) % SEQ_NUM_MODULO;
					packet.createEOT(seqNum).sendPacketTo(targetAddress, targetPort, localSocket);
					seqnumLogWriter.write(String.valueOf(seqNum));
                                        seqnumLogWriter.newLine();
				}
				// checking one received packet
				packet receivedPacket = packet.getPacketFrom(localSocket);

				if (receivedPacket.getType() == 0) {
					int receivedSeqNum = receivedPacket.getSeqNum();
					int lastSeqNum = packetWindowBuffer.getLast().getSeqNum();
					ackLogWriter.write(String.valueOf(receivedSeqNum));
					ackLogWriter.newLine();
					if (packetWindowBuffer.removeIf((p) -> isValid(receivedSeqNum, p.getSeqNum(), lastSeqNum))) {

						scheduledTasks.forEach((task) -> task.cancel(true));
						scheduledTasks.clear();
						scheduledTasks.add(newTimerPool.schedule(resendAll, timeOutDelay, TimeUnit.MILLISECONDS));
					}
					// invalid ack received
				} else if (receivedPacket.getType() == 2) {
					endInstant = Instant.now();
					packetWindowBuffer.clear();
					newTimerPool.shutdown();
					break;
				} // otherwise discard the packet, do nothing
			}
			scheduledTasks.forEach((task) -> task.cancel(true));
			scheduledTasks.clear();
			timeLogWriter.write(String.valueOf(Duration.between(startInstant, endInstant).toMillis()));
			timeLogWriter.newLine();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
