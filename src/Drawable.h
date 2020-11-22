//
// Created by kookie on 20. 11. 2020..
//

#ifndef PIXIES_DRAWABLE_H
#define PIXIES_DRAWABLE_H
#include <memory>
#include "Shader.h"

namespace kki{
    class Drawable{
        virtual void draw(std::shared_ptr<kki::Shader> shader) = 0;
    };
}

#endif //PIXIES_DRAWABLE_H
