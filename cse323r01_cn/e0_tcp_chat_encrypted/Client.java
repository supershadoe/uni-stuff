import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.net.Socket;
import java.util.Scanner;

public class Client {
  private final FileOutputStream f;
  private final PrintStream p;

  public static final int KEY = 12;

  public Client() throws IOException, FileNotFoundException {
    f = new FileOutputStream("chat_log_client.txt");
    p = new PrintStream(f);
  }

  private String encrypt(String msg, int key) {
    String encrypted = "";
    for (char c: msg.toCharArray()) {
      encrypted += (char) (c + key);
    }
    return encrypted;
  }

  private String decrypt(String msg) {
    String decrypted = "";
    for (char c: msg.toCharArray()) {
      decrypted += (char) (c - KEY);
    }
    return decrypted;
  }

  private void processMessage(Socket s) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    String message = br.readLine();
    String msg = "[Server] "+ message;
    System.out.println(msg);
    p.println(msg);
    msg = "[Server (D)] "+ decrypt(message);
    System.out.println(msg);
    p.println(msg);
  }

  private String readMessage(InputStream i) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(i));
    int b = br.read();
    String message = "";
    while (b != -1) {
      message += (char) b;
      b = br.read();
    }
    return message;
  }

  public void connect() throws IOException, InterruptedException {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter IP address: ");
    String ip = sc.next();
    System.out.print("Enter port: ");
    int port = sc.nextInt();
    
    while (true) {
      Socket s = new Socket(ip, port);
      PrintStream sp = new PrintStream(s.getOutputStream());
      System.out.print("Enter text to send: ");
      String message = sc.next();
      p.println("[Client] Sent message: " + message);
      String encrypted = encrypt(message, Server.KEY);
      message = "[Client] Encrypted message: " + encrypted;
      System.out.println(message);
      p.println(message);
      sp.println(encrypted);
      Thread.sleep(5000);
      processMessage(s);
    }
  }

  public static void main(String[] args) {
    try {
      Client c = new Client();
      c.connect();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}