import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;

public class Client {
  private final String fName;

  public Client(String fName) {
    this.fName = fName;
  }

  public void connect(final String ip) throws IOException, FileNotFoundException {
    Socket s = new Socket(ip, Constants.PORT);
    System.out.println(
      "[Client] Connected to Server at " +
      s.getInetAddress().getHostAddress() +
      ":" + s.getPort()
    );
    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    File f = new File(fName);
    FileOutputStream fout = new FileOutputStream(f);
    int b = br.read();
    while (b != -1) {
      fout.write(b);
      b = br.read();
    }
    System.out.println("[Client] Wrote message to " + fName);
    s.close();
    fout.close();
    System.out.println("[Client] Connection terminated.");
  }

  public static void main(String[] args) {
    try {
      String ip = (args.length > 1) ? args[0] : "127.0.0.1";
      String fName = (args.length > 2) ? args[0] : "out.txt";
      Client c = new Client(fName);
      c.connect(ip);
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}