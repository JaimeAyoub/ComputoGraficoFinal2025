#pragma once

//#include "glad/glad.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
//#include "assimp/postprocess.h"
#include "mesh.h"
#include "shader.h"
#include <string>
#include <vector>
#include <memory>
#include <tuple>
//#include <iostream>
//#include <map>

class Model {
public:
    // Model data
    std::vector<Texture> textures_loaded; // Stores all textures loaded so far, optimization to ensure textures aren't loaded multiple times.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    aiScene* assimpScene; // Guardar la escena de Assimp para acceder al nodo raíz
    std::tuple<glm::vec3,glm::vec3> BoundingBox();
    glm::vec3 GetCenter();

    Model(std::string const& path, bool gamma = false);
    void Draw(Shader& shader, glm::mat4 center);

private:
    std::unique_ptr<Assimp::Importer> importer_ptr;

    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void drawNode(aiNode* node, const aiScene* scene, Shader& shader, glm::mat4 parentTransform);

    // Checks all material textures of a given type and loads them if they're not loaded yet.
    // The required info is returned as a struct Texture.
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};