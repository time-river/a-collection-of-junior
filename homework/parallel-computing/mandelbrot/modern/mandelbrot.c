/*  Sequential Mandelbrot program with modern OpenGL :  <22-04-17, river> */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key,
        int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]){
    GLFWwindow *window = NULL;

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot", NULL, NULL);
    if(!window){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    char *shader_source[2] = { NULL };
    shader_source[0] = read_all("vertex.glsl");
    if(shader_source[0] == NULL){
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    shader_source[1] = read_all("fragment.glsl");
    if(shader_source[0] == NULL || shader_source[1] == NULL){
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    GLint vertex_shader, fragment_shader; 
    vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
    fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);
    if(shader[0] == -1 || shader[1] == -1){
        free_all(&buf, 2);
        delete_shader(shader, sizeof(shader));
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    GLint program;
    program = create_program(shader, sizeof(shader));
    if(program == -1){
        free_all(&buf, 2);
        delete_shader(shader, sizeof(shader));
        delete_program(program);
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    free_all(&buf, 2);
    delete_shader(shader, sizeof(shader));

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };
    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    
    GLuint vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glUniform2i(0, width, height); // canvas
        glUniform1f(1, 0.0f); // center
        glUniform1f(2, 1.0f); // scale
        glUniform1ui(3, 100); // max_iters

        clClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawElements(GL_POINTS, width*height, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char *description){
    fprintf(stderr, "Error: %s\n", description);
}
