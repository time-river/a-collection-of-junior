import java.net.*;
import java.io.*;

public class URLReader {
    public static void main(String[] args) throws Exception {
        URL baidu = new URL("https://www.baidu.com/index.html");
        BufferedReader in = new BufferedReader(
                new InputStreamReader(baidu.openStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null)
            System.out.print(inputLine);
        in.close();
    }
}
