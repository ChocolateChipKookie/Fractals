//
// Created by kookie on 18. 11. 2020..
//

#include "gl_types.h"

size_t kki::gl::sizeOfType(kki::gl::type t) {
    switch (t) {
        case BYTE:
        case UNSIGNED_BYTE:                 return 1;
        case SHORT:
        case UNSIGNED_SHORT:
        case HALF_FLOAT:                    return 2;
        case INT:
        case UNSIGNED_INT:
        case FLOAT:
        case FIXED:
        case INT_2_10_10_10_REV:
        case UNSIGNED_INT_2_10_10_10_REV:
        case UNSIGNED_INT_10F_11F_11F_REV:  return 4;
        case DOUBLE:                        return 8;
    }
    throw graphics_error("Type does not exist!");
}
