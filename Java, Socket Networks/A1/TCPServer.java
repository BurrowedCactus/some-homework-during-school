import java.net.*;
import java.io.*;
import java.util.concurrent.*;

public class TCPServer implements Runnable {
	private ServerSocket serverSocket;
	private int UDPport;
	private int req_code;
	private ExecutorService executorService = Executors.newSingleThreadExecutor();

	TCPServer(int port, int req_code) {
		this.UDPport = port;
		this.req_code = req_code;
	}

	@Override
	public void run() {
		try {
			serverSocket = new ServerSocket(0);
		} catch (IOException e) {
			System.exit(1);
		}
		System.out.println("listening on port: " + serverSocket.getLocalPort());
		while (true) {
			try {
				// for each message we create a thread to handle it.
				Socket s = serverSocket.accept();
				executorService.submit(new ServiceRequest(s));
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
		}
	}

	// Call this method stops the server
	private void stopServer() {
		// Stop the executor service.
		executorService.shutdownNow();
		try {
			// Stop accepting requests.
			serverSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.exit(0);
	}

	// This function handles all user requests.
	class ServiceRequest implements Runnable {
		private Socket socket;

		public ServiceRequest(Socket connection) {
			this.socket = connection;
		}

		public void run() {
			String client_message = "";
			try {
				// A buffer ---> wait for data from the client
				BufferedReader is = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				PrintStream os = new PrintStream(socket.getOutputStream());
				client_message = is.readLine();
				int result = -1;
				try {
					result = Integer.parseInt(client_message);
				} catch (NumberFormatException nfe) {
					result = -1;
				}
				if (result == req_code) {
					os.println(Integer.toString(UDPport));
					os.flush();
				} else {
					os.println("0");
					os.flush();
				}
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
			if (client_message.equals("TERMINATE")) {
				stopServer();
			}
		}
	}
}
