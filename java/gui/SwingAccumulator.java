import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SwingAccumulator extends JFrame{
    private JTextField tfInput, tfOutput;
    private int sum = 0;

    public SwingAccumulator(){
        Container cp = getContentPane();
        cp.setLayout(new GridLayout(2, 2, 5, 5));

        add(new JLabel("Enter an Integer: "));
        tfInput = new JTextField(10);
        add(tfInput);
        add(new JLabel("The Accumulated Sum is: "));
        tfOutput = new JTextField(10);
        tfOutput.setEditable(false);
        add(tfOutput);

        tfInput.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent evt){
                int numberIn = Integer.parseInt(tfInput.getText());
                sum += numberIn;
                tfInput.setText("");
                tfOutput.setText(sum + "");
            }
        });

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Swing Accumulator");
        setSize(350, 120);
        setVisible(true);
    }

    public static void main(String[] args){
        SwingUtilities.invokeLater(new Runnable(){
            @Override
            public void run(){
                new SwingAccumulator();
            }
        });
    }
}
