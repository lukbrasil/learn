/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   helper.h
 * Author: lukbrasil
 *
 * Created on 31 de Agosto de 2018, 22:59
 */

#ifndef HELPER_H
#define HELPER_H

#include "glHeader.h"

#include <string>

namespace Types {
    typedef std::basic_string<GLchar> string;
}

namespace Utils {
    Types::string loadShader(const GLchar * filename);
    void printShaderErrorLog(GLuint shader);
}

namespace Program {
    void init(void);
    void display(void);
}

#endif /* HELPER_H */

