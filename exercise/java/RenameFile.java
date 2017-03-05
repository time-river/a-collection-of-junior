import java.io.*;
import java.util.Date;

public class RenameFile {
    private static void fileData(File f){
        System.out.println(
                "Absolute path: " + f.getAbsolutePath() +
                "\nCan read: " + f.canRead() +
                "\nCan write: " + f.canWrite() +
                "\ngetName: " + f.getName() +
                "\ngetParent: " + f.getParent() +
                "\ngetPath: " + f.getPath() +
                "\nlength: " + f.length() +
                "\nlastModified: " + new Date(f.lastModified()));
        if(f.isFile())
            System.out.println("It's a file");
        else if(f.isDirectory()) {
            System.out.println("It's a directory");
        }
    }

    public static void main(String[] args) {
        File old = new File(args[0]);
        File rname = new File(args[1]);
        System.out.println("The original file's information:");
        fileData(old);
        old.renameTo(rname);
        System.out.println("\nThe file information after rename:");
        fileData(rname);
        if (!old.exists()) {
            System.out.println("\nThe original file never exists.");
        }
    }
}
