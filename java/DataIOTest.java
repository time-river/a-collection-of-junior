import java.io.*;

public class DataIOTest {
    public static void main(String[] args) throws IOException {
        DataOutputStream out = new DataOutputStream(new  FileOutputStream("/tmp/invoice1.txt"));
        double[] prices = {
            19.99, 9.99, 15.99, 3.99, 4.99
        };
        int[] units = { 12, 8, 13, 29, 50 };
        String[] descs = { 
            "Java T-shirt", "Java Mug", "Duke Jugging Dolls", "Java Pin", "Java Key Chain"
        };

        for (int i=0; i<prices.length; i++) {
            out.writeDouble(prices[i]);
            out.writeChar('\t');
            out.writeInt(units[i]);
            out.writeChar('\t');
            out.writeUTF(descs[i]);
            out.writeChar('\t');
        }
        out.close();

        DataInputStream in = new DataInputStream(new FileInputStream("/tmp/invoice1.txt"));
        double price;
        int unit;
        String desc;
        double total = 0.0;

        for (int i=0; i<prices.length; i++) {
            price = in.readDouble();
            in.readChar();
            unit = in.readInt();
            in.readChar();
            desc = in.readUTF();
            in.readChar();
            System.out.println("You've ordered " +
                    unit + " units of " +
                    desc + " at $" + price);
            total = total + unit * price;
        }
        System.out.println("For a TOTAL of: $" + total);
        in.close();
    }
}
