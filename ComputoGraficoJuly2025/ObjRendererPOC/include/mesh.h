#pragma once

//#include "glad/glad.h" // holds all OpenGL type declarations
#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
#include "shader.h" // Assuming shader.h is in the same directory
#include "MeshStructs.h"
#include <string>
#include <vector>

// Forward declaration for stb_image
//#include "stb_image.h"

// Function to load a texture using stb_image
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gammaCorrection = false);

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    MaterialProperties materialProperties;
    std::string name;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
        std::vector<Texture> textures, MaterialProperties properties);
    void Draw(Shader& shader);

   
 

private:
    // Render data
    unsigned int VBO, EBO;

    void setupMesh();
};
