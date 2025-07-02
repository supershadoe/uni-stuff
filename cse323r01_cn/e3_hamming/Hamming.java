import java.lang.Math;

public class Hamming {
  public static String encode(String message) {
    final int m = message.length();
    int k = 0;
    while (Math.pow(2, k) < m + k + 1) {
      k++;
    }
    final int k = k;
    final int n = m + k;
    char[] ch = new char[n];
    int j = 0;
    for (int i = 1; i <= n; i++) {
      // Skip if power of 2
      if (i & (i - 1) == 0) {
        continue;
      }
      ch[i - 1] = message.charAt(j);
      j++;
    }
    for (int i = 0; i < k; i++) {
      char parity = '0';
      // Skip i
      for (int j = Math.pow(2, i); j < n; j += i + 1) {
        // Take i
        for (int k = j; k <= j + i + 1; k++) {
          // to finish
        }
      }
    }
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
