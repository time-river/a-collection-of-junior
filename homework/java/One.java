import java.util.*;

public class One {
    private int num;

    One(int num){
        this.num = num;
    }

    public void sumAndPrime(){
        int sum = 0, count=0;
        for(int i=1; i<=num; i++)
            sum += i;
        System.out.println("From 1 to " + num + ", sum is " + sum);

        for(int i=2; i<=sum; i++){
            if(this.isPrime(i))
                count++;
        }
        System.out.println("From 1 to " + sum + ", the number of prime is " + count);
    }

    private boolean isPrime(int n){
        if(n == 2)
            return true;
        if(n%2 == 0)
            return false;
        for(int i=3; i*i <= n; i+=2)
            if(n%i == 0)
                return false;
        return true;
    }

    public void parity(){
        int number = num, tmp;
        int oddSum = 0, evenSum = 0, everySum = 0;

        do{
            tmp = number % 10;
            everySum += tmp;
            if(tmp%2 == 0){
                evenSum += 1;
                System.out.print("偶数 ");
            }
            else{
                oddSum += 1;
                System.out.print("奇数 ");
            }
            number /= 10;
        } while(number != 0);

        System.out.print("\n");
        System.out.println("偶数的数量: " + evenSum);
        System.out.println("奇数的数量: " + oddSum);
        System.out.println("各位的加和值：" + everySum);
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        System.out.println("输入一个整数：");
        One base = new One(in.nextInt());

        System.out.println("选择:");
        System.out.println("    1. 程序计算并输出从 1 开始到该整数的所有整数之和；同时，计算并输出不大于该整数的所有素数的数目。");
        System.out.println("    2. 程序判断该数字串各位上数字的奇偶性，并分别输出奇、偶数位的计数值及各位的加和值.");
        String next = in.next();
        if(next.equals("2"))
            base.parity();
        else
            base.sumAndPrime();
    }
}

