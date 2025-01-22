public class Runner {
  public static void main(String[] args) {
    try {
      if (args[0].equals("s")) {
        Server s = new Server();
        s.listen();
      } else {
        Client c = new Client();
        c.connect(args.length > 1 ? args[1] : "127.0.0.1");
      }
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}