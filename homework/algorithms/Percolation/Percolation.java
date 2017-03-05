import java.lang.Math;
import java.util.Arrays;
import java.util.Random;

public class Percolation {
    private int N;
    private boolean[][] grid;
    private UnionFind unionFind;

    public Percolation(int N){ // create N-by-N grid, with all sites blocked
        this.N = N;

        grid = new boolean[N][N];
        for(int i=0; i<N;i++)
            for(int j=0;j<N;j++)
                grid[i][j] = false;

        unionFind = new UnionFind(N*N+2);
        for(int i=0; i<N; i++){
            unionFind.union(N*N, i); // N*N is top
            unionFind.union(N*(N-1)+i, N*N+1); // N*N+1 is bottom
        }
    }
    public void open(int i, int j){ // open site(row i, column j) if it is not already
        if(i >= N || j >= N || grid[i][j])
            return;

        grid[i][j] = true;

        if(i>0 && grid[i-1][j]){
            unionFind.union(i*N+j, (i-1)*N+j);
        }
        if(i<(N-1) && grid[i+1][j]){
            unionFind.union(i*N+j, (i+1)*N+j);
        }
        if(j>0 && grid[i][j-1]){
            unionFind.union(i*N+j, i*N+(j-1));
        }
        if(j<(N-1) && grid[i][j+1]){
            unionFind.union(i*N+j, i*N+(j+1));
        }
    }
    public boolean isOpen(int i, int j){ // is site(row i, column j) open?
        return grid[i][j];
    }
    public boolean isFull(int i, int j){ // is site(row i, column j) full?
        return unionFind.connected(N*N, i*N+j);
    }
    public boolean percolates(){ // does the system percolate?
        return unionFind.connected(N*N, N*N+1);
    }
    public static void main(String[] args){ // test client, optional
        if(args.length != 2){
            System.out.println("error.");
            return;
        }
        int N = Integer.parseInt(args[0]);
        int cycle = Integer.parseInt(args[1]);

        int count=0;

        for(int k=0; k< cycle; k++){
            Percolation percolation = new Percolation(N);
            Random random = new Random();
            int i, j;

            while(true){
                i = Math.abs(random.nextInt()) % N;
                j = Math.abs(random.nextInt()) % N;

                if(percolation.isOpen(i, j)){
                    continue;
                }
                else{
                    percolation.open(i, j);
                    count++;
                }

                if(percolation.percolates())
                    break;
            }
        }
        System.out.format("%d-by-%d, posibility: %.3f\n", N, N, (float)count/((N*N)*cycle));
    }
}
