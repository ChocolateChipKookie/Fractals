cmake_minimum_required(VERSION 3.16)
project(Fractals)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

include_directories(
        ../kki_util/include
        vendor/stb
        vendor/glad/include
        vendor/FastNoise)

add_executable( Fractals
        src/main.cpp
        vendor/glad/glad.c

        src/Shader.h
        src/Shader.cpp
        src/Context.h
        src/Context.cpp
        src/InputMonitor.h
        src/InputMonitor.cpp


        src/Image.h
        src/Image.cpp

        src/Texture.h
        src/Texture.cpp
        )


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw-3.3.2)
target_link_libraries(Fractals glfw)

add_subdirectory(vendor/glm)
target_link_libraries(Fractals glm)

find_package(OpenGL REQUIRED)
target_link_libraries(Fractals OpenGL::GL)