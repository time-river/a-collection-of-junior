import java.util.*;

interface Shape{
    void draw();
    void erase();
}

class Circle implements Shape {
    public void draw() {
        System.out.println("Calling Circle.draw().");
    }
    public void erase() {
        System.out.println("Calling Circle.erase().");
    }
}

class Square implements Shape {
    public void draw() {
        System.out.println("Calling Square.draw().");
    }
    public void erase() {
        System.out.println("Calling Square.erase().");
    }
}

class Triangle implements Shape {
    public void draw() {
        System.out.println("Calling Triangle.draw().");
    }
    public void erase() {
        System.out.println("Calling Triangle.erase().");
    }
}

public class NewShapes {
    static void drawOneShape(Shape s){
        s.draw();
    }
    static void drawShapes(Shape[] ss){
        for (int i=0; i < ss.length; i++){
            ss[i].draw();
        }
    }

    public static void main(String[] args) {
        Random rand = new Random();
        Shape[] s = new Shape[9];
        for (int i=0; i < s.length; i++) {
            switch(rand.nextInt(3)) {
                case 0: s[i] = new Circle(); break;
                case 1: s[i] = new Square(); break;
                case 2: s[i] = new Triangle(); break;
            }
        }
        drawShapes(s);
    }
}
