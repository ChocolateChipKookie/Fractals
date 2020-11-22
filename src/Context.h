//
// Created by kookie on 27/03/2020.
//

#ifndef MEEGERENGEN_CONTEXT_H
#define MEEGERENGEN_CONTEXT_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <functional>

namespace kki{
    class Context {
    private:
        static void defaultHints();
        static void defaultOptions();

    public:

        // Context using custom window hints and options
        Context(
                int width,
                int height,
                const std::string& name,
                const std::function<void()>& window_hints = defaultHints,
                const std::function<void()>& window_options = defaultOptions);
        // Windowed context
        Context(int width, int height, const std::string& name, bool depth, bool alpha);
        // Destructor
        ~Context();

        // Apply options
        void applyOptions(const std::function<void()>& window_options);

        [[nodiscard]] bool shouldClose() const;

        void setKeyCallback(void(*function)(GLFWwindow*, int, int, int, int)) const;
        void setResizeCallback(void(*function)(GLFWwindow*, int, int)) const;
        void setShouldClose(bool value) const;
        void swapBuffers() const;
        void pollEvents();
        //Blocks thread, waits for seconds amount of seconds for new event
        //Unblocks when event occurs
        //If seconds is < 0 it blocks the thread completly
        void waitEvents(double seconds = -1.);
        void setViewport(int width, int height) const;
        void resetViewport() const;
        void resize(int width, int height) const;
        [[nodiscard]] unsigned getWidth() const;
        [[nodiscard]] unsigned getHeight() const;
        void bind();

        void setClearColour(float r, float g, float b, float a = 1.f);
        void setClearColour(const glm::vec4& colour);
        void setClearColour(const glm::vec3& colour);

    private:

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        GLFWwindow* context_{nullptr};
    };
}





#endif //MEEGERENGEN_CONTEXT_H
