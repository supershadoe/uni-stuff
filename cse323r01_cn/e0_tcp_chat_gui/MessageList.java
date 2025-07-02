import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;

class MessageList extends JPanel {
  MessageList() {
    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
  }

  public void showMessage(String s) {
    add(new JLabel(s));
    revalidate();
  }
}