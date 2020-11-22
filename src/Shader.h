//
// Created by kookie on 28/03/2020.
//

#ifndef MEEGERENGEN_SHADER_H
#define MEEGERENGEN_SHADER_H

#include <string>
#include <glm/matrix.hpp>
#include <glad/glad.h>
#include <map>
#include <unordered_map>

namespace kki{
    class Shader {
    public:
        enum flag{
            INVALID     = -1,
            PROGRAM     = 0,
            VERTEX      = GL_VERTEX_SHADER,
            GEOMETRY    = GL_GEOMETRY_SHADER,
            FRAGMENT    = GL_FRAGMENT_SHADER,
// For newer versions of OpenGL:
//            COMPUTE     = GL_COMPUTE_SHADER,
//            TESSELATION = GL_TESS_CONTROL_SHADER,
//            EVALUATION  = GL_TESS_EVALUATION_SHADER,
        };

        explicit Shader(const std::string& shader_path, bool save_code = false);
        ~Shader();

        unsigned getId() const {return id_;};

        // activate the shader
        void use() const;

        int uniformLocation(const std::string& uniform_name);

        // utility uniform functions
        void setBool(const std::string& name, bool value);
        void setInt(const std::string& name, int value);

        void setFloat(const std::string& name, float x);
        void setFloat(const std::string& name, float x, float y);
        void setFloat(const std::string& name, float x, float y, float z);
        void setFloat(const std::string& name, float x, float y, float z, float w);
        void setFloatVec(const std::string& name, const glm::vec2& values);
        void setFloatVec(const std::string& name, const glm::vec3& values);
        void setFloatVec(const std::string& name, const glm::vec4& values);
        void setFloatMat(const std::string& name, const glm::mat2& mat);
        void setFloatMat(const std::string& name, const glm::mat3& mat);
        void setFloatMat(const std::string& name, const glm::mat4& mat);

        const std::string& getCode(flag type);

    private:
        unsigned int id_;
        std::map<flag, std::string> code_;
        std::unordered_map<std::string, int> uniform_locations_;

        static void check_compile_errors(unsigned int shader, flag type);
    };
}

#endif //MEEGERENGEN_SHADER_H
