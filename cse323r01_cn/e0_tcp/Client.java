import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;

public class Client {
  public void connect(final String ip) throws IOException {
    Socket s = new Socket(ip, Constants.PORT);
    System.out.println("[Client] Connected to Server");
    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    System.out.println("[Server] ".concat(br.readLine()));
    PrintStream p = new PrintStream(s.getOutputStream());
    p.println("Bye");
    s.close();
    System.out.println("[Client] Connection terminated.");
  }
}