import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class ChatRoom implements ActionListener {
  private MessageList msgList;
  private JTextField newMsgField;
  private JButton sendButton;
  private Server s;
  private Client c;

  public ChatRoom(Server s, Client c) {
    this.s = s;
    this.c = c;
    msgList = new MessageList();
    newMsgField = new JTextField();
    sendButton = new JButton("Send");

    JFrame frame = new JFrame("Chat App");
    frame.setSize(411, 730);
    frame.setLayout(new BorderLayout());
    frame.add(msgList, BorderLayout.NORTH);

    JPanel chatPanel = new JPanel();
    chatPanel.setSize(20, 20);
    chatPanel.setLayout(new BorderLayout());
    chatPanel.add(newMsgField, BorderLayout.CENTER);
    chatPanel.add(sendButton, BorderLayout.LINE_END);

    frame.add(chatPanel, BorderLayout.SOUTH);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    sendButton.addActionListener(this);
    frame.setVisible(true);
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    if (ae.getSource() == sendButton) {
      msgList.showMessage("send");
    }
  }
}
