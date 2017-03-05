import java.util.ArrayList;

class Vertex{
    int index;
    int x, y;
    private ArrayList<Edge> list = new ArrayList<Edge>();

    public Vertex(int index, int x, int y){ // Vertex information: index, location(x, y)
        this.index = index;
        this.x = x;
        this.y = y;
    }

    public double distance(Vertex v){
        return Math.sqrt(Math.pow((x-v.x), 2) + Math.pow((y-v.y), 2));
    }

    public static double distance(Vertex v, Vertex w){
        return Math.sqrt(Math.pow((v.x-w.x), 2) + Math.pow((v.y-w.y), 2));
    }

    public void addNeighbor(Vertex v){
        Edge info = new Edge(index, v.index, distance(v));
        list.add(info);
    }

    public Iterable<Edge> getNeighbors(){
        return list;
    }
}

