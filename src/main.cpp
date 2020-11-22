#include <iostream>
#include <chrono>
#include <thread>
#include "Context.h"
#include "InputMonitor.h"
#include "Shader.h"
#include "Texture.h"
#include "Image.h"
#include <complex>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

class Fractal : public kki::Texture{
private:
    const float _exit{4.f};
protected:
    glm::vec2 min, max;
    kki::InputMonitor& monitor;

public:

    Fractal(int width, int height, const glm::vec2& min, const glm::vec2& max, kki::InputMonitor& monitor)
        : kki::Texture(width, height), min(min), max(max), monitor(monitor)
    {
        updateTexture();
        changed = true;
        monitor.addKeys({
                                GLFW_KEY_A,
                                GLFW_KEY_S,
                                GLFW_KEY_D,
                                GLFW_KEY_W,
                                GLFW_KEY_Q,
                                GLFW_KEY_E
            });
    }

    virtual float calculateDivergence(glm::vec2& input) = 0;

    virtual glm::vec3 calculateColour(float divergence) const{
        return {divergence, divergence, divergence};
    }

    void update() override {
        Texture& tex = *this;
        glm::vec2 distance = max - min;
        glm::vec2 d{distance.x/width, distance.y/height};

        glm::vec2 current = min;
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                float value = calculateDivergence(current);
                at(x, y) = calculateColour(value);
                current.x += d.x;
            }
            current.x = min.x;
            current.y += d.y;
        }
        changed = true;
        updateScene();
        updateParameters();
    }

    virtual void updateScene() {
        if (monitor[GLFW_KEY_A]){
            float inc = (max.x - min.x)/100.f;
            min.x -= inc;
            max.x -= inc;
        }
        if (monitor[GLFW_KEY_D]){
            float inc = (max.x - min.x)/100.f;
            min.x += inc;
            max.x += inc;
        }
        if (monitor[GLFW_KEY_S]){
            float inc = (max.y - min.y)/100.f;
            min.y -= inc;
            max.y -= inc;
        }
        if (monitor[GLFW_KEY_W]){
            float inc = (max.y - min.y)/100.f;
            min.y += inc;
            max.y += inc;
        }
        if (monitor[GLFW_KEY_Q]){
            float inc = (max.y - min.y) * 0.01f;
            min.y -= inc;
            min.x -= inc;
            max.x += inc;
            max.y += inc;
        }
        if (monitor[GLFW_KEY_E]){
            float inc = (max.y - min.y) * 0.01f;
            min.y += inc;
            min.x += inc;
            max.x -= inc;
            max.y -= inc;
        }
    }

    virtual void updateParameters() {}

    void save(const std::string& path = "image.png"){
        size_t data_size = width * height * 3;
        auto* data = new unsigned char[data_size];
        auto* iter = data;
        for (unsigned i = 0; i < width * height; ++i, iter += 3){
            const auto& colour = at(i);
            for(unsigned j = 0; j < 3; ++j){
                iter[j] = static_cast<unsigned char>(colour[j] * 255.f);
            }
        }
        stbi_flip_vertically_on_write(true);
        stbi_write_png(path.c_str(), width, height, 3, data, 3 * width);
        delete [] data;
    }
};

class JuliaFractal : public Fractal{
private:
    glm::vec2 _current{0.28, 0.01};

    size_t _samples{200};
    float _exit{4.f};
public:

    JuliaFractal(int width, int height, size_t samples, kki::InputMonitor& monitor)
            :   Fractal(width, height, {-2.f, -2.f}, {2.f, 2.f}, monitor), _samples(samples)
    {
        updateTexture();
        changed = true;
        monitor.addKeys({GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN});
    }

    float calculateDivergence(glm::vec2& input) override {
        std::complex<float> z{input.x, input.y};
        std::complex<float> c{_current.x, _current.y};
        unsigned iter = 0;

        float abs = 0.f;
        while (abs < _exit && iter < _samples)
        {
            z = z * z + c;
            abs = z.real() * z.real() - z.imag() * z.imag();
            ++iter;

        }
        return static_cast<float>(iter) / static_cast<float>(_samples);
    }

    void updateParameters() override{
        float inc = (max.x - min.x) / 100.f;
        if (monitor[GLFW_KEY_RIGHT]){
            _current.x += inc;
        }
        if (monitor[GLFW_KEY_LEFT]){
            _current.x -= inc;
        }
        if (monitor[GLFW_KEY_UP]){
            _current.y += inc;
        }
        if (monitor[GLFW_KEY_DOWN]){
            _current.y -= inc;
        }
    }

};

class MandelbrotFractal : public Fractal{
private:
    size_t _samples{200};
    const float _exit = 4.f;
public:

    MandelbrotFractal(int width, int height, kki::InputMonitor& monitor)
            :   Fractal(width, height, {-2, -1}, {1, 1}, monitor)
    {
        updateTexture();
        changed = true;
    }

    float calculateDivergence(glm::vec2& input) {
        std::complex<float> val{0.f, 0.f};
        std::complex<float> c{input.x, input.y};
        unsigned iter = 0;

        float abs = 0.f;
        while (abs < _exit && iter < _samples)
        {
            val = val * val + c;
            abs = val.real() * val.real() - val.imag() * val.imag();
            ++iter;

        }
        return static_cast<float>(iter) / static_cast<float>(_samples);
    }
};

int main()
{
    int width               = 600;
    int height              = 400;

    // Duration of frame
    std::chrono::milliseconds frame_len(30);

    // Window init
    kki::Context window(width, height, "Fractals");
    kki::InputMonitor input ({}, window);
    window.bind();

    JuliaFractal fractal(width, height, 100, input);

    // Shaders init
    auto shader = std::make_shared<kki::Shader>("../src/shaders/pixies.glsl");
    auto background_shader = std::make_shared<kki::Shader>("../src/shaders/texture.glsl");
    background_shader->use();

    bool hold = true;
    while (!window.shouldClose())
    {
        auto begin = std::chrono::steady_clock::now();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        fractal.update();
        fractal.draw(background_shader);

        window.swapBuffers();
        auto end = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(frame_len - (end - begin));
        window.resetViewport();
        window.pollEvents();

        if ( input[GLFW_KEY_LEFT_CONTROL] && input[GLFW_KEY_S] ){
            if(!hold){
                fractal.save();
                std::cout << "Image saved!" << std::endl;
                hold = true;
            }
        }
        else{
            hold = false;
        }
    }
    return 0;
}
