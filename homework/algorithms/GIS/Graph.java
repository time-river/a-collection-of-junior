import java.util.ArrayList;

public class Graph{
    int vertexNumber;
    int edgeNumber;
    ArrayList<Vertex> vertexList = new ArrayList<Vertex>();

    public Graph(int vertexNum, int edgeNum){
        this.vertexNumber = vertexNum;
        this.edgeNumber = edgeNum;
    }

    public Vertex getVertex(int index){
        return vertexList.get(index);
    }

    public void addVertex(int index, int x, int y){
        Vertex vertex = new Vertex(index, x, y);
        vertexList.add(vertex);
    }

    public void addEdge(int vIndex, int wIndex){
        Vertex v = vertexList.get(vIndex);
        Vertex w = vertexList.get(wIndex);
        v.addNeighbor(w);
        w.addNeighbor(v); // 无向图
    }
}
