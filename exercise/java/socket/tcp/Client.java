import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("127.0.0.1", 1680); // 发出连接请求

            // 建立连接，通过 socket 获取连接上的输入/输出流
            /* out --> socket */
            PrintWriter out = new PrintWriter(socket.getOutputStream());
            /* buffer <-- InputStream <-- socket */
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
            
            // 创建标准输入流，从键盘接收数据
            /* buffer <-- InputStream <-- standard in */
            BufferedReader sin = new BufferedReader(
                    new InputStreamReader(System.in));

            String s;
            do {
                s = sin.readLine();
                out.println(s);
                out.flush();
                if (!s.equals("bye")) {
                    System.out.println("@ Server response: " + in.readLine());
                } else {
                    System.out.println("The connection is closing... ");
                }
            } while (!s.equals("bye"));

            out.close();
            in.close();
            socket.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}

/**
 * 字符流 Reader / Writer
 * 字节流 InputStream / OutStream
 * 
 * 节点流 —— Memory / Pipe / File
 * 过滤流 —— Object Serialization / Data Conversion / Buffering / Filtering / Concatenation / Peeking Ahead / Converting between Bytes and Characters
 *
 * 输入 / 输出流的套接
 * 比如：
 *     数据源 --> FileInputStream  --> BufferedInputStream  --> DataInputStream  --> 程序
 *     程序   --> DataOutputStream --> BufferedOutputStream --> FileOutputStream --> 数据接收节点
 *
 * 1. 文件流 —— 文件系统的文件进行读写
 *    FileInputStream / FileOutputStream, FileReader / FileWriter
 * 2. 缓存流 —— 从原始流成块读入或把数据积累到一个大数据块后再成批写出
 *    BufferedInputStream / BufferedOutputStream, BufferedReader / BufferedWriter
 * 3. 管道流 —— 线程间数据的直接传输
 *    PipedReader / PipedWriter, PipedInputStream / PipedOutputStream
 * 4. 数据流 —— 允许按 Java 的基本数据类型读写流中的数据
 *    DataInputStream / DataOutputStream
 * 5. 标准输入/输出
 *    System.in / System.out / System.err
 *    
 */
