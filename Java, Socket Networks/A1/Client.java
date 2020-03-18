import java.net.*;
import java.io.*;
import java.util.*;

public class Client {
	public int tcpPort;
	public int udpPort;
	String address;
	Scanner scan = new Scanner(System.in);

	// UDP socket
	DatagramSocket udp;
	// TCP socket
	Socket socket;

	Client(String s, int i) {
		this(s, i, -1);
	}

	Client(String s, int i, int code) {
		tcpPort = i;
		try {
			udp = new DatagramSocket();
		} catch (SocketException e) {
			e.printStackTrace();
		}
		try {
			// create a socket and attempt to form a TCP connection
			socket = new Socket(InetAddress.getByName(address), tcpPort);

			// TCP connection
			if (socket.isConnected()) {
				BufferedReader is = new BufferedReader(new InputStreamReader(socket.getInputStream()));

				DataOutputStream os = new DataOutputStream(socket.getOutputStream());
				String msg = "";
				if (code == -1) {
					msg = scan.nextLine();
				} else {
					msg = Integer.toString(code);
				}
				OutputStreamWriter osw = new OutputStreamWriter(socket.getOutputStream());
				os.writeBytes(msg + "\n");
				os.flush();
				String response = is.readLine();
				udpPort = Integer.parseInt(response);
				if (response.equals("0")) {
					System.out.println("Invalid req_code.");
					socket.close();
					System.exit(0);
				}
			}
		} catch (IOException ioe) {
			System.exit(1);
		}
	}

	public static void main(String[] args) {
		Client me;
		if (args.length >= 3) {
			me = new Client(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]));
		} else {
			me = new Client(args[0], Integer.parseInt(args[1]));
		}
		// UDP connection, this thread handles the response from the server.
		// Uses Server UDP port + 1 as receiving port.
		new Thread("receiving thread") {
			public void run() {
				try {
					while (true) {
						// create a UDP socket
						// udp = new DatagramSocket(udpPort + 1);
						byte[] buffer = new byte[65536];
						DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
						String msg = "";
						me.udp.receive(packet);
						msg = new String(packet.getData(), packet.getOffset(), packet.getLength());
						System.out.println(msg);
						// This means the client is one-time communication with the server.
						if (msg.equals("NO MSG") && args.length == 4) {
							me.socket.close();
							me.udp.close();	
							break;
						}
					}
				} catch (IOException ioe) {
					System.exit(1);
				}
			}
		}.start();

		// UDP connection, this thread sends user typed info to the server.
		// Uses Server UDP port as sending port.
		try {
			// create a udp socket
			String msg = "GET";
			DatagramPacket packet = new DatagramPacket(msg.getBytes(), msg.getBytes().length,
						InetAddress.getByName(me.address), me.udpPort);
			me.udp.send(packet);
			if (args.length == 4) {
				msg = new String(args[3]);
				packet = new DatagramPacket(msg.getBytes(), msg.getBytes().length,
						InetAddress.getByName(me.address), me.udpPort);
				me.udp.send(packet);			
			} else {
				while (!msg.equals("TERMINATE")) {
					// create a packet for UDP
					msg = me.scan.nextLine();
					packet = new DatagramPacket(msg.getBytes(), msg.getBytes().length,
							InetAddress.getByName(me.address), me.udpPort);
					me.udp.send(packet);
				}
				me.udp.close();
				me.socket.close();
				System.exit(0);
			}
		} catch (Exception e) {
			System.exit(1);
		}
	}

}
