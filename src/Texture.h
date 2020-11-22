//
// Created by kookie on 20. 11. 2020..
//

#ifndef PIXIES_TEXTURE_H
#define PIXIES_TEXTURE_H

#include "Drawable.h"
#include <vector>
#include <glm/vec3.hpp>

namespace kki{
    class Texture : public Drawable{
    private:
        unsigned _texture{0};
        unsigned _vao{}, _vbo{}, _ebo{};
        //                  Positions       Texture coords
        float vertices[16]={ -1.f, -1.f,     0.f, 0.f,
                             1.f, -1.f,     1.f, 0.f,
                             1.f,  1.f,     1.f, 1.f,
                             -1.f,  1.f,     0.f, 1.f};
        unsigned indeces[6] = {0, 1, 2, 0, 2, 3};

    protected:
        std::vector<glm::vec3> texture_data;
        size_t width;
        size_t height;
        bool changed = false;
    public:

        Texture(int width, int height);
        Texture(Texture& other) = delete;

        ~Texture();

        [[nodiscard]]
        size_t getWidth() const { return width; }
        [[nodiscard]]
        size_t getHeight() const { return height; }

        inline glm::vec3& at(size_t x, size_t y){ return texture_data[y * width + x]; }
        inline glm::vec3& operator()(size_t x, size_t y) { return at(x, y); }

        inline glm::vec3& at(size_t i){ return texture_data[i]; }
        inline glm::vec3& operator()(size_t i) { return at(i); }


        virtual void update() = 0;
        void updateTexture();

        void draw(std::shared_ptr<kki::Shader> shader) override;
    };
}


#endif //PIXIES_TEXTURE_H
