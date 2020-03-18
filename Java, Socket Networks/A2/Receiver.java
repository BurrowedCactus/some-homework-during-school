import java.io.*;
import java.net.*;

public class Receiver {
	static String targetAddress;
	static int targetPort;
	static int localPort;

	static void sendPacket(packet thePacket, DatagramSocket localSocket) throws Exception {
		byte[] byteArrayData = thePacket.getUDPdata();
		InetAddress address = InetAddress.getByName(targetAddress);
		localSocket.send(new DatagramPacket(byteArrayData, byteArrayData.length, address, targetPort));
	}

	public static void main(String args[]) {
		targetAddress = args[0];
		targetPort = Integer.parseInt(args[1]);
		localPort = Integer.parseInt(args[2]);
		String fileToBeWritten = args[3];
		int expectedSeqNum = 0;
		try (DatagramSocket receiverSocket = new DatagramSocket(localPort);
				BufferedWriter fileWriter = new BufferedWriter(new FileWriter(fileToBeWritten));
				BufferedWriter arrivalLogWriter = new BufferedWriter(new FileWriter("arrival.log"));) {
			while (true) {
				byte[] buffer = new byte[1024];
				DatagramPacket udpPacket = new DatagramPacket(buffer, buffer.length);
				packet thePacket = null;
				try {
					receiverSocket.receive(udpPacket);
					thePacket = packet.parseUDPdata(udpPacket.getData());
					arrivalLogWriter.write(String.valueOf(thePacket.getSeqNum()));
					arrivalLogWriter.newLine();
				} catch (Exception e) {
					e.printStackTrace();
				}

				if (thePacket.getType() == 1 && thePacket.getSeqNum() == expectedSeqNum) {
					try {
						// save the received packet
						fileWriter.write(thePacket.getData().toString());
						sendPacket(packet.createACK(expectedSeqNum), receiverSocket);
						expectedSeqNum = (expectedSeqNum + 1) % Sender.SEQ_NUM_MODULO;
					} catch (Exception e) {
						e.printStackTrace();
					}
				} else if (thePacket.getType() == 2) {
					// EOT packet received
					try {
						sendPacket(packet.createEOT(expectedSeqNum - 1), receiverSocket);
						break;
					} catch (Exception e) {
						e.printStackTrace();
					}
				} else {
					try {
						// discard the received packet
						sendPacket(packet.createACK(expectedSeqNum - 1), receiverSocket);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
}
