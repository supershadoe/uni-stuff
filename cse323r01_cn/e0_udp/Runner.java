public class Runner {
  public static void main(String[] args) {
    try {
      if (args[0].equals("s")) {
        Sender s = new Sender();
        s.send(args.length > 1 ? args[1] : "127.0.0.1");
      } else {
        Receiver r = new Receiver();
        r.receive();
      }
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}