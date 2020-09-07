#include "lib/glad/glad.h"
#include "spdlog/spdlog.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "lib/stb/stb_image.h"

Texture::Texture(const std::string &path)
        : m_ID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_nChannels(0) {
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_nChannels, 0);
    if (!m_LocalBuffer) {
        spdlog::error("failed to load image file: {}\nReason: {}\n", path, stbi_failure_reason());
        exit(0);
    }

    glGenTextures(1, &m_ID);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    Unbind();

    stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
