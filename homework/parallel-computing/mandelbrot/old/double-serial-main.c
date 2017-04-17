/* 
 * Sequential Mandelbrot program with animation:  <16-04-17, river>
 * https://github.com/Ibrahim-Habib/Parallel-Fractal-Mandelbrot-Set-Visualization
 */

#include <stdio.h>
#include <tgmath.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define X_RESN 800
#define Y_RESN 800

static double imax = 2.0, imin = -2.0;
static double rmax = 2.0, rmin = -2.0;
static double escape_radius = 2.0, max_repeats = 200;
static int width = X_RESN, height = Y_RESN;

void init(void);
void reshape(int width, int height);
void display(void);
void set_pixel(int i, int j, int k, int type, double complex z, double complex c);

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mandelbrot Set");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

void init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    // Initialize viewing values 
    glMatrixMode(GL_PROJECTION); // Select Matrix Mode
    glLoadIdentity();            // Provide Base Matrix
    //glOrtho(0.0, width, 0.0, height, -1.0, 1.0); // Set window dimension
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // Set window dimension
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int width, int height){
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Set transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    double DCI = (imax - imin) / height;
    double DCR = (rmax - rmin) / width;
    double complex z, c;
    double modulus;
    int i, j, k;

    for(i=0; i<width; i++){
        glBegin(GL_POINTS);
        for(j=0; j<height; j++){
            z = 0.0;
            c = (rmin + i*DCR) + (imin + j*DCI)*I;

            for(k=0, modulus=0.0; modulus<=escape_radius && k<=max_repeats; k++){
                z = cpow(z, 2.0) + c;
                modulus = cabs(z);
            }
            set_pixel(i, j, k, 3, z, c);
        }
        glEnd();

        // glFlush(); 可省略
        glutSwapBuffers();
    }
}

void set_pixel(int i, int j, int k, int type, double complex z, double complex c){

#define NUMCOLOR 16
    unsigned short color_table[NUMCOLOR][3] = {
        {255,255,255}, //WHITE
        {0,0,0},       //BLACK
        {255,0,0},     //RED
        {255,255,0},   //YELLOW
        {0,255,0},     //GREEN
        {0,255,255},   //CYAN
        {0,0,255},     //BLUE
        {255,0,255},   //MAGENTA
        {255,128,255}, //AQUAMARINE
        {0,128,0},     //FORESTGREEN
        {200,128,0},   //ORANGE
        {200,0,255},   //MAROON
        {128,128,64},  //BROWN
        {255,128,128}, //PINK
        {255,255,128}, //CORAL
        {128,128,128}  //GRAY
    };
    unsigned short *color;

    switch(type){
        case 1:
            color = color_table[k%NUMCOLOR];
            glColor3f((GLfloat)color[0]/255, (GLfloat)color[1]/255, (GLfloat)color[2]/255);
            break;
        case 2:
            if(k > max_repeats){
                glColor3f(0.5f, 0.0f, 0.5f);
            }
            else{
                glColor3f((GLfloat)k/(GLfloat)max_repeats, 0.0f, 0.0f);
            }
            break;
        case 3: default:
            if(k > max_repeats){
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            else{
                float z_real, c_real;
                glColor3f((GLfloat)modff(cabs(z), &z_real), (GLfloat)modff(cabs(c), &c_real), (GLfloat)k/(GLfloat)max_repeats);
            }
            break;
    }

    float test;
    glVertex2d((GLdouble)i/width, (GLdouble)j/height);
}
