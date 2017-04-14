/*
 * http://ycymio.com/blog/2016/03/20/OpenGL-beginner-1/
 * OpenGL入门学习系列集(一)
 */

#include <GL/glut.h>
#include <math.h>

void hello_display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
    glFlush();
}

void circle_display(void){

    const int n = 20;
    const GLfloat R = 0.5f;
    const GLfloat Pi = 3.1415926536f;

    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    //glBegin(GL_POLYGON);
    //glBegin(GL_LINES);
    //glBegin(GL_LINE_STRIP);
    //glBegin(GL_LINE_LOOP);
    glBegin(GL_TRIANGLES);
    for(i=0; i < n; i++){
        GLfloat x = 2 * Pi/n * i;
        glVertex2f(R*cos(x), R*sin(x));
    }
    glEnd();
    glFlush();
}

void star_display(void){
    const GLfloat Pi = 3.1415926536f;

    GLfloat a = 1 / (2 - 2*cos(72*Pi/180));
    GLfloat bx = a * cos(18 * Pi/180);
    GLfloat by = a * sin(18 * Pi/180);
    GLfloat cy = -a * cos(18 * Pi/180);
    GLfloat
        PointA[2] = {0, a},
        PointB[2] = {bx, by},
        PointC[2] = {0.5, cy},
        PointD[2] = {-0.5, cy},
        PointE[2] = {-bx, by};
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    glVertex2fv(PointA);
    glVertex2fv(PointC);
    glVertex2fv(PointE);
    glVertex2fv(PointB);
    glVertex2fv(PointD);
    glEnd();
    glFlush();
}

void point_display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glEnd();
    glFlush();
}

void line_display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x0f0f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, 0.5f);
    glEnd();
    glFlush();
}

void polygon_display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.5f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, 0.0f);
    glEnd();
    glFlush();
}

void stipple_display(void){
    static GLubyte mask[128] =
    {
     0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00,
     0x03, 0x80, 0x01, 0xC0,
     0x06, 0xC0, 0x03, 0x60,
     0x04, 0x60, 0x06, 0x20,
     0x04, 0x30, 0x0C, 0x20,
     0x04, 0x18, 0x18, 0x20,
     0x04, 0x0C, 0x30, 0x20,
     0x04, 0x06, 0x60, 0x20,
     0x44, 0x03, 0xC0, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x44, 0x01, 0x80, 0x22,
     0x66, 0x01, 0x80, 0x66,
     0x33, 0x01, 0x80, 0xCC,
     0x19, 0x81, 0x81, 0x98,
     0x0C, 0xC1, 0x83, 0x30,
     0x07, 0xE1, 0x87, 0xE0,
     0x03, 0x3F, 0xFC, 0xC0,
     0x03, 0x31, 0x8C, 0xC0,
     0x03, 0x3F, 0xFC, 0xC0,
     0x06, 0x64, 0x26, 0x60,
     0x0C, 0xCC, 0x33, 0x30,
     0x18, 0xCC, 0x33, 0x18,
     0x10, 0xC4, 0x23, 0x08,
     0x10, 0x63, 0xC6, 0x08,
     0x10, 0x30, 0x0C, 0x08,
     0x10, 0x18, 0x18, 0x08,
     0x10, 0x00, 0x00, 0x08
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(mask);
    glRectf(-0.5f, -0.5f, 0.0f, 0.0f);
    glDisable(GL_POLYGON_STIPPLE);
    glRectf(0.0f, 0.0f, 0.5f, 0.5f);
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Hello OpenGL!");
    glutDisplayFunc(stipple_display);
    glutMainLoop();
    return 0;
}
