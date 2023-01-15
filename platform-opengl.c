#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "platform.h"

GLFWwindow *window;


void platform_init()
{
    if (!glfwInit()) {
        printf("could not init glfw\n");
        return;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwTerminate();
        return;
    }
}


void platform_create_window(int width, int height, int scale)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(width * scale, height * scale, "test window", NULL, NULL);
    if (!window) {
        printf("could not create window\n");
        glfwTerminate();
        return;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwMakeContextCurrent(window);

    int nx, ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*
        load shaders
        create quad
        load texture
    */
}


int platform_get_time()
{
    return 0;
}


void platform_delay(int ticks)
{
}


void platform_user_input(App *app)
{
}


void platform_draw_graphics(struct graphics graphics)
{
}


void platform_shutdown()
{
}
