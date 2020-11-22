//
// Created by kookie on 28/03/2020.
//

#include "Shader.h"
#include "util/graphics_error.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <vector>
// Included id shader.h
//#include <glad/glad.h>
//#include <map>

void kki::Shader::check_compile_errors(unsigned int shader, flag type)
{
    const unsigned INFO_LEN = 1024;
    char infoLog[INFO_LEN];
    int success;
    int len;
    switch (type) {
        case flag::PROGRAM:
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, INFO_LEN, &len, infoLog);
                std::cout << "ERROR::SHADER LINK ERROR:\n" << infoLog << "\n ------------------------------------------------------- " << std::endl;
            }
            break;
        }
        case flag::INVALID:
        {
            throw kki::graphics_error("Invalid flag!");
        }
        default:
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, INFO_LEN, &len, infoLog);
                std::cout << "ERROR::SHADER COMPILE ERROR:\n";
                switch (type) {
                    case flag::VERTEX:
                        std::cout << "vertex\n";
                        break;
                    case flag::FRAGMENT:
                        std::cout << "fragment\n";
                        break;
                    case flag::GEOMETRY:
                        std::cout << "geometry\n";
                        break;
                }
                std::cout << infoLog << "\n---------------------------------------------------" << std::endl;
            }
            break;
        }
    }
    if (!success) {
        throw kki::graphics_error("Error compiling shader!");
    }
}

kki::Shader::Shader(const std::string& shader_path, bool save_code)
{
    // Fetch code of shader programs
    std::ifstream shader_file(shader_path);

    if(!shader_file.is_open()){
        throw kki::graphics_error{"Error opening shader file!"};
    }

    // If the file is open, load the code
    // Create stringstreams for the shader programs
    std::map<flag, std::stringstream> shader_streams;
    std::set<flag> declared;
    // Set the initial type to invalid
    flag type = INVALID;

    // While the file is not done reading, read line per line
    std::string line;
    while (std::getline(shader_file, line)) {
        // If the line starts with #type, it is the declaration of the shader type
        if(line.find("#type ", 0) == 0){
            // Look at the type of the shader
            if      (line.find("fragment")  == 6) {
                type = flag::FRAGMENT;
            }
            else if (line.find("vertex")    == 6) {
                type = flag::VERTEX;
            }
            else if (line.find("geometry")  == 6) {
                type = flag::GEOMETRY;
            }
//                else if (line.rfind("tesselation") == 6) {
//                    type = flag::TESSELATION;
//                }
//                else if (line.rfind("compute") == 6) {
//                    type = flag::COMPUTE;
//                }
            else {
                // If the type has been declared wrong, throw error
                throw kki::graphics_error{"Shader type declaration invalid, no shader type found!"};
            }
            if (declared.find(type) != declared.end()){
                // If it is a duplicate declaration of a shader, throw error
                throw kki::graphics_error{"Shader type already declared!"};
            }
            // Add type to declared shader types
            declared.insert(type);
        }
        else{
            // If the vector type is declared, add the line to the shader
            if(type != INVALID){
                shader_streams[type] << line << '\n';
            }
        }

    }

    // Create strings for the programs
    for (auto& entry : declared){
        code_[entry]  = shader_streams[entry].str();
    }

    // Create shaders and compile them
    std::vector<unsigned int> shaders;
    shaders.reserve(code_.size());
    for (auto &s : code_) {
        flag shader_type = s.first;
        const char* code = s.second.c_str();
        int len = s.second.size();

        const unsigned int shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, &code, &len);
        glCompileShader(shader);
        check_compile_errors(shader, shader_type);
        shaders.push_back(shader);
    }

    //Link the shader program
    id_ = glCreateProgram();
    for (unsigned int s : shaders){
        glAttachShader(id_, s);
    }
    glLinkProgram(id_);
    check_compile_errors(id_, flag::PROGRAM);

    //Tidy up
    for (unsigned int s : shaders){
        glDeleteShader(s);
    }

    if(!save_code){
        for (auto &entry : code_){
            entry.second.clear();
            entry.second.shrink_to_fit();
        }
    }
}

kki::Shader::~Shader()
{
    glDeleteProgram(id_);
}

void kki::Shader::use() const
{
    glUseProgram(id_);
}

const std::string &kki::Shader::getCode(flag type) {
    return code_[type];
}

int kki::Shader::uniformLocation(const std::string &uniform_name) {
    auto pos = uniform_locations_.find(uniform_name);
    if (pos == uniform_locations_.end()){
        int loc = glGetUniformLocation(id_, uniform_name.c_str());
        uniform_locations_[uniform_name] = loc;
        return loc;
    }
    else{
        return uniform_locations_[uniform_name];
    }
}

void kki::Shader::setBool(const std::string &name, bool value) {
    glUniform1i(uniformLocation(name), static_cast<int>(value));
}

void kki::Shader::setInt(const std::string &name, int value) {
    glUniform1i(uniformLocation(name), static_cast<int>(value));
}

void kki::Shader::setFloat(const std::string& name, float x) {
    glUniform1f(uniformLocation(name), x);
}

void kki::Shader::setFloat(const std::string& name, float x, float y) {
    glUniform2f(uniformLocation(name), x, y);
}

void kki::Shader::setFloat(const std::string& name, float x, float y, float z) {
    glUniform3f(uniformLocation(name), x, y, z);
}

void kki::Shader::setFloat(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(uniformLocation(name), x, y, z, w);
}

void kki::Shader::setFloatVec(const std::string& name, const glm::vec2& values) {
    glUniform2fv(uniformLocation(name), 1, &values[0]);
}

void kki::Shader::setFloatVec(const std::string& name, const glm::vec3& value) {
    glUniform3fv(uniformLocation(name), 1, &value[0]);
}

void kki::Shader::setFloatVec(const std::string& name, const glm::vec4& value) {
    glUniform4fv(uniformLocation(name), 1, &value[0]);
}

void kki::Shader::setFloatMat(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(uniformLocation(name), 1, GL_FALSE, &mat[0][0]);

}

void kki::Shader::setFloatMat(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(uniformLocation(name), 1, GL_FALSE, &mat[0][0]);

}

void kki::Shader::setFloatMat(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, &mat[0][0]);

}

