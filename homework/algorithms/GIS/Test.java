import java.util.Locale;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.util.Stack;

final class In{
    private static String charsetName = "UTF-8";
    private static Locale locale = new Locale("zh", "cn");
    private static Scanner scanner;

    public In(){
        scanner = new Scanner(new BufferedInputStream(System.in), charsetName);
        scanner.useLocale(locale);
    }

    public int readInt(){
        return scanner.nextInt();
    }

    public void close(){
        scanner.close();
    }

    public boolean hasNextLine(){
        return scanner.hasNextLine();
    }

    public boolean hasNextInt(){
        return scanner.hasNextInt();
    }
}

public class Test{
    public static void main(String[] args){
        int V=0, E=0, S=-1, T=-1;
        Graph G = null;
        Dijkstra dij = null;

        In in = new In();
        if(in.hasNextLine()){
            V = in.readInt();
            E = in.readInt();
            G = new Graph(V, E);
        }

        int index, x, y, v, w;

        StdDraw.setCanvasSize(1024, 512);
        StdDraw.setXscale(0, 10000);
        StdDraw.setYscale(0, 5000);
        StdDraw.setPenRadius(0.002);
        StdDraw.enableDoubleBuffering();


        StdDraw.setPenColor(StdDraw.GRAY);
        for(int i=0; i<V; i++){
            if(in.hasNextLine()){
                index = in.readInt();
                x = in.readInt();
                y = in.readInt();

                G.addVertex(index, x, y);

                StdDraw.point(x, y);
            }
        }
        for(int i=0; i<E; i++){
            if(in.hasNextLine()){
                v = in.readInt();
                w = in.readInt();

                G.addEdge(v, w);

                StdDraw.line(G.getVertex(v).x, G.getVertex(v).y,
                        G.getVertex(w).x, G.getVertex(w).y); 
            }
        }
        if(in.hasNextInt())
            S = in.readInt();
        if(in.hasNextInt())
            T = in.readInt();
        in.close();

        if(S == -1 || T == -1){
            System.out.println("no source or destination.");
            return;
        }

        long startTime, endTime;
        startTime = System.currentTimeMillis();
        dij = new Dijkstra(G, S);
        endTime = System.currentTimeMillis();

        double sum = 0;
        int vNum = 1;

        Stack<Edge> path = dij.pathTo(T);
        
        StdDraw.setPenRadius(0.005);
        StdDraw.setPenColor(StdDraw.BLUE);
        
        System.out.print(S);
        while(path != null && !path.empty()){
            Edge e = path.pop();
            sum += e.weight;
            vNum += 1;
            System.out.print(" --> " + e.to());

            StdDraw.line(G.getVertex(e.from()).x, G.getVertex(e.from()).y,
                    G.getVertex(e.to()).x, G.getVertex(e.to()).y); 
        }
        StdDraw.show();
        System.out.println("\nvertex total: " + V + " edge total: " + E + " path length: " + sum +" vertex number: " + vNum + " run time: " + (endTime-startTime) + "ms");
    }
}
