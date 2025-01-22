import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.charset.StandardCharsets;

public class Receiver {
  private final DatagramSocket s;

  public Receiver() throws IOException {
    s = new DatagramSocket(Constants.RECEIVER_PORT);
  }

  private void decode() throws IOException {
    byte b[] = new byte[1000];
    DatagramPacket p = new DatagramPacket(b, b.length);
    s.receive(p);
    String message = new StringBuilder()
      .append("[Receiver] Received message from ")
      .append(p.getAddress().getHostAddress().toString())
      .append(":")
      .append(Integer.toString(p.getPort()))
      .append(": ")
      .append(new String(b, StandardCharsets.UTF_8))
      .toString();
    System.out.println(message);
  }

  public void receive() throws IOException {
    while (true) {
      decode();
    }
  }
}