#ifndef SHADER_H
#define SHADER_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

GLuint create_shader(const char *path, GLenum type);
GLuint create_program(const GLuint *shader, const int n);

#endif
