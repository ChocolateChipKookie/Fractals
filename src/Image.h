//
// Created by kookie on 02/04/2020.
//

#ifndef MEEGERENGEN_IMAGE_LOADER_H
#define MEEGERENGEN_IMAGE_LOADER_H

#include <string>
#include <glm/vec3.hpp>
#include <vector>

namespace kki{
    class Image {
        std::vector<glm::vec3> _data;
        int _width{}, _height{}, _channels{};
    public:
        explicit Image(const std::string& image_path, bool flip_on_load = true, int desired_channels = 0);

        [[nodiscard]]
        int getWidth() const { return _width; }
        [[nodiscard]]
        int getHeight() const { return _height; }

        inline glm::vec3& at(size_t x, size_t y){ return _data[y * _width + x]; }
        inline glm::vec3& operator()(size_t x, size_t y) { return at(x, y); }

        inline glm::vec3& at(size_t i){ return _data[i]; }
        inline glm::vec3& operator()(size_t i) { return at(i); }


    };
}

#endif //MEEGERENGEN_IMAGE_LOADER_H
