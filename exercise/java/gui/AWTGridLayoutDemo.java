import java.awt.*;
import java.awt.event.*;

public class AWTGridLayoutDemo extends Frame{
    private Button btn1, btn2, btn3, btn4, btn5, btn6;

    public AWTGridLayoutDemo(){
        setLayout(new GridLayout(3, 2, 3, 3));

        btn1 = new Button("Button 1");
        add(btn1);
        btn2 = new Button("This is Button 2");
        add(btn2);
        btn3 = new Button("3");
        add(btn3);
        btn4 = new Button("Another Button 4");
        add(btn4);
        btn5 = new Button("Button 5");
        add(btn5);
        btn6 = new Button("One More Button 6");
        add(btn6);

        setTitle("GridLayout Demo");
        setSize(280, 150);
        setVisible(true);
    }

    public static void main(String[] args){
        new AWTGridLayoutDemo();
    }
}
