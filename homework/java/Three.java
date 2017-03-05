import java.util.Scanner;
import java.util.ArrayList;

public class Three{
    public static void main(String[] args){
    	Scanner scanner = new Scanner(System.in);
        Note note = new Note();

    	System.out.println("1.存储记录.");
    	System.out.println("2.查看存储记录数量.");
    	System.out.println("3.追加记录.");
    	System.out.println("4.展示全部记录.");
    	System.out.println("5.展示某个记录.");
    	System.out.println("6.删除全部记录.");
    	System.out.println("7.删除某个记录.");
    	System.out.println("8.退出程序.");
    	System.out.println("输入你的选择:");

    	while(true){
			switch(scanner.nextInt()){
                case 1:
                    System.out.println("输入记录，以#结束。");
                    String string = null;
                    while(true){
                        if(!scanner.hasNext())
                            break;
                        string = scanner.useDelimiter("\n").next();
                        if(string.matches("#"))
                            break;
                        note.append(string);
                    }
                    System.out.println("添加成功。");
                    break;
                case 2:
                    System.out.println("共" + note.getSize() + "条记录。");
                    break;
                case 3:
                    System.out.println("输入要追加的内容。");
                    if(scanner.hasNextLine()){
                        string = scanner.useDelimiter("\n").next();
                        note.append(string);
                        System.out.println("追加成功。");
                    } else {
                        System.out.println("无输入，无法追加。");
                    }
                    break;
                case 4:
                    note.display();
                    break;
                case 5:
                    System.out.println("输入记录的序号。");
                    if(scanner.hasNextLine()){
                        int n = scanner.nextInt();
                        note.display(n-1);
                    }
                    break;
                case 6:
                    note.removeAll();
                    break;
                case 7:                    
                    System.out.println("输入记录的序号。");
                    if(scanner.hasNextLine()){
                        int n = scanner.nextInt();
                        note.remove(n-1);
                    }
                    break;
                case 8:
                    System.out.println("Bye~");
                    return;
            }
        }
    }
}

class Note{
    private ArrayList<String> list = new ArrayList<String>();

    public void add(String string){
        list.add(string);
    }

    public void removeAll(){
        list.clear();
        System.out.println("清空成功。");
    }

    public void remove(int n){
        if(n < list.size()){
            list.remove(n);
            System.out.println("删除成功。");
        }
        else
            System.out.println("删除失败。");
    }
    
    public void display(){
        for(String tmp: list){
            System.out.println(tmp);
        }
    }

    public void display(int n){
        if(n < list.size()){
            System.out.println(list.get(n));
        } else{
            System.out.println("不存在该条记录。");
        }
    }
    public int getSize(){
        return list.size();
    }

    public void append(String string){
        list.add(string);
    }
}
