import java.io.*;
public class Server {
	static int REQ_CODE;

	public static void main(String[] args) {
		UDPServer theUDPServer = new UDPServer();
		if(args.length == 1) {
			REQ_CODE = Integer.parseInt(args[0]);
		} else {
			REQ_CODE = 123456;
		}
		TCPServer theTCPServer = new TCPServer(theUDPServer.getUDPPort(), REQ_CODE);
		Thread t1 = new Thread(theTCPServer);
		Thread t2 = new Thread(theUDPServer);
		t1.start();
		t2.start();
	}
}
