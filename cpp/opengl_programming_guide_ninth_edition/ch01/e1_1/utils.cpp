/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "helper.h"

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

Types::string Utils::loadShader(const GLchar * filename) {
    ifstream file(filename);
    Types::string content;

    if (file) {
        Types::string line;
        while (getline(file, line)) {
            content += line + '\n';
        }
    }

    return content;
}

void Utils::printShaderErrorLog(GLuint shader) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar* shaderErrorLog = (GLchar*) malloc(sizeof (GLchar) * (maxLength + 1));

    glGetShaderInfoLog(shader, maxLength, &maxLength, shaderErrorLog);
    shaderErrorLog[maxLength] = '\0';
    printf(shaderErrorLog);

    free(shaderErrorLog);
}

Types::string translateProfileMask(GLint contexProfileMask) {
    switch (contexProfileMask) {
        case GL_FALSE:
            return "undefined";
        case GL_CONTEXT_CORE_PROFILE_BIT:
            return "core";
        case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT:
            return "compatibility";
        default:
            return "unknown";
    }
}

Types::string translateProfileFlags(GLint contexProfileFlags) {
    if (contexProfileFlags) {
        vector<Types::string> flags;

        if (contexProfileFlags & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT) {
            flags.push_back("forward compatible");
        }

        if (contexProfileFlags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            flags.push_back("debug");
        }

        if (contexProfileFlags & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT) {
            flags.push_back("robust memory access");
        }

        if (contexProfileFlags & GL_CONTEXT_FLAG_NO_ERROR_BIT) {
            flags.push_back("no error");
        }

        Types::string result{"unknown"};
        int i = 0;
        for (auto s : flags) {
            if (i++) {
                result += ", " + s;
            } else {
                result = s;
            }
        }

        return result;
    } else {
        return "undefined";
    }
}

void Utils::printContextInfo() {
    GLint major;
    GLint minor;
    const GLubyte * version;
    const GLubyte * vendor;
    const GLubyte * renderer;
    GLint contexProfileMask;
    GLint contexProfileFlags;
    const GLubyte * glslVersion;
    GLint glslVersionCount;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    version = glGetString(GL_VERSION);
    vendor = glGetString(GL_VENDOR);
    renderer = glGetString(GL_RENDERER);
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contexProfileMask);
    glGetIntegerv(GL_CONTEXT_FLAGS, &contexProfileFlags);
    glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &glslVersionCount);

    cout << "[OpenGL context info]"
            << '\n' << "version=" << major << "." << minor
            << '\n' << "string_version=" << version
            << '\n' << "vendor=" << vendor
            << '\n' << "renderer=" << renderer
            << '\n' << "profile_mask=" << contexProfileMask << " (" << translateProfileMask(contexProfileMask) << ")"
            << '\n' << "profile_flags=" << contexProfileFlags << " (" << translateProfileFlags(contexProfileFlags) << ")"
            << '\n' << "glsl_version=" << glslVersion
            << '\n' << "supported_glsl_versions="
            ;

    for (GLuint i = 0; i < glslVersionCount - 1; i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << glGetStringi(GL_SHADING_LANGUAGE_VERSION, i);
    }

    cout.flush();
}
