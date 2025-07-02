import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
  private final ServerSocket ss;

  public Server(int port) throws IOException {
    ss = new ServerSocket(port);
  }

  private void decode() throws IOException {
    System.out.println("[Server] Listening for requests.");
    Socket s = ss.accept();
    System.out.println("[Server] Connection established.");
    PrintStream p = new PrintStream(s.getOutputStream());
    p.println("Hello");
    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    System.out.println("[Client] ".concat(br.readLine()));
    if (s.isConnected()) {
      s.close();
    }
    System.out.println("[Server] Connection closed.");
  }

  public void listen() throws IOException {
    while(true) {
      decode();
    }
  }
}