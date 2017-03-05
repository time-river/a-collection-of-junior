import java.util.Random;
import java.util.Arrays;

public class Test extends Object implements Cloneable{
    Integer[] ordered = null;
    Integer[] reversed = null;
    Integer[] unordered = null;
    int size;

    public Test(int size){
        this.size = size;

        ordered = new Integer[this.size];
        reversed = new Integer[this.size];
        unordered = new Integer[this.size];
        Random random = new Random();

        for(int i=0; i<this.size; i++){
            ordered[i] = i;
            reversed[i] = size - i;
            unordered[i] = random.nextInt();
        }
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        Test t = (Test)super.clone();
        t.ordered = ordered.clone();
        t.reversed = reversed.clone();
        t.unordered = unordered.clone();

        return t;
    }

    public static void main(String[] args){
        if(args.length !=2 ){
            System.out.println("args [number] [cycle]");
            return;
        }
        int N = Integer.parseInt(args[0]);
        float cycle = Float.parseFloat(args[1]);
        long[] time = new long[18];
        boolean[] flag = new boolean[18];
        long startTime, endTime;

        for(int i=0; i<18; i++){
            time[i] = 0;
            flag[i] = false;
        }

        for(int i=0; i<cycle; i++){
            Test data = new Test(N);

            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis(); 
                    Insertion.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[0] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[0] = true;
                }

                try{
                    startTime = System.currentTimeMillis(); 
                    Insertion.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[1] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[1] = true;
                }

                try{
                    startTime = System.currentTimeMillis(); 
                    Insertion.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[2] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[2] = true;
                }
            } catch(CloneNotSupportedException e){ e.printStackTrace();}


            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis();
                    Merge.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[3] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[3] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    Merge.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[4] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[4] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    Merge.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[5] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[5] = true;
                }
            } catch(CloneNotSupportedException e){}

            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis();
                    MergeBU.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[6] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[6] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    MergeBU.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[7] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[7] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    MergeBU.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[8] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[8] = true;
                }
            } catch(CloneNotSupportedException e){}

            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis();
                    Quick.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[9] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[9] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    Quick.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[10] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[10] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    Quick.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[11] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[11] = true;
                }
            } catch(CloneNotSupportedException e){}

            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis();
                    QuickDijkstra.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[12] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[12] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    QuickDijkstra.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[13] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[13] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    QuickDijkstra.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[14] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[14] = true;
                }
            } catch(CloneNotSupportedException e){}

            try{
                Test test = (Test)data.clone();

                try{
                    startTime = System.currentTimeMillis();
                    QuickBentleyMcllroy.sort(test.ordered);
                    endTime=System.currentTimeMillis();
                    time[15] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[15] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    QuickBentleyMcllroy.sort(test.reversed);
                    endTime=System.currentTimeMillis();
                    time[16] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[16] = true;
                }

                try{
                    startTime = System.currentTimeMillis();
                    QuickBentleyMcllroy.sort(test.unordered);
                    endTime=System.currentTimeMillis();
                    time[17] += endTime - startTime;
                } catch(StackOverflowError e){
                    flag[17] = true;
                }
            } catch(CloneNotSupportedException e){}
        }

        System.out.format("Insertion sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[0]?-1.0:time[0]/cycle, flag[1]?-1.0:time[1]/cycle, flag[2]?-1.0:time[2]/cycle);

        System.out.format("Merge sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[3]?-1.0:time[3]/cycle, flag[4]?-1.0:time[4]/cycle, flag[5]?-1.0:time[5]/cycle);

        System.out.format("MergeBU sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[6]?-1.0:time[6]/cycle, flag[7]?-1.0:time[7]/cycle, flag[8]?-1.0:time[8]/cycle);

        System.out.format("Quick sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[9]?-1.0:time[9]/cycle, flag[10]?-1.0:time[10]/cycle, flag[11]?-1.0:time[11]/cycle);

        System.out.format("QuickDijkstra sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[12]?-1.0:time[12]/cycle, flag[13]?-1.0:time[13]/cycle, flag[14]?-1.0:time[14]/cycle);

        System.out.format("QuickBentleyMcllroy sort:\n" +
                "   ordered: %.3f\n" +
                "   reversed: %.3f\n" +
                "   unordered: %.3f\n\n", flag[15]?-1.0:time[15]/cycle, flag[16]?-1.0:time[16]/cycle, flag[17]?-1.0:time[17]/cycle);
    }
}
