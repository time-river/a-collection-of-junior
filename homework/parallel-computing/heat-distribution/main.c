/* heat distribution:  <27-05-17, river>
 * reference:
 *  https://www.cs.fsu.edu/~engelen/courses/HPC-2010/Pr3.pdf
 */

#include <mpi.h>
#include <errno.h>
#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define MAXSIZE 82
#define MAXSTEP 2000
#define TEMPERATURE 10

static int update(double *hp, int p, int P, int n, int m, int t);

const char *grayscale10 = " .:-=+*#%@$";

int main(int argc, char *argv[]){
    int p = 0, P = 0;
    double *hp = NULL;
    double maxtemperature = TEMPERATURE;
    int n = MAXSIZE, m = 0;
    int maxstep = MAXSTEP;
    double ts = 0.0, te = 0.0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    if(argc == 2){
        maxtemperature = strtod(argv[1], NULL);
    }
    else if(argc == 3){
        maxtemperature = strtod(argv[1], NULL);
        n = atoi(argv[2]) + 2;
        if(n < 3){
            fprintf(stderr, "Must large than 3\n");
            return 0;
        }
    }
    else if(argc == 4){
        maxtemperature = strtod(argv[1], NULL);
        n = atoi(argv[2]) + 2;
        maxstep = atoi(argv[3]);
        if(n < 3){
            fprintf(stderr, "Must large than 3\n");
            return 0;
        }
    }

    m = (n-2) / P + 2;
    hp = (double *)malloc(sizeof(double)*n*m);

    memset(hp, 0, sizeof(double)*n*m);

    /* | this column: grids[n*i], the initial temperature
     * +----------+-
     * |          |^
     * |          ||m
     * |          ||
     * |          ||
     * |          |v
     * +----------+-
     * |<-------->|
     *   n
     */
    for(int i=0; i < m; i++)
        hp[n*i] = maxtemperature;

    MPI_Barrier(MPI_COMM_WORLD);

    ts = MPI_Wtime(); 

    for(int t=0; t<maxstep; t++){
        if(update(hp, p, P, n, m, t))
            break;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    te = MPI_Wtime();

    if(p == 0){
        int iresult, index; 
        MPI_Status status;

        for(int p=0; p<P; p++){
            if(p != 0){
                iresult = MPI_Recv(hp, n*m, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, &status);
                if(iresult){
                    fprintf(stderr, "FILE %s -- LINE %d MPI_Recv: %s\n", __FILE__, __LINE__, strerror(errno));
                    MPI_Abort(MPI_COMM_WORLD, 1);
                }
            }

            /* notice forced conversion */
            for (int i = 1; i < m-1; i++){
                for (int j = 1; j < n-1; j++){
                    //fprintf(stdout, "%5.1f ", hp[n*i+j]);
                    // notice forced conversion
                    index = (int)(floor(hp[n*i+j] / maxtemperature * strlen(grayscale10)));
                    fprintf(stdout, "%c", grayscale10[index]);
                }
                putchar('\n');
            }
        }
    }
    else{
        MPI_Send(hp, n*m, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    free(hp);

    MPI_Finalize();

    return 0;
}
/*
 * hp -- the point of the array storing grid
 * p  -- the number of process
 * P  -- the size of the processes
 * n  -- the size of the girds' each row
 * m  -- the size of the process' columns assigned, include the columns of each side's redundancy
 * t  -- the number of iteration
 *
 * Grid:
 *  the left row's temperature is perpetual
 *  the right row's temperature is zero
 *
 *   +----------+-
 *   |          |^ ^
 *   |          || | each process' rows: (n-2)/P, indeed, including two redundancing rows, m = (n-2)/P+2
 *   |          || v
 *   |          ||n
 *   |          |v
 *   +----------+-
 *   |<-------->| n
 *
 *  the
 *  Grid[i][j] = hp[n*i+j]
 */
static int update(double *hp, int p, int P, int n, int m, int t){
    int stop = 0;
    double *hnew = NULL;
    MPI_Status status;

    hnew = (double *)alloca(sizeof(double)*n*m);
    memset(hnew, 0, sizeof(double)*n*m);

    if(p == 0 && p < P-1){
        /* +----------+
         * |          |
         * |          |
         * +----------+ -- send to down
         * +----------+ -- recv from down
         */
        MPI_Sendrecv(hp+n*(m-2), n, MPI_DOUBLE, p+1, 0,
                hp+n*(m-1), n, MPI_DOUBLE, p+1, 1, MPI_COMM_WORLD, &status);
    }
    else if(p > 0 && p < P-1){
        /* tag 0: recv from up, send to down
         * tag 1: recv from down, send to up
         *
         *  redundance two rows
         *
         * +----------+  -- tag: 0 recv [0, n) from p-1
         * +----------+  -- tag: 1 send [n, n*2) to p-1
         * |          |
         * +----------+  -- tag: 0 send [n*(m-2), n*(m-1)) to p+1
         * +----------+  -- tag: 1 recv [n*(m-1), n*m) from p+1
         */
        MPI_Sendrecv(hp+n*(m-2), n, MPI_DOUBLE, p+1, 0,
                hp+n*0,     n, MPI_DOUBLE, p-1, 0, MPI_COMM_WORLD, &status);
        MPI_Sendrecv(hp+n*1,     n, MPI_DOUBLE, p-1, 1,
                hp+n*(m-1), n, MPI_DOUBLE, p+1, 1, MPI_COMM_WORLD, &status);
    }
    else if(p > 0 && p == P-1){
        /* +----------+ -- recv from up
         * +----------+ -- send to up
         * |          |
         * |          |
         * +----------+
         */
        MPI_Sendrecv(hp+n*1,     n, MPI_DOUBLE, p-1, 1,
                hp+n*0,     n, MPI_DOUBLE, p-1, 0, MPI_COMM_WORLD, &status);
    }

    for(int i=1; i<m-1; i++)        // row [1, m-1), 0 and m-1 is redundancy
        for(int j=1; j<n-1; j++){    // column [1, n-1), the same as row
            hnew[n*i+j] = 0.25 * (
                    hp[n*(i-1)+j] + // up
                    hp[n*(i+1)+j] + // down
                    hp[n*i+(j-1)] + // left
                    hp[n*i+(j+1)]   // right
                    );
        }

    for (int i = 1; i < m-1; i++)
        for (int j = 1; j < n-1; j++)
            hp[n*i+j] = hnew[n*i+j];

    return stop;
}
