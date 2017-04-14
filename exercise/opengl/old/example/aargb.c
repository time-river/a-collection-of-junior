#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static float rotAngle = 0;

/* Initialize antialiasing for RGBA mode, including alpha
 * blending, hint, and line width. Print out implementation-specific
 * info on line width granularity and width.
 */

void init(void){
    GLfloat values[2];
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
    printf("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n",
            values[0]);
    glGetFloatv(GL_LINE_WIDTH_RANGE, values);
    printf("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n",
            values[0], values[1]);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_)
}
