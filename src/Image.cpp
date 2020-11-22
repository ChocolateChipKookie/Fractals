//
// Created by kookie on 02/04/2020.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "util/graphics_error.h"

kki::Image::Image(const std::string &image_path, bool flip_on_load, int desired_channels) {
    stbi_set_flip_vertically_on_load(flip_on_load);

    unsigned char* image = stbi_load(image_path.c_str(), &_width, &_height, &_channels, desired_channels);

    if(!image){
        throw kki::graphics_error("Error loading image!");
    }
    if (_channels != 3){
        throw kki::graphics_error("Error loading image, only 3 channels supported!");
    }

    size_t data_size = _width * _height;
    _data.reserve(data_size);
    for(size_t i = 0; i < data_size; ++i) {
        unsigned char* pos = image + (i * _channels);
        _data.emplace_back(
                static_cast<float>(pos[0]) / 255.f,
                static_cast<float>(pos[1]) / 255.f,
                static_cast<float>(pos[2]) / 255.f
                );
    }
    stbi_image_free(image);
}