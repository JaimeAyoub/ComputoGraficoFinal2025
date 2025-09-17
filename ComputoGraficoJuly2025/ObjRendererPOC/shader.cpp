#include "shader.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    unsigned int vertex, fragment;
    
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform1i(uniformID, (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform1i(uniformID, value);
}

void Shader::setFloat(const std::string& name, float value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform1f(uniformID, value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform2fv(uniformID, 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform2f(uniformID, x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(uniformID, 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform3f(uniformID, x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform4fv(uniformID, 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniform4f(uniformID, x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix2fv(uniformID, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix3fv(uniformID, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    GLuint uniformID = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(uniformID, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMaterial(const std::string& name, const MaterialProperties& materialProperties) const {
    setVec3("material.ambient", materialProperties.ambient);
    setVec3("material.diffuse", materialProperties.diffuse);
    setVec3("material.specular", materialProperties.specular);
    setFloat("material.shininess", materialProperties.shininess);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
