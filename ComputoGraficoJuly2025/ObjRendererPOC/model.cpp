#include "model.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.h"
#include "shader.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


std::tuple<glm::vec3, glm::vec3> Model::BoundingBox()
{

	glm::vec3 minBB(std::numeric_limits<float>::max());
	glm::vec3 maxBB(std::numeric_limits<float>::lowest());

	for (Mesh& mesh : meshes)
	{
		for (Vertex& vertex : mesh.vertices)
		{
			minBB = glm::min(vertex.Position, minBB);
			maxBB = glm::max(vertex.Position, maxBB);
		}
	}
	
	
	return { minBB,maxBB };

}

glm::vec3 Model::GetCenter()
{
	glm::vec3 minBB, maxBB;
	std::tie(minBB, maxBB) = BoundingBox();

	glm::vec3 Center = ((maxBB + minBB) / 2.0f);

	return Center;
}



Model::Model(std::string const& path, bool gamma) : gammaCorrection(gamma) {
	loadModel(path);
}

void Model::Draw(Shader& shader,glm::mat4 center) {

	if (assimpScene && assimpScene->mRootNode) {
		drawNode(assimpScene->mRootNode, assimpScene, shader, center); // Empezar con matriz identidad
	}
	//for (unsigned int i = 0; i < meshes.size(); i++)
	//    meshes[i].Draw(shader);
}

void Model::drawNode(aiNode* node, const aiScene* scene, Shader& shader, glm::mat4 parentTransform) {
	// Obtiene la matriz de transformación del nodo actual de Assimp
	glm::mat4 nodeTransform;
	// La matriz de Assimp está en fila-mayor, GLM usa columna-mayor. Transponemos.
	nodeTransform = glm::transpose(glm::make_mat4(&node->mTransformation.a1));

	// Combina con la transformación del padre para obtener la transformación global del nodo
	glm::mat4 currentTransform = parentTransform * nodeTransform;

	// Dibuja todas las mallas en este nodo
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		// Asume que las mallas en `this->meshes` tienen el mismo orden que en `scene->mMeshes`
		// y que `node->mMeshes[i]` es el índice en `scene->mMeshes`.
		// Esto es crucial para que `this->meshes[node->mMeshes[i]]` sea la malla correcta.
		// Si `processMesh` simplemente añade mallas al vector sin respetar el índice global de la escena,
		// esto fallará. La forma robusta es que `processMesh` devuelva un `Mesh` y luego
		// `Model` lo guarde en un `std::vector<Mesh>` en el mismo orden que `scene->mMeshes`.

		// Pasa la transformación del nodo a la malla para que la pase al shader
		shader.setMat4("model", currentTransform); // ¡Pasamos la matriz del nodo como la matriz model!
		meshes[node->mMeshes[i]].Draw(shader);
	}

	// Dibuja todos los hijos del nodo recursivamente
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		drawNode(node->mChildren[i], scene, shader, currentTransform);
	}
}

void Model::loadModel(std::string const& path) {
	importer_ptr = std::make_unique<Assimp::Importer>();
	const aiScene* scene = importer_ptr->ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR::ASSIMP::" << importer_ptr->GetErrorString() << std::endl;
		return;
	}
	assimpScene = const_cast<aiScene*>(scene);
	directory = path.substr(0, path.find_last_of('/'));

	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		meshes.push_back(processMesh(scene->mMeshes[i], scene));
	}
	//processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	// Process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	MaterialProperties properties;

	// Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normals
		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) { // Does the mesh contain texture coordinates?
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		// Add other attributes here if defined in Vertex struct (e.g., tangents, bitangents)

		vertices.push_back(vertex);
	}
	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		aiColor3D ambient(0.4f, 0.4f, 0.4f);
		aiColor3D diffuse(0.2f, 0.2f, 0.2f);
		aiColor3D specular(1.0f, 1.0f, 1.0f);
		float shininess = 0.0f;

		aiString aName;
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_NAME, aName))
		{
			properties.name = aName.C_Str();
		}

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, ambient))
		{
		}
		properties.ambient = glm::vec3(ambient.r, ambient.g, ambient.b);

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse))
		{
		}
		properties.diffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.b);

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, specular))
		{
		}
		properties.specular = glm::vec3(specular.r, specular.g, specular.b);

		// Asegúrate de que el valor por defecto sea razonable si no se encuentra el shininess
		if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS || shininess == 0.0f) {
			// Si no tiene shininess o es 0, Asimp usa un valor por defecto de 32.0f
			shininess = 32.0f;
		}
		properties.shininess = shininess;

		// Puedes añadir más propiedades aquí si tu shader las usa
		// Por ejemplo: AI_MATKEY_OPACITY, AI_MATKEY_COLOR_EMISSIVE, etc.
		// Siempre revisa la documentación de Assimp para las claves de material (aiMaterial.h)

		// 1. Diffuse maps
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. Normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal"); // Assimp often stores normal maps as height maps
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. Height maps
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height"); // Assimp often stores ambient maps as height maps
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		//5. Emissive
		std::vector<Texture> emisiveMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
		//6. MetalicRoughness
		//std::vector<Texture> metallicRoughnessMaps = loadMaterialTextures(material,aite)  Checar como se aplica
	}

	Mesh newMesh = Mesh(vertices, indices, textures, properties);
	newMesh.name = mesh->mName.C_Str();
	return newMesh;
}

// Checks all material textures of a given type and loads them if they're not loaded yet.
// The required info is returned as a struct Texture.
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		// Check if texture was already loaded
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one.
				break;
			}
		}
		if (!skip) { // If texture hasn't been loaded yet, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory, gammaCorrection);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // Add to loaded textures
		}
	}
	return textures;
}

