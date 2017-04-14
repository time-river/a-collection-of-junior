/* GLFW Getting started
 * http://www.glfw.org/docs/latest/quick.html
 */

#include <stdio.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv){

    // Initializing and terminating GLFW
    if(!glfwInit()){ // if(!glfwInit())
    /* On successful initialization, GLFW_TRUE is returned. If an error occurred, GLFW_FALSE is returned.
     * Note that GLFW_TRUE and GLFW_FALSE are and will always be just one and zero
     */
        /* Initialization failed */
    }
    /* When you are done using GLFW, typically just before the application exits, you need to terminate GLFW. */
    glfwTerminate();

    // Setting an error callback
    void error_callback(int error, const char* description){
        fprintf(stderr, "Error: %s\n", description);
    }
    glfwSetErrorCallback(error_callback);
    /* Callback functions must be set, so GLFW knows to call them.
     * The function to set the error callback is one of the few GLFW functions that may be called before initialization
     */

    // Creating a window and context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    /* Require a minimum OpenGL version by setting the GLFW_CONTEXT_VERSION_MAJOR and GLFW_CONTEXT_VERSION_MINOR hints before creation. */
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        /* Window or OpenGL context creation failed */
    }
    /* When a window and context is no longer needed, destroy it. */
    glfwDestroyWindow(window);

    // Making the OpenGL context current
    /* before using OpenGL API */
    glfwMakeContextCurrent(window);

    // Rendering with OpenGL
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Reading the timer
    double time = glfwGetTime();

    // Checking the window close flag
    while (!glfwWindowShouldClose(window))
    {
        /* Keep running */

        // Swapping buffers
        glfwSwapBuffers(window);

        // Processing events
        glfwPollEvents();
    }
}
// Receiving input events
/*
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
glfwSetKeyCallback(window, key_callback);
*/
