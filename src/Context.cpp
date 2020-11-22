//
// Created by kookie on 27/03/2020.
//

#include "Context.h"
#include "util/graphics_error.h"

/////////////////////////////////////////////////////////////////
//  Constructors, destructors and default callback functions   //
/////////////////////////////////////////////////////////////////

kki::Context::Context(int width,
                      int height,
                      const std::string &name,
                      const std::function<void()> &window_hints,
                      const std::function<void()> &window_options) {
    // Init GLFW window
    glfwInit();
    // Set window hints
    window_hints();

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        throw graphics_error{ "Failed to create GLFW window" };
    }

    // Set window
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw graphics_error{ "Failed to create GLFW window" };
    }

    // Set window options
    window_options();
    this->context_ = window;
}

void kki::Context::defaultHints() {
    // Needed window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
}

void kki::Context::defaultOptions() {
}

void kki::Context::applyOptions(const std::function<void()> &window_options) {
    this->bind();
    window_options();
}

void kki::Context::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void kki::Context::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

kki::Context::Context(int width, int height, const std::string &name, bool depth, bool alpha) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        throw graphics_error{ "Failed to create GLFW window" };
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw graphics_error{ "Failed to create GLFW window" };
    }

    glDisable(GL_LIGHTING);
    if(depth){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    if (alpha)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    this->context_ = window;
}

kki::Context::~Context()
{
    glfwDestroyWindow(context_);
}

//
//  Handling functions
//

bool kki::Context::shouldClose() const
{
    return glfwWindowShouldClose(context_);
}

void kki::Context::setShouldClose(bool value) const
{
    glfwSetWindowShouldClose(context_, value);
}

void kki::Context::swapBuffers() const
{
    glfwSwapBuffers(context_);
}

void kki::Context::pollEvents()
{
    glfwPollEvents();
}

void kki::Context::waitEvents(double seconds)
{
    if(seconds < 0.){
        glfwWaitEvents();
    }
    else{
        glfwWaitEventsTimeout(seconds);
    }
}

void kki::Context::setViewport(int width, int height) const {
    glViewport(0, 0, width, height);
}

void kki::Context::resetViewport() const
{
    int width, height;
    glfwGetWindowSize(context_, &width, &height);
    setViewport(width, height);
}

void kki::Context::resize(int width, int height) const
{
    glfwSetWindowSize(context_, width, height);
}

unsigned kki::Context::getWidth() const
{
    int width, height;
    glfwGetWindowSize(context_, &width, &height);
    return width;
}

unsigned kki::Context::getHeight() const
{
    int width, height;
    glfwGetWindowSize(context_, &width, &height);
    return height;
}

void kki::Context::setKeyCallback(void(*function)(GLFWwindow*, int, int, int, int)) const
{
    glfwSetKeyCallback(context_, function);
}

void kki::Context::setResizeCallback(void(*function)(GLFWwindow*, int, int)) const {
    glfwSetFramebufferSizeCallback(context_, function);
}

void kki::Context::bind()
{
    glfwMakeContextCurrent(context_);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void kki::Context::setClearColour(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void kki::Context::setClearColour(const glm::vec4& colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
}

void kki::Context::setClearColour(const glm::vec3& colour) {
    glClearColor(colour.r, colour.g, colour.b, 1.f);
}




