import java.awt.*;
import java.awt.event.*;

public class AWTAccumulator extends Frame implements ActionListener{
    private Label lblInput;
    private Label lblOutput;
    private TextField tfInput;
    private TextField tfOutput;
    private int sum = 0;

    public AWTAccumulator(){
        setLayout(new FlowLayout());

        lblInput = new Label("Enter an Integer: ");
        add(lblInput);

        tfInput = new TextField(10);
        add(tfInput);

        tfInput.addActionListener(this);

        lblOutput = new Label("The Accumulated Sum is: ");
        add(lblOutput);

        tfOutput = new TextField(10);
        tfOutput.setEditable(false);
        add(tfOutput);

        setTitle("AWT Accumulator");
        setSize(350, 120);
        setVisible(true);
    }

    public static void main(String[] args){
        new AWTAccumulator();
    }

    @Override
    public void actionPerformed(ActionEvent evt){
        int numberIn = Integer.parseInt(tfInput.getText());
        sum += numberIn;
        tfInput.setText("");
        tfOutput.setText(sum + "");
    }
}
