#version 330 core

layout (location = 0) in attribute vec3 position;

void main(void){
    gl_Position = vec4(canvas, 1.0f);
}
