public class Edge{ // Neighboring vertex information, include index(vertex), distance(edge) 
    int v, w;
    double weight;

    public Edge(int v, int w, double weight){
        this.v = v;
        this.w = w;
        this.weight = weight;
    }

    public int from(){
        return v;
    }

    public int to(){
        return w;
    }

    public double weight(){
        return weight;
    }
}
