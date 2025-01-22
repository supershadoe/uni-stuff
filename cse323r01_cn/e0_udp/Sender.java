import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Sender {
  private final DatagramSocket s;

  public Sender() throws IOException {
    s = new DatagramSocket(Constants.SENDER_PORT);
  }

  private void draftMsg(InetAddress ip) throws IOException {
    String msg = "Hello";
    DatagramPacket p = new DatagramPacket(
      msg.getBytes(),
      msg.length(),
      ip,
      Constants.RECEIVER_PORT
    );
    s.send(p);
    String out = new StringBuilder("[Sender] Sent message to ")
      .append(ip.getHostAddress().toString())
      .append(":")
      .append(Constants.RECEIVER_PORT)
      .append(": ")
      .append(msg)
      .toString();
    System.out.println(out);
  }

  public void send(String ipAddress) throws IOException, InterruptedException {
    System.out.println("[Sender] Sending messages.");
    InetAddress ip = InetAddress.getByName(ipAddress);
    while(true) {
      draftMsg(ip);
      Thread.sleep(5000);
    }
  }
}
