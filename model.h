#include <assimp/scene.h>
#include "mesh.h"
#include "shader_program.h"

class Model {
public:
    explicit Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma) { loadModel(path); }
    ~Model();

    void Draw(ShaderProgram &shader);
private:
    // model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
};
