#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <spdlog/spdlog.h>
#include "model.h"
#include "lib/stb/stb_image.h"

void Model::Draw(ShaderProgram &shaderProgram) {
    for (auto &mesh : meshes)
        mesh.Draw(shaderProgram);
}

Model::~Model() = default;

void Model::loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_FlipUVs |
                                             aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        spdlog::error("Assimp error: {}", importer.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};
        vertex.Position = assimpToGlmVector(mesh->mVertices[i]);
        if (mesh->HasNormals()) {
            vertex.Normal = assimpToGlmVector(mesh->mNormals[i]);
        }
        if (mesh->mTextureCoords[0]) {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vertex.TexCoords = assimpToGlmVector(mesh->mTextureCoords[0][i]);
            vertex.Tangent = assimpToGlmVector(mesh->mTangents[i]);
            vertex.Bitangent = assimpToGlmVector(mesh->mBitangents[i]);
        } else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString filename;
        mat->GetTexture(type, i, &filename);
        bool loaded = false;
        for (auto &j : textures_loaded) {
            if (std::strcmp(j.GetFileName().data(), filename.C_Str()) == 0) {
                textures.push_back(j);
                loaded = true;
                break;
            }
        }
        if (!loaded) {
            Texture texture({filename.C_Str(), directory, getNameFromTextureType(type), true});
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

std::string Model::getNameFromTextureType(aiTextureType type) {
    switch (type) {
        case aiTextureType_DIFFUSE:
            return "texture_diffuse";
        case aiTextureType_SPECULAR:
            return "texture_specular";
        case aiTextureType_HEIGHT:
            return "texture_height";
        case aiTextureType_AMBIENT:
            return "texture_normal";
        default:
            spdlog::error("aiTextureType {} is not implemented", type);
            return "texture_unknown";
    }
}

glm::vec3 Model::assimpToGlmVector(aiVector3t<ai_real> aiVec) {
    glm::vec3 glmVec;
    glmVec.x = aiVec.x;
    glmVec.y = aiVec.y;
    glmVec.z = aiVec.z;
    return glmVec;
}

glm::vec2 Model::assimpToGlmVector(aiVector2t<ai_real> aiVec) {
    glm::vec2 glmVec;
    glmVec.x = aiVec.x;
    glmVec.y = aiVec.y;
    return glmVec;
}
