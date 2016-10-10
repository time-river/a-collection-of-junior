import java.net.*;
import java.io.*;

public class ParseURL {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://www.baidu.com:443/" + "index.html");
        System.out.println("protocol: " + url.getProtocol());
        System.out.println("host: " + url.getHost());
        System.out.println("filename: " + url.getFile());
        System.out.println("port: " + url.getPort());
        System.out.println("ref: " + url.getRef());
    }
}
