#ifndef GRAPHIC_DESIGN_TEXTURE_H
#define GRAPHIC_DESIGN_TEXTURE_H

#include <string>

struct TextureSpec {
    std::string FileName;
    std::string FilePath;
    std::string Type;
    bool FlipImage;
};

class Texture {
private:
    unsigned int m_ID;
    std::string m_FileName;
    std::string m_FilePath;
    std::string m_Type;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_nChannels;

    unsigned int getFormat() const;
public:
    explicit Texture(const TextureSpec &spec);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    static void Unbind();

    inline std::string GetType() const { return m_Type; };
    inline std::string GetFileName() const { return m_FileName; };
};

#endif