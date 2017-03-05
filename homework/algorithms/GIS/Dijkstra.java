import java.util.PriorityQueue;
import java.util.Stack;
import java.lang.Comparable;

public class Dijkstra{
    private Graph G;
    private int V, E, S;
    private PriorityQueue<Node> pq = new PriorityQueue<Node>();
    private Edge[] edgeTo = null;
    private double[] distTo = null;
    
    public Dijkstra(Graph G, int S){
        V = G.vertexNumber;
        E = G.edgeNumber;
        this.S = S;
        this.G = G;

        pq = new PriorityQueue<Node>();
        edgeTo = new Edge[V];
        distTo = new double[V];

        for(int i=0; i<V; i++)
            distTo[i] = Double.POSITIVE_INFINITY;
        distTo[S] = 0;

        Node startNode = new Node(S, 0.0);
        pq.add(startNode);

        while(pq.size() != 0){
            int nowVertexIndex = pq.poll().to();
            for(Edge e: G.getVertex(nowVertexIndex).getNeighbors()){
                relax(e);
            }
        }
    }

    private void relax(Edge e){
        int v = e.from(), w = e.to();
        Node old = new Node(w, distTo[w]);
        if(distTo[w] > distTo[v]+e.weight){
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;

            Node next = new Node(w, distTo(w));
            if(pq.contains(old)){
                pq.remove(old);
            }
            pq.add(next);
        }
    }

    public double distTo(int v){
        return distTo[v];
    }

    public boolean hasPathTo(int v){
        return distTo[v] < Double.POSITIVE_INFINITY;
    }

    public Stack<Edge> pathTo(int v){
        if(!hasPathTo(v)) return null;
        Stack<Edge> path = new Stack<Edge>();
        for(Edge e=edgeTo[v]; e!= null; e=edgeTo[e.from()]){
            path.push(e);
        }
        return path;
    }
}

class Node implements Comparable<Node>{
    int nextVertex;
    double weight;
    
    Node(int v, double weight){
        this.nextVertex = v;
        this.weight = weight;
    }

    public int to(){
        return nextVertex;
    }

    public int compareTo(Node w){
        if(weight < w.weight) return -1;
        else if(weight == w.weight) return 0;
        else    return 1;
    }
}
