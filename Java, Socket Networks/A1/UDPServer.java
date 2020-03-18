import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.List;

public class UDPServer implements Runnable {
	private int port;
	private DatagramSocket udp;
	private ExecutorService executorService = Executors.newSingleThreadExecutor();
	private List<String> chats = new ArrayList<String>();

	public UDPServer() {
		try {
			udp = new DatagramSocket();
		} catch (SocketException e) {
			e.printStackTrace();
		}
		port = udp.getLocalPort();
	}

	public int getUDPPort() {
		return port;
	}

	@Override
	public void run() {
		while (true) {
			byte[] buffer = new byte[65536];
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
			try {
				udp.receive(packet);
			} catch (IOException e) {
				e.printStackTrace();
			}
			executorService.submit(new ServiceRequest(packet));
		}

	}

	// Call this method stops the server
	private void stopServer() {
		// Stop the executor service.
		executorService.shutdownNow();
		udp.close();
		System.exit(0);
	}

	// This function handles all user requests.
	class ServiceRequest implements Runnable {
		private DatagramPacket packet;

		public ServiceRequest(DatagramPacket packet) {
			this.packet = packet;
		}

		public void run() {
			// until the client says a message "TERMINATE", we
			// will accept messages from the client
			String msg = new String(packet.getData(), packet.getOffset(), packet.getLength());
			if (msg.equals("TERMINATE")) {
				stopServer();
			} else if (msg.equals("GET")) {
				chats.forEach(chat -> {
					DatagramPacket thePacket = new DatagramPacket(chat.getBytes(), chat.getBytes().length,
							packet.getAddress(), packet.getPort());
					try {
						udp.send(thePacket);
					} catch (IOException e) {
						e.printStackTrace();
					}

				});
				String NO_MSG = new String("NO MSG");
				try {
					udp.send(new DatagramPacket(NO_MSG.getBytes(), NO_MSG.getBytes().length, packet.getAddress(),
							packet.getPort()));
				} catch (IOException e) {
					e.printStackTrace();
				}

			} else {
				chats.add("[" + packet.getPort() + "]: " + msg);
				System.out.println("[" + packet.getPort() + "]: " + msg);
			}
		}
	}

}
