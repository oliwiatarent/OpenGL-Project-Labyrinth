#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shaders/shaderprogram.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>     vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(ShaderProgram& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

class ExternalModel
{
public:
    ExternalModel() = default;
    ExternalModel(string path)
    {
        cout << "Ladowanie modelu: " << path << endl;
        loadModel(path);
        cout << "Zaladowano " << meshes.size() << " mesh-y." << endl;
    }
    void Draw(ShaderProgram& shader);
    // model data
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
