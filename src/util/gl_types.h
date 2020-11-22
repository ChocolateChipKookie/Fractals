//
// Created by kookie on 18. 11. 2020..
//

#ifndef KOOKIE_ENGINE_GL_TYPES_H
#define KOOKIE_ENGINE_GL_TYPES_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include "graphics_error.h"

namespace kki::gl{
    enum type : GLenum{
        BYTE =              GL_BYTE,
        UNSIGNED_BYTE =     GL_UNSIGNED_BYTE,
        SHORT =             GL_SHORT,
        UNSIGNED_SHORT =    GL_UNSIGNED_SHORT,
        INT =               GL_INT,
        UNSIGNED_INT =      GL_UNSIGNED_INT,
        HALF_FLOAT =        GL_HALF_FLOAT,
        FLOAT =             GL_FLOAT,
        DOUBLE =            GL_DOUBLE,
        FIXED =             GL_FIXED,
        INT_2_10_10_10_REV =            GL_INT_2_10_10_10_REV,
        UNSIGNED_INT_2_10_10_10_REV =   GL_UNSIGNED_INT_2_10_10_10_REV,
        UNSIGNED_INT_10F_11F_11F_REV =  GL_UNSIGNED_INT_10F_11F_11F_REV,
    };

    size_t sizeOfType(type t);
}

#endif //KOOKIE_ENGINE_GL_TYPES_H
