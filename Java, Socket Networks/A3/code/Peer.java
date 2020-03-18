import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class Peer {
	final static int CHUNK_SIZE = 512;
	final static double CHUNK_SIZE_DOUBLE = Double.valueOf(CHUNK_SIZE);

	Socket socket;

	static void markTrue(boolean a, boolean b, boolean c) {
		a = true;
		if (a && b && c) {
			System.out.println("PEER 0 SHUTDOWN: HAS 1");
			System.out.println("0    " + new File("./Shared/").listFiles()[0].getName());
			System.exit(0);
		}
		if (a) {
			System.out.println("PEER 0 SHUTDOWN: HAS 1");
			System.out.println("0    " + new File("./Shared/").listFiles()[0].getName());
			System.exit(0);
		}

	}

	public Peer(Socket connection) {
		this.socket = connection;
	}

	public static void main(String args[]) {
		String targetAddress = args[0];
		int targetPort = Integer.parseInt(args[1]);
		int expireTimer = (int) (1000 * Double.parseDouble(args[2]));
		File file = new File("./Shared/").listFiles()[0];
		boolean exitConditionShareDone = false;
		boolean exitConditionAllAcquired = false;
		boolean exitConditionTimer = false;
		ScheduledExecutorService timerPool = Executors.newScheduledThreadPool(1);
		timerPool.schedule(new TimerTask() {
			public void run() {
				markTrue(exitConditionTimer, exitConditionShareDone, exitConditionAllAcquired);
			}
		}, expireTimer, TimeUnit.MILLISECONDS);
		// connection to peer

		try (ServerSocket serverSocket = new ServerSocket(0);
				Socket tracker = new Socket(InetAddress.getByName(targetAddress), targetPort);
				PrintWriter out = new PrintWriter(tracker.getOutputStream(), true);
				BufferedReader in = new BufferedReader(new InputStreamReader(tracker.getInputStream()));) {

			if (tracker.isConnected()) {
				out.println(serverSocket.getInetAddress());
				out.println(serverSocket.getLocalPort());

				out.println(file.getName());
				out.println(file.length());

				out.println((long) Math.ceil(file.length() / CHUNK_SIZE_DOUBLE));

				// wait for tracker response. Tracker will response after there are at least 2
				// peers connected.
				String peerAddress;
				while (true) {
					peerAddress = in.readLine();
					if (peerAddress != null) {
						break;
					}
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				int peerPort = Integer.parseInt(in.readLine());
				String fileName = in.readLine();
				File file2 = new File(File.separator + "Shared" + File.separator + fileName);
				// be ready to receive data and write to file;
				new Thread() {
					public void run() {
						try (Socket s = serverSocket.accept();
								FileOutputStream fOut = new FileOutputStream(file2);
								DataInputStream dataIn = new DataInputStream(s.getInputStream());) {
							byte[] chunk = new byte[512];
							int chunkLen = 0;
							while ((chunkLen = dataIn.read(chunk)) != -1) {
								fOut.write(chunk, 0, chunkLen);
							}
							markTrue(exitConditionAllAcquired, exitConditionShareDone, exitConditionTimer);
						} catch (IOException ioe) {
							ioe.printStackTrace();
						}
					}
				}.start();
				// new Thread() {
				// public void run() {

				// while true here? to handle establishing connection before the other peer is
				// ready
				try (Socket peer = new Socket(InetAddress.getByName(peerAddress), peerPort);
						FileInputStream fromFile = new FileInputStream(file);
						DataOutputStream toSocket = new DataOutputStream(peer.getOutputStream());) {
					byte[] chunk = new byte[512];
					int chunkLen = 0;
					while ((chunkLen = fromFile.read(chunk)) != -1) {
						toSocket.write(chunk, 0, chunkLen);
					}
					markTrue(exitConditionShareDone, exitConditionAllAcquired, exitConditionTimer);
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
				// }
				// }.start();
			}
			/*
			 * while (true) { // listening from the tracker checkList = (CheckList)
			 * inObj.readObject(); if (checkList.isEverythingTrue()) { // download & upload
			 * complete } else { executorService.submit(new Peer(socket)); } }
			 */
		} catch (IOException ioe) {
			System.out.println("try failed");
			ioe.printStackTrace();
			System.exit(1);
		}
	}
}
