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

#include "glHeader.h"
#include "helper.h"

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

    Program::init();
    while (!glfwWindowShouldClose(window)) {
        Program::display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}