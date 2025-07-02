import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
  private final ServerSocket ss;
  private final FileOutputStream f;
  private final PrintStream p;

  public static final int KEY = 14;

  public Server() throws IOException, FileNotFoundException {
    ss = new ServerSocket(4123);
    f = new FileOutputStream("chat_log_server.txt");
    p = new PrintStream(f);
  }

  private static String encrypt(String msg, int key) {
    String encrypted = "";
    for (char c: msg.toCharArray()) {
      encrypted += (char) (c + key);
    }
    return encrypted;
  }

  private static String decrypt(String msg) {
    String decrypted = "";
    for (char c: msg.toCharArray()) {
      decrypted += (char) (c - KEY);
    }
    return decrypted;
  }

  private void processMessage(Socket s) throws IOException {
    String msg = "[Server] Connection established.";
    System.out.println(msg);
    p.println(msg);
    BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    String message = br.readLine();
    msg = "[Client] "+ message;
    System.out.println(msg);
    p.println(msg);
    msg = "[Client (D)] "+ decrypt(message);
    System.out.println(msg);
    p.println(msg);
  }

  private void sendMessage(Socket s) throws IOException {
    PrintStream sp = new PrintStream(s.getOutputStream());
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter reply: ");
    String message = sc.next();
    p.println("[Server] Sent reply: " + message);
    String encrypted = encrypt(message, Client.KEY);
    message = "[Server] Encrypted message: " + encrypted;
    System.out.println(message);
    p.println(message);
    sp.println(encrypted);
  }

  public void waitForMessage() throws IOException {
    String message = "[Server] Waiting for connections.";
    System.out.println(message);
    p.println(message);
    while (true) {
      Socket s = ss.accept();
      processMessage(s);
      sendMessage(s);
    }
  }

  public static void main(String[] args) {
    try {
      Server s = new Server();
      s.waitForMessage();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}