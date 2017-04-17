/* Parallel Mandelbrot program using MPICH:  <16-04-17, river> */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <mpi.h>
#include <tgmath.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define TAG 0 // Message from master

#define X_RESN 800
#define Y_RESN 800

static float imax = 2.0, imin = -2.0;
static float rmax = 2.0, rmin = -2.0;
static float escape_radius = 2.0, max_repeats = 200;
static int width = X_RESN, height = Y_RESN;
static int divided_part;

void init_opengl(int *argc, char **argv);
void init(void);
void reshape(int width, int height);
void display(void);
void set_pixel(float i, float j, float k, int type, float z, float c);

void slave_func(void);


int main(int argc, char *argv[]){
    
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    /* parse argv */
    divided_part = world_size;

    switch(world_size){
        case 1:
            fprintf(stderr, "A Master needs at least one slave to satisfy him!\n");
            break;
        default:
            if(world_rank == 0){
                init_opengl(&argc, argv);
            }
            else{
                slave_func();
            }
            break;
    }

    MPI_Finalize();
    return 0;
}

void slave_func(void){
    int buf[2];
    int h = height;

    MPI_Recv(buf, 2, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Recv buf: %d %d\n", buf[0], buf[1]);
    int w = buf[1] - buf[0]; // [buf[0], buf[1])
    int size = 5 * height * w;
    /* 
     * float result[size];
     * error !!
     * 数组太大了，段错误
     */
    float *result = (float *)malloc(sizeof(float)*size);
    if(result == NULL){
        fprintf(stderr, "FILE %s -- LINE %d malloc: %s\n", __FILE__, __LINE__, strerror(errno));
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    float DCR = (rmax - rmin) / width;
    float DCI = (imax - imin) / height;

    float complex z, c;
    float modulus;
    int i, j, k;

    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            z = 0.0f;
            c = (rmin + (i+buf[0])*DCR) + (imin + j*DCI)*I;

            for(k=0, modulus=0.0f; modulus<=escape_radius && k<=max_repeats; k++){
                z = cpowf(z, 2.0f) + c;
                modulus = cabsf(z);
            }

            float integer;
            result[i*height+j*5+0] = (float)(i+buf[0])/width;
            result[i*height+j*5+1] = (float)j/height;
            result[i*height+j*5+2] = (float)k/max_repeats;
            result[j*height+j*5+3] = modff(cabsf(z), &integer);
            result[j*height+j*5+4] = modff(cabsf(c), &integer);
        }
    }
    MPI_Send(result, size, MPI_FLOAT, 0, TAG, MPI_COMM_WORLD);

    printf("send successfully\n");
    free(result);

    return;
}


void init_opengl(int *argc, char **argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mandelbrot Set");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return;
}

void init(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT);

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void){
    int iresult;

    glClear(GL_COLOR_BUFFER_BIT);

    // 静态划分
    int w = width / (divided_part-1);
    int buf[2] = {0};
    for(int rank=1; rank<divided_part; rank++){
        buf[0] = (rank-1) * w;
        buf[1] = rank * w;
        iresult = MPI_Send(&buf, 2, MPI_INT, rank, TAG, MPI_COMM_WORLD);
        if(iresult){
            fprintf(stderr, "FILE %s -- LINE %d MPI_Send: %s\n", __FILE__, __LINE__, strerror(errno));
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    int size = w * height * 5;
    float *result = (float *)malloc(sizeof(float)*size);
    if(result == NULL){
        fprintf(stderr, "FILE %s -- LINE %d malloc: %s\n", __FILE__, __LINE__, strerror(errno));
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    for(int rank=1; rank<divided_part; rank++){
        iresult = MPI_Recv(result, size, MPI_FLOAT, rank, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(iresult){
            fprintf(stderr, "FILE %s -- LINE %d MPI_Recv: %s\n", __FILE__, __LINE__, strerror(errno));
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        printf("Receive successfully\n");

        printf("rank: %d\n", rank);
        for(int i=0; i<w; i++){
            glBegin(GL_POINTS);
            
            for(int j=0; j<height; j++){
                set_pixel(result[i*height+j*5+0],
                        result[i*height+j*5+1],
                        result[i*height+j*5+2],
                        3,
                        result[i*height+j*5+3],
                        result[i*height+j*5+4]);
            }
            glEnd();

            glFlush();
            glutSwapBuffers();
        }
        printf("Swap end\n");
    }

    free(result);
}

void set_pixel(float i, float j, float k, int type, float z, float c){
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
            color = color_table[(int)k%NUMCOLOR];
            glColor3f((GLfloat)color[0]/255, (GLfloat)color[1]/255, (GLfloat)color[2]/255);
            break;
        case 2:
            if(k > max_repeats){
                glColor3f(0.5f, 0.0f, 0.5f);
            }
            else{
                glColor3f(k, 0.0f, 0.0f);
            }
            break;
        case 3: default:
            if(k > max_repeats){
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            else{
                glColor3f(z, c, k);
            }
            break;
    }

    glVertex2f(i, j);
}
