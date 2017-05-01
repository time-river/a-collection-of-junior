/* - Mandelbrot GLSL Fragment Shader:  <22-04-17, river> -
 * http://nuclear.mutantstargoat.com/articles/sdr_fract/
 * References:
 *   Fast and easy high resolution fractals with a pixel shader
 *     http://nuclear.mutantstargoat.com/articles/sdr_fract/
 *   曼德博集合
 *     https://zh.wikipedia.org/wiki/%E6%9B%BC%E5%BE%B7%E5%8D%9A%E9%9B%86%E5%90%88
 *   欧几里得距离
 *     https://zh.wikipedia.org/wiki/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E8%B7%9D%E7%A6%BB
 *   OPENGL ES SHADING LANGUAGE BUILT-IN FUNCTIONS
 *     http://www.shaderific.com/glsl-functions/
 *   Orbit trap
 *     https://en.wikipedia.org/wiki/Orbit_trap
 */

#version 330 core

layout (location=0) uniform ivec2 canvas;
layout (location=1) uniform vec2  center;
layout (location=2) uniform float scale;
layout (location=3) uniform unint max_iters;

float DCR = 4.0f * scale / canvas.x;
float DCI = 4.0f * scale / canvas.y;
unint iters = max_iters / 2;

void main(void){
    vec3 color;
    vec2 z = (0.0f, 0.0f);
    vec2 c = ();
    vec2 index = (0.0f, 0.0f);
    float modulus, theta;
    int i;

    for(i=-iters; i<=iters && modulus<=2.0f ; i++){
        z = pow(z, index) + c;
        modulus = length(z);
    }

    if(i > iters)
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else{
        n = i + iters;
        theta = atan(z.y/z.x)
        color = ( abs(cos(n*theta)) * modulus,
                  abs(sin(n*theta)) * modulus,
                  modulus
                );
    }
    gl_FragColor = color;
}
