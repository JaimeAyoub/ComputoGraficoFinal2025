#pragma once
#include "glm/glm.hpp"
#include <string>

// Structure to define vertex attributes
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // Add other attributes if needed, e.g., Tangent, Bitangent, BoneIDs, Weights
};

// Structure to define texture data
struct Texture {
    unsigned int id;
    std::string type; // e.g., "texture_diffuse", "texture_specular"
    std::string path; // Store path for comparison/debugging
};

struct MaterialProperties {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    glm::vec3 normal;
    float shininess;
    std::string name;
    // Añade otras propiedades que quieras usar, como opacidad, emission, etc.
};