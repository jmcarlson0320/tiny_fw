#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "platform.h"

#define MAX_LOG_LENGTH 1024

typedef struct {
    GLenum type;
    const char *filename;
    GLuint shader;
} shader_info;


GLFWwindow *window;


static char *read_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("could not open file: %s\n", filename);
        return NULL;
    }

    // count the bytes in the file
    fseek(fp, 0, SEEK_END);
    int num_bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer;
    buffer = (char *) malloc(num_bytes + 1);

    // read file into buffer
    int bytes_read = fread(buffer, 1, num_bytes, fp);
    fclose(fp);
    if (bytes_read != num_bytes) {
        printf("could not read from file: %s\n", filename);
        return NULL;
    }
    buffer[num_bytes] = '\0';

    return buffer;
}


GLuint load_shaders(shader_info *shaders)
{
    if (!shaders) {
        return 0;
    }

    GLuint program = glCreateProgram();

    shader_info *cur = shaders;
    while (cur->type != GL_NONE) {
        // load src from file
        char *src = read_file(cur->filename);

        // compile shader
        cur->shader = glCreateShader(cur->type);
        glShaderSource(cur->shader, 1, &src, NULL);
        free(src);

        glCompileShader(cur->shader);

        // check compilation status
        GLint success;
        glGetShaderiv(cur->shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLuint shader = cur->shader;
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char *errorLog = malloc(sizeof(char) * maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            printf("%s", errorLog);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
            return 0;
        }

        // add to program
        glAttachShader(program, cur->shader);

        // get next shader_info struct
        cur++;
    }

    GLint success = 0;
    char err_msg[MAX_LOG_LENGTH] = {'\0'};

    // link program
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, MAX_LOG_LENGTH, NULL, err_msg);
        printf("could not link shaders\n%s", err_msg);
        return 0;
    }

    return program;
}

GLuint load_passthrough_shaders()
{
    shader_info info[] = {
        {GL_VERTEX_SHADER, "shaders/default.vert"},
        {GL_FRAGMENT_SHADER, "shaders/default.frag"},
        {GL_NONE, NULL}
    };

    return load_shaders(info);
}

void platform_init()
{
    if (!glfwInit()) {
        printf("could not init glfw\n");
        return;
    }
}


void platform_create_window(int width, int height, int scale)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width * scale, height * scale, "test window", NULL, NULL);
    if (!window) {
        printf("could not create window\n");
        glfwTerminate();
        return;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("could not init glew\n");
        glfwTerminate();
        return;
    }

    int nx, ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint shaderID = load_passthrough_shaders();
    VertexArray quad = generate_quad();
    GLuint textureID = load_texture_data();
    glActiveTexture(GL_TEXTURE0);
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
