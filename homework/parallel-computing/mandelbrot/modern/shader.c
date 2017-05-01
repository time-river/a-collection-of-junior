#include "shader.h"

GLint create_shader(const char *path){
    char *code = NULL, *tmp = NULL;
    size_t count = 0;
    FILE *file = NULL;
    int n = 0;

    file = fopen(path, "r");
    if(file == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return -1;
    }

    do{
        tmp = realloc(buf, sizeof(buf)+sizeof(char)*BUFSIZ);
        if(tmp == NULL){
            free(tmp);
            return -1;
        }
        code = tmp;

        count = fread(code+n*BUFSIZ, sizeof(char), BUFSIZ, file);
    }while(count == BUFSIZ);

#ifdef DEBUG
    printf("%s LINE %d:\n"
            "  %s\n", buf);
#endif

    GLint  result;
    GLuint shader;
    GLchar infoLog[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result){
        glDeleteShader(shader);
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return -1;
    }
    return shader;
}

void free_all(const char **ptr, int n){
    for(int i=0; i<n; i++)
        free(ptr[i]);
    return;
}

GLint create_shader(GLenum type, const char *code){
    GLint  result;
    GLuint shader;
    GLchar infoLog[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result){
        glDeleteShader(shader);
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return -1;
    }
    return shader;
}

GLint create_program(const GLuint *shader, const int n){
    int result;
    GLuint program;

    program = glCreateProgram();
    for(int i=0; i<n; i++)
        glAttachShader(program, shader[i]);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(!result){
        glDeleteProgram(program);
        delete_shader(shader, n);
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return -1;
    }
    return program;
}

void delete_shader(const GLuint *shader, int n){
    for(int i=0; i<n; i++)
        glDeleteShader(shader[i]);
}
