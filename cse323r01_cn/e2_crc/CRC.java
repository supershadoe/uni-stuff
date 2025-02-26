public class CRC {
  private static String xor(String div, String polyn) {
    String res = "";
    for (int i = 0; i < div.length(); i++) {
      res += div.charAt(i) == polyn.charAt(i) ? "0" : "1";
    }
    return res.charAt(0) == '0' ? res.substring(1) : res;
  }
  private static String modulo2(String message, String polyn) {
    int redundantBitCount = polyn.length() - 1;
    String rMsg = message;
    for (int i = 0; i < redundantBitCount; i++) {
      rMsg += "0";
    }
    String quotient = "";
    String remainder = message.substring(0, redundantBitCount);

    for (int i = redundantBitCount; i < rMsg.length(); i++) {
      remainder += rMsg.charAt(i);
      if (remainder.charAt(0) == '0') {
        remainder = remainder.substring(1);
        quotient += "0";
      } else {
        quotient += "1";
        remainder = xor(remainder, polyn);
      }
    }

    return remainder;
  }
  public static String encode(String message, String polyn) {
    return message + modulo2(message, polyn);
  }
  public static boolean verify(String message, String polyn) {
    String remainder = modulo2(message, polyn);
    for (int i = 0; i < remainder.length(); i++) {
      if (remainder.charAt(i) == '1') {
        return false;
      }
    }
    return true;
  }
  public static void main(String[] args) {
    if (args[0].equals("/v") || args[0].equals("/V")) {
      if (verify(args[1], args[2])) {
        System.out.println("No errors");
      } else {
        System.out.println("Corrupted message");
      }
    } else if (args[0].equals("/e") || args[0].equals("/E")) {
      System.out.println("Encoded message: " + encode(args[1], args[2]));
    } else {
      System.err.println("Unknown arg");
    }
  }
}