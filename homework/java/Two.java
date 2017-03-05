import java.util.Scanner;
import java.io.BufferedInputStream;

public class Two{
    public static void main(String[] args){
        Scanner scanner = null;
        Graph graph = null;

        System.out.println("输入坐标点，用空格分开, 回车结束。");
        while(true){
            scanner = new Scanner(new BufferedInputStream(System.in));

            String[] fileds = scanner.nextLine().trim().split("\\s+");
            int len = fileds.length;
            if(fileds[0].matches("")){
                System.out.println("Bye~");
                break;
            }
            else if(len != 3 && len != 6 && len != 8){
                System.out.println("输入数量错误。");
                continue;
            }

            int[] param = new int[len];
            for(int i=0; i< len; i++)
                param[i] = Integer.parseInt(fileds[i]);

            switch(len){
                case 3:
                    graph = new Graph(param[0], param[1], param[2]);
                    break;
                case 6:
                    graph = new Graph(param[0], param[1], param[2], param[3], param[4], param[5]);
                    break;
                case 8:
                    graph = new Graph(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7]);
                    break;
            }
            
            if(graph == null)
                continue;

            graph.draw();
            System.out.println("Shape: " + Shape.shapeType(graph));
            int[] point = Shape.centerPoint(graph);
            System.out.println("Center point —— x: " + point[0] + " y:" + point[1]);
        }
    }
}

class Shape{
    String shape = new String();

    void draw(){
        if(!shape.matches(""))
            System.out.println(shape);
    }

    static String shapeType(Graph graph){
        String type = new String();

        switch(graph.shape){
            case "Rectangle":
                type = "Rectangle";
                break;
            case "Circle":
                type = "Circle";
                break;
            case "Triangle":
                type = "Triangle";
                break;
        }
        return type;
    }

    static int[] centerPoint(Graph graph){
        int[] point = new int[2];

        switch(graph.shape){
            case "Rectangle":
                point[0] = (graph.x_1 + graph.x_2 + graph.x_3 + graph.x_4) / 4;
                point[1] = (graph.y_1 + graph.y_2 + graph.y_3 + graph.y_4) / 4;
                break;
            case "Circle":
                point[0] = graph.x_1;
                point[1] = graph.y_1;
                break;
            case "Triangle":
                point[0] = (graph.x_1 + graph.x_2 + graph.x_3) / 3;
                point[1] = (graph.y_1 + graph.y_2 + graph.y_3) / 3;
                break;
        }
        return point;
    }
}

class Graph extends Shape{
    int x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, r;

    Graph(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4){
        super.shape = "Rectangle";
        this.x_1 = x_1;
        this.y_1 = y_1;
        this.x_2 = x_2;
        this.y_2 = y_2;
        this.x_3 = x_3;
        this.y_3 = y_3;
        this.x_4 = x_4;
        this.y_4 = y_4;
    }

    Graph(int x, int y, int r){
        super.shape = "Circle";
        this.x_1 = x;
        this.y_1 = y;
        this.r = r;
    }

    Graph(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3){
        super.shape = "Triangle";
        this.x_1 = x_1;
        this.y_1 = y_1;
        this.x_2 = x_2;
        this.y_2 = y_2;
        this.x_3 = x_3;
        this.y_3 = y_3;
    }

    void draw(){
        super.draw();
    }
}
