#ifndef SHADER_H
#define SHADER_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

char *read_all(const char *path);
void  free_all(const char **ptr, int n);

GLint create_shader(GLenum type, const char *code);
GLint create_program(const GLuint *shader, const int n);
void delete_shader(const GLuint *shader, int n);

#endif
