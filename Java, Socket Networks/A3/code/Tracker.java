import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.io.FileWriter;

public class Tracker {
	// return the index of the other peer
	static int otherPeer(int self) {
		if (self == 1) {
			return 0;
		} else {
			return self + 1;
		}
	}

	public static void main(String args[]) {
		// access order : file id -> chunk id -> owner id
		// access order : (which is the file) -> (which part of the file) -> (who has
		// the chunk)
		// ArrayList<ArrayList<ArrayList<Integer>>> table = new
		// ArrayList<ArrayList<ArrayList<Integer>>>();
		ArrayList<String> peerAddresses = new ArrayList<String>();
		ArrayList<Integer> peerPorts = new ArrayList<Integer>();
		ArrayList<String> fileNames = new ArrayList<String>();
		int peerHasOtherFileUpTo[] = new int[8];
		for(int i = 0; i < 8; ++i){
			peerHasOtherFileUpTo[i] = -1;
		}
		int count = 0;
		try (ServerSocket serverSocket = new ServerSocket(0);) {
			try (PrintWriter pw = new PrintWriter(new FileWriter("port.txt"));) {
				pw.println(serverSocket.getLocalPort());
				pw.close();
			}
			while (true) {
				try (Socket socket = serverSocket.accept();
						BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));) {
					int index = count;
					peerAddresses.add(in.readLine());
					peerPorts.add(Integer.parseInt(in.readLine()));
					fileNames.add(in.readLine());
					long fileSize = Long.parseLong(in.readLine());
					long numChunks = Long.parseLong(in.readLine());
					System.out.println("PEER " + index + " CONNECT: OFFERS 1");
					System.out.println(index + "    " + fileNames.get(index) + " " + numChunks);
					peerHasOtherFileUpTo[index] = 0;
					++count;
					synchronized (fileNames) {
						if (fileNames.size() >= 2) {
							fileNames.notify();
						}
					}
/*
					new Thread() {
						public void run() {
							try (PrintWriter out = new PrintWriter(socket.getOutputStream(), true);){
								synchronized (fileNames) {
									while (!(fileNames.size() >= 2)) {
										fileNames.wait();
									}
									System.out.println("print to clients " + index);
									System.out.println(peerAddresses.get(otherPeer(index)));
									System.out.println(peerPorts.get(otherPeer(index)));
									System.out.println(fileNames.get(otherPeer(index)));
									out.println(peerAddresses.get(otherPeer(index)));
									out.println(peerPorts.get(otherPeer(index)));
									out.println(fileNames.get(otherPeer(index)));
								}
							} catch (InterruptedException e) {
								e.printStackTrace();
							} catch (IOException ioe) {
								ioe.printStackTrace();
							}

						}
					}.start();
*/

				}
			}

		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}
}
