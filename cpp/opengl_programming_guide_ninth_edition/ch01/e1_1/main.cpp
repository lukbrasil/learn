/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: luk
 *
 * Created on August 21, 2018, 8:43 PM
 */

#include <GL/gl3w.h>
#include <GL/glcorearb.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

const GLint vaoCount = 1;
GLuint vaos[vaoCount];

void PrintShaderErrorLog(GLuint shader) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* shaderErrorLog = (GLchar*) malloc(sizeof (GLchar) * (maxLength + 1));

    glGetShaderInfoLog(shader, maxLength, &maxLength, shaderErrorLog);
    shaderErrorLog[maxLength] = '\0';
    printf(shaderErrorLog);

    free(shaderErrorLog);
}

void init(void) {
    GLchar const * vertex_shader_text =
        "#version 300 es\r\n"
        "layout (location = 0) in vec4 vPosition;\r\n"
        "void main() {\r\n"
        "  gl_Position = vPosition;\r\n"
        "}\r\n";

    GLchar const * fragment_shader_text =
        "#version 300 es\r\n"
        "precision mediump float;\r\n"
        "layout (location = 0) out vec4 fColor;\r\n"
        "void main() {\r\n"
        "  fColor = vec4(0.5, 0.4, 0.8, 1.0);\r\n"
        "}\r\n";

    const GLint vPosition = 0;

    static GLfloat vertices[][2] = {
        {-0.90, -0.90},
        {0.85, -0.90},
        {-0.90, 0.85},
        {0.90, -0.85},
        {0.90, 0.90},
        {-0.85, 0.90}
    };

    // Initialize buffer

    const GLint buffersCount = 1;
    GLuint buffers[buffersCount];
    glCreateBuffers(buffersCount, buffers);
    glNamedBufferStorage(buffers[0], sizeof (vertices), vertices, 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    // Initialize vao

    glGenVertexArrays(vaoCount, vaos);
    glBindVertexArray(vaos[0]);

    // Initialize vertex shader

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    GLint isCompiled = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == 0) {
        PrintShaderErrorLog(vertex_shader);
    }

    // Initialize fragment shader

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    isCompiled = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == 0) {
        PrintShaderErrorLog(fragment_shader);
    }

    // Initialize program

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == 0) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar * shaderProgramInfoLog = (GLchar*) malloc(sizeof (GLchar) * (maxLength + 1));
        glGetProgramInfoLog(program, maxLength, &maxLength,
            shaderProgramInfoLog);
        shaderProgramInfoLog[maxLength] = '\0';
        printf(shaderProgramInfoLog);
        free(shaderProgramInfoLog);

    }

    glUseProgram(program);

    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, ((void*) 0));
}

void display(void) {
    static const GLfloat bgColor[] = {0.0, 0.0, 0.0, 0.0};

    glClearBufferfv(GL_COLOR, 0, bgColor);
    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

/*
 * 
 */
int main(int argc, char** argv) {
    if (!gl3wInit() || !glfwInit()) {
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    init();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}