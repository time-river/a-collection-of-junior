#include <tgmath.h>
#include <stdio.h>

#define X_RESN 800
#define Y_RESN 800

static float imax = 2.0, imin = -2.0;
static float rmax = 2.0, rmin = -2.0;
static float escape_radius = 2.0, max_repeats = 100;
static int width = X_RESN, height = Y_RESN;

int main(void){
    float DCI = (imax - imin) / height;
    float DCR = (rmax - rmin) / width;

    float complex z, c;
    float modulus;
    int i, j, k;

    for(i=0; i<width; i++){
        for(j=0; j<height; j++){
            z = 0.0f;
            c = (rmin + i*DCR) + (imin + j*DCI)*I;

            for(k=0, modulus=0.0f; modulus<=escape_radius && k<=max_repeats; k++){
                z = cpowf(z, 2.0f) + c;
                modulus = cabsf(z);
                printf("z.real: %f z.imag: %f z.modulus: %f\n", creal(z), cimag(z), modulus);
            }

        }
    }
    return 0;
}
