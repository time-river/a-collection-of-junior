public class Outer{
    private int size;

    public class Inner{
        public void doStuff(){
            size++;
        }
    }

    Inner i = new Inner();

    public void increaseSize(){
        i.doStuff();
    }

    public static void main(String[] args){
        Outer o = new Outer();
        for (int i=0; i<4; i++){
            o.increaseSize();
            System.out.println("The value of size: " + o.size);
        }
    }
}
