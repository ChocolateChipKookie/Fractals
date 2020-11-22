//
// Created by kookie on 20. 11. 2020..
//

#ifndef PIXIES_PIXIES_H
#define PIXIES_PIXIES_H
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <kki/random.h>
#include "Drawable.h"

namespace kki {

    class Pixies : public Drawable{
    private:
        unsigned _vao{}, _vbo[2]{};
    protected:
        std::vector<glm::vec2> positions;
        std::vector<glm::vec3> colours;
        size_t pixies;
    public:

        Pixies(std::vector<glm::vec2>  vertices, std::vector<glm::vec3>  colours);
        explicit Pixies(size_t count, bool random_start = true);
        Pixies(Pixies& other) = delete;
        ~Pixies();

        void updateBuffer();
        void draw(std::shared_ptr<kki::Shader> shader) override;

        void resetPositions();
        virtual void update(size_t i) = 0;
        void updateAll();
    };
}


#endif //PIXIES_PIXIES_H
