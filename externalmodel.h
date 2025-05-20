#include "mesh.h"
#include <iostream>

class ExternalModel
{
public:
    ExternalModel() = default;
    ExternalModel(string path)
    {
        cout << "£adowanie modelu: " << path << endl;
        loadModel(path);
        cout << "Za³adowano " << meshes.size() << " mesh-y." << endl;
    }
    void Draw(ShaderProgram& shader);
    // model data
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
};

