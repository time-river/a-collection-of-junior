#include <stdio.h>  
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
  
int main(int argc, char** argv)  
{  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(100, 100);
    glutCreateWindow("OpenGL Test");
    const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字  
    const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台  
    const GLubyte* OpenGLVersion =glGetString(GL_VERSION); //返回当前OpenGL实现的版本号  
    const GLubyte* Extensions  =glGetString(GL_EXTENSIONS);  
    const GLubyte* gluVersion= gluGetString(GLU_VERSION); //返回当前GLU工具库版本  
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("OpenGL实现厂商的名字：%s\n", name);  
    printf("渲染器标识符：%s\n", biaoshifu);  
    printf("OpenGL实现的版本号：%s\n",OpenGLVersion );  
    printf("OpenGL支持的扩展：%s\n",Extensions );  
    printf("OGLU工具库版本：%s\n", gluVersion);  
    printf("GLSL版本: %s\n", glslVersion);  
    return 0;  
}  
