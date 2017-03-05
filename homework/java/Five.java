import java.lang.Thread;
import java.util.Random;

public class Five{
    public static void main(String[] args){
        Movie movie = new Movie(15);
        for(int i = 0; i < 3; i++){
            Window w = new Window(movie, i+1);
            new Thread(w).start();
        } 
    }
}

class Window extends Thread{
    private int num;
    private Movie movie = null;
    private Random random = new Random();

    Window(Movie movie, int num){
        this.movie = movie;
        this.num = num;
    }

    public void run(){
        while(!movie.isEmpty()){
            System.out.println("窗口：" + num + "出售编号为" + movie.getTicket() + "电影票。");
            try{
                Thread.currentThread().sleep(Math.abs(random.nextInt())%10*1000);
            } catch (InterruptedException e){}
        }
    }
}

class Movie{
    private int total;
    private int i = 0;
    
    Movie(int total){
        this.total = total;
    }

    public synchronized int getTicket(){
        i++;
        return i;
    }

    public boolean isEmpty(){
        if(i == total)
            return true;
        else
            return false;
    }
}
