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
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

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

string loadShader(const GLchar * filename) {
    ifstream file(filename);
    string content;

    if (file) {
        string line;
        while (getline(file, line)) {
            content += line + '\n';
        }
    }

    return content;
}

void init(void) {
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

    string vertex_shader_content = loadShader("vertex.glsl");
    const GLchar * vertex_shader_text = vertex_shader_content.c_str();
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    cout << vertex_shader_text;
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    GLint isCompiled = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == 0) {
        PrintShaderErrorLog(vertex_shader);
    }

    // Initialize fragment shader

    string fragment_shader_content = loadShader("fragment.glsl");
    const GLchar * fragment_shader_text = fragment_shader_content.c_str();
    cout << fragment_shader_text;
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