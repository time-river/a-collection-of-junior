import java.io.*;
import java.net.*;

public class MultiClientServer implements Runnable {
    static int SerialNum = 0;
    Socket socket;
    public MultiClientServer(Socket ss) {
        socket = ss;
    }

    public static void main(String args[]) {
        int MaxClientNum = 5;
        try {
            ServerSocket server = new ServerSocket(1680);
            for (int i=0; i<MaxClientNum; i++) {
                Socket socket = server.accept();
                Thread t = new Thread(new MultiClientServer(socket));
                t.start();
            }
            server.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }

    public void run() {
        int myNum = ++ SerialNum;
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            BufferedReader sin = new BufferedReader(new InputStreamReader(System.in));

            String s;
            while (!(s = in.readLine()).equals("bye")) {
                System.out.println("# Reveived from Client No. " + myNum + ": " + s);
                out.println(sin.readLine());
                out.flush();
            }
            System.out.println("The connection to Client No. " + myNum + " is closing...");
            in.close();
            out.close();
            socket.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}
