import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
  private final ServerSocket ss;
  private final String fName;

  public Server(String fName) throws IOException {
    ss = new ServerSocket(Constants.PORT);
    this.fName = fName;
  }

  private void decode() throws IOException, FileNotFoundException {
    System.out.println("[Server] Listening for requests.");
    Socket s = ss.accept();
    System.out.println("[Server] Connection established.");
    File f = new File(fName);
    FileInputStream fin = new FileInputStream(f);
    System.out.println("[Server] Reading from " + fName);
    int b = fin.read();
    String message = "";
    while (b != -1) {
      message += (char) b;
      b = fin.read();
    }
    PrintStream p = new PrintStream(s.getOutputStream());
    p.println(message);
    System.out.println(
      "[Server] Sent file to " +
      s.getInetAddress().getHostAddress() +
      ":" + s.getPort()
    );
    if (s.isConnected()) {
      s.close();
    }
    fin.close();
    System.out.println("[Server] Connection closed.");
  }

  public void listen() throws IOException {
    while(true) {
      decode();
    }
  }

  public static void main(String[] args) {
    String fName = (args.length > 2) ? args[0] : "in.txt";
    try {
      Server s = new Server(fName);
      s.listen();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}