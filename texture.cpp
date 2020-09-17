#include <glad/glad.h>
#include "spdlog/spdlog.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "lib/stb/stb_image.h"

Texture::Texture(const TextureSpec &spec)
        : m_ID(0), m_FilePath(spec.Path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_nChannels(0) {
    m_LocalBuffer = stbi_load(spec.Path.c_str(), &m_Width, &m_Height, &m_nChannels, 0);
    stbi_set_flip_vertically_on_load(spec.FlipImage);
    if (!m_LocalBuffer) {
        spdlog::error("failed to load image file: {}\nReason: {}\n", spec.Path, stbi_failure_reason());
        exit(0);
    }
    // it acts as if it's stateful, I don't have time to investigate that, this is a safe way to reset anything in there
    stbi_set_flip_vertically_on_load(!spec.FlipImage);

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, spec.TargetFormat, m_Width, m_Height, 0, spec.SourceFormat, GL_UNSIGNED_BYTE,
                 m_LocalBuffer);
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
