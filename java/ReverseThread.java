import java.io.*;

public class ReverseThread extends Thread {
    private PrintWriter out = null;
    private BufferedReader in = null;
    public ReverseThread(PrintWriter out, BufferedReader in) {
        this.out = out;
        this.in = in;
    }

    public void run() {
        if (out != null && in != null) {
            try {
                String input;
                while ((input = in.readLine()) != null) {
                    out.println(reverseIt(input));
                    out.flush();
                }
                out.close();
            } catch (IOException e) {
                System.err.println("ReverseThread run: " + e);
            }
        }
    }

    // 单词逆序
    private String reverseIt(String source) {
        int i, len = source.length();
        StringBuffer dest = new StringBuffer(len);
        for (i=(len-1); i >= 0; i--)
            dest.append(source.charAt(i));
        return dest.toString();
    }
}
