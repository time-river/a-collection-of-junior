import java.net.*;
import java.io.*;

public class URLConnection {
    public static void main(String[] args) throws Exception {
        URL oracle = new URL("https://www.baidu.com/");
        HttpURLConnection yc = (HttpURLConnection)oracle.openConnection();
        BufferedReader in = new BufferedReader(new InputStreamReader(
                                    yc.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) 
            System.out.println(inputLine);
        in.close();
    }
}
