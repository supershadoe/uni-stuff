import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class ConnectPage implements ActionListener {
  private JTextField ipField, portField;
  private JButton connectButton;
  private ConnectionCallback callback;

  public ConnectPage(Connectioncallback callback) {
    this.callback = callback;

    ipField = new JTextField();
    portField = new JTextField();
    connectButton = new JButton("Connect");

    JFrame frame = new JFrame("Chat App");
    frame.setSize(100, 100);
    frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
    frame.add(ipField);
    frame.add(portField);
    frame.add(connectButton);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    connectButton.addActionListener(this);
    frame.setVisible(true);
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    callback.onConnectionCreate(
      ipField.getText(),
      Integer.parseInt(portField.getText())
    );
  }
}
