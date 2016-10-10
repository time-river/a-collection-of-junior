import java.net.*;
import java.io.*;

public class Server {
    public static void main(String args[]) {
        try {
            // 建立 socket 并等待连接请求
            ServerSocket server = new ServerSocket(1680);
            Socket socket = server.accept();

            // 连接建立，通过 socket 获取连接上的输入/输出流
            /* buffer <-- InputStream <-- socket */
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
            /* out --> socket */
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            // 标准输入流
            /* buffer <-- InputStream <-- in */
            BufferedReader sin = new BufferedReader(
                    new InputStreamReader(System.in));

            String s;
            while (!(s = in.readLine()).equals("bye")) {
                System.out.println("# Received from Client: " + s);
                out.println(sin.readLine());
                out.flush();
            }

            System.out.println("The connection is closing...");
            in.close();
            out.close();
            socket.close();
            server.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}
