import java.util.Random;
import java.lang.Math;

public class PercolationStats{
    private int n;
    private int trials;
    private double[] samples;

    public PercolationStats(int n, int trials){ // perform trials independent experiments on an n-by-n grid
        this.n = n;
        this.trials = trials;
        samples = new double[trials];

        for(int k=0; k<trials; k++){
            Random random = new Random();
            Percolation percolation = new Percolation(n);
            int i, j, count=0;

            while(true){
                i = Math.abs(random.nextInt()) % n;
                j = Math.abs(random.nextInt()) % n;

                if(percolation.isOpen(i, j))
                    continue;
                else{
                    percolation.open(i, j);
                    count++;
                }

                if(percolation.percolates())
                    break;
            }
            samples[k] = (double)count / Math.pow(n, 2);
        }
    }
    public double mean(){ // samples mean of percolation threshold
        double sum=0;
        for(int i=0; i<trials; i++)
            sum += samples[i];
        return sum/trials;
    }
    public double stddev(){ // samples standard deviation of percolation threshold
        double mean = this.mean();
        double sum=0;
        for(int i=0; i<trials; i++)
            sum += Math.pow(samples[i]-mean, 2);
        return sum/(trials-1);
    }
    public double confidenceLo(){ // low endpoint of 95% confidence interval
        double mean = this.mean();
        double s = this.stddev();

        return mean-1.96*s/Math.pow(trials, 1/2);
    }
    public double confidenceHi(){ // high endpoint of 95% ocnfidence interval
        double mean = this.mean();
        double s = this.stddev();

        return mean+1.96*s/Math.pow(trials, 1/2);
    }
    public static void main(String[] args){ // test client (described below)
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);

        PercolationStats percolationStats = new PercolationStats(N, T);
        System.out.format("mean                    = %f\n", percolationStats.mean());
        System.out.format("stddev                  = %f\n", percolationStats.stddev());
        System.out.format("95%% confidence interval = %f, %f\n", percolationStats.confidenceLo(), percolationStats.confidenceHi());
    }
}
