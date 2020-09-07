#include <string>

class Texture {
private:
    unsigned int m_ID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_nChannels;
public:
    explicit Texture(const std::string &path);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    static void Unbind();

    inline int GetWidth() const { return m_Width; };

    inline int GetHeight() const { return m_Height; };
};
