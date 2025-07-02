public class App {
  public static void main(String[] args) {
    ConnectPage cp = new ConnectPage(new ConnectionCallback() {
      @Override
      public void onConnectionCreate(String ip, int port) {
        Server s = new Server(port);
        Client c = new Client();
        c.connect(ip, port);
        cp.setVisible(false);
        ChatRoom cr = new ChatRoom(s, c);
      }
    });
  }
}