#include <tgmath.h>

/* 曼德博集合
 * https://zh.wikipedia.org/wiki/%E6%9B%BC%E5%BE%B7%E5%8D%9A%E9%9B%86%E5%90%88
 */

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

void mandelbrot(double imax, double imin,
        double rmax, double rmin,
        int width, int height,
        double escape_radius, int max_repeats){
    // 复平面
    // DCI -- 单位高度
    // DCR -- 单位宽度
    double DCI = (imax - imin) / height;
    double DCR = (rmax - rmin) / width;
    double complex z, c;
    double modulus;
    int i, j, k;

    for(i=0; i<width; i++){
        for(j=0; j<height; j++){
            z = 0;
            c = (rmin + i*DCR) + (imin + j*DCR)*I;
            for(k=0, modulus=0.0; modulus<=escape_radius && k<=max_repeats; k++){
                z = cpow(z, 2.0) + c;
                modulus = cabs(z);
            }

            if(k > max_repeats){
                //Draw c, Black
            }
            else{
                //Draw c, color(z, c, repeats)
            }
        }
    }
    return; 
}
