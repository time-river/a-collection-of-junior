#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
//    glShadeModel(GL_FLAT);
}

void triangle(void){
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(5.0f, 5.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(25.0f, 5.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(5.0f, 25.0f);
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    triangle();
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(0.0, 30.0, 0.0, 30.0*(GLdouble)h/(GLdouble)w);
    else
        gluOrtho2D(0.0, 30.0*(GLdouble)w/(GLdouble)h, 0.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
