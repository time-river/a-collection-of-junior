import java.io.*;
import java.net.*;

public class UdpServer {
    DatagramSocket socket = null;
    BufferedReader in = null;
    boolean moreQuotes = true;

    public void serverWork() throws IOException {
        socket = new DatagramSocket(4445);

        in = new BufferedReader(new FileReader("sentences.txt"));
        while (moreQuotes) {
            // 构造接收数据报并启动
            byte[] buf = new byte[256];
            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            socket.receive(packet);

            // 接收到 client 端的数据报，从 sentences.txt 中读取一行
            // 作为响应数据报中的数据
            String dString = null;
            if ((dString = in.readLine()) == null) {
                in.close();
                moreQuotes = false;
                dString = "No more sentences. Bye.";
            }
            buf = dString.getBytes();

            // 从接收到的数据报中获取 client 端的地址和端口
            // 构造响应数据并发送
            InetAddress address = packet.getAddress();
            int port = packet.getPort();
            System.out.println("address: " + address.toString());
            System.out.println("port: " + port);
            packet = new DatagramPacket(buf, buf.length, address, port);
            socket.send(packet);
        }
        socket.close();
    }

    public static void main(String[] args) {
        UdpServer server = new UdpServer();
        try {
            server.serverWork();
        } catch (IOException e) 
        {
            System.out.println("Error: " + e);
        }
    }
}
