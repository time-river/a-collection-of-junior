/* 
 * Sequential Mandelbrot program:  <16-04-17, river>
 * https://www.tjhsst.edu/~rlatimer/assignments2005/mandelbrot1Glut.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define X_RESN 800
#define Y_RESN 800

void init(void);
void reshape(int width, int height);
void display(void);
void set_pixel(int i, int j, int k, int type, double complex z, double complex c);

static double imax = 2.0, imin = -2.0;
static double rmax = 2.0, rmin = -2.0;
static double escape_radius = 2.0, max_repeats = 100;
static int width = X_RESN, height = Y_RESN;

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
    // Clear the window, select clearing (background) color —— gray
    glClearColor(0.5f, 0.5f, 0.5f, 0.0);

    // Initialize viewing values
    glMatrixMode(GL_PROJECTION); // Select Matrix Mode
    glLoadIdentity();            // Provide Base Matrix
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0); // Set window dimensions

}

void reshape(int width, int height){
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the new viewport size
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    double DCI = (imax - imin) / height;
    double DCR = (rmax - rmin) / width;
    double complex z, c;
    double modulus;
    int i, j, k;

    for(i=0; i<width; i++){
        for(j=0; j<height; j++){
            z = 0.0;
            c = (rmin + i*DCR) + (imin + j*DCR)*I;

            for(k=0, modulus=0.0; modulus<=escape_radius && k<=max_repeats; k++){
                z = cpow(z, 2.0) + c;
                modulus = cabs(z);
            }

            set_pixel(i, j, k, 3, z, c);

        }
    }

    // Flush the buffer to force drawing of all objects thus far
    glFlush();
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
            glBegin(GL_POINTS);
                glVertex3d((GLdouble)i, (GLdouble)j, 0.0);
            glEnd();
            break;
        case 2:
            if(k > max_repeats){
                glColor3f(0.5f, 0.0f, 0.5f);
                glBegin(GL_POINTS);
                    glVertex3d((GLdouble)i, (GLdouble)j, 0.0);
                glEnd();
            }
            else{
                glColor3f((GLfloat)k/(GLfloat)max_repeats, 0.0f, 0.0f);
                glBegin(GL_POINTS);
                    glVertex3d((GLdouble)i, (GLdouble)j, 0.0);
                glEnd();
            }
		    break;	
        case 3:
            if(k > max_repeats){
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_POINTS);
                    glVertex3d((GLdouble)i, (GLdouble)j, 0.0);
                glEnd();
            }
            else{
                float z_real, c_real;
                glColor3f((GLfloat)modff(cabs(z), &z_real), (GLfloat)modff(cabs(c), &c_real), (GLfloat)k/(GLfloat)max_repeats);
                glBegin(GL_POINTS);
                    glVertex3d((GLdouble)i, (GLdouble)j, 0.0);
                glEnd();
            }
			
        }

}


