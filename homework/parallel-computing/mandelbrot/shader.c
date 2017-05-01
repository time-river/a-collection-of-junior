#include "shader.h"

GLuint create_shader(const char *path, GLenum type){
    char *code = NULL, *buf = NULL;
    size_t count = 0, size = sizeof(char)*BUFSIZ;
    FILE *file = NULL;
    int n = 0;

    file = fopen(path, "r");
    if(file == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        goto read_error;
    }

    do{
        buf = (char *)realloc(code, size*(n+1));
        if(buf == NULL){
            free(code);
            goto read_error;
        }
        code = buf;
        memset(code+size*n, 0, size);
        
        count = fread(code+size*n, sizeof(char), BUFSIZ, file);
        n++;
    } while(count == BUFSIZ);

    GLint result;
    GLuint shader;
    GLchar info_log[BUFSIZ];

    shader = glCreateShader(type);
    if(shader == 0){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        goto shader_error;
    }
    glShaderSource(shader, 1, &code, NULL);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result){
        glDeleteShader(shader);
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, info_log);
        goto shader_error;
    }

    free(code);
    return shader;

shader_error:
    free(code);
read_error:
    return 0;
}

GLuint create_program(const GLuint *shader, const int n){
    int result;
    GLuint program;
    char info_log[BUFSIZ];

    program = glCreateProgram();
    if(program == 0){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        goto error;
    
    }
    for(int i=0; i<n; i++)
        glAttachShader(program, shader[i]);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(!result){
        glDeleteProgram(program);
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, info_log);
        goto error;
    }
    return program;
error:
    return 0;
}
