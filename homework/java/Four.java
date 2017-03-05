import java.util.Scanner;
import java.io.BufferedInputStream;
import java.util.Locale;
import java.util.regex.*;

public class Four{
    public static void main(String[] args){
        String string = In.readAll();
        System.out.println("中英文字符数量: " + Statistics.charNumber(string));
        System.out.println("字符串数量: " + Statistics.stringNumber(string));
    }
}

class Statistics{
    static int charNumber(String string){
        Pattern pattern = Pattern.compile("[a-zA-Z\u4e00-\u9fa5]");
        Matcher m = pattern.matcher(string);

        int i = 0;
        while(m.find())
            i++;
        return i;
    }
    
    static int stringNumber(String string){
        Pattern pattern = Pattern.compile("\n");
        Matcher m = pattern.matcher(string);
        
        int i = 0;
        while(m.find())
            i++;
        return i;
    }
}

final class In{
    private static String charsetName = "UTF-8";
    private static Locale locale = new Locale("zh", "cn");
	private static Scanner scanner = new Scanner(new BufferedInputStream(System.in), charsetName);

    static { 
        scanner.useLocale(locale);
    }

    public static String readAll(){
        if(!scanner.hasNextLine())
            return null;
        return scanner.useDelimiter("\\A").next();
    }

    public void close(){
        scanner.close();
    }
}
