#include <vector>
#include "lib/glad/glad.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int SizeOf(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                return 0;
        }
    }
};

template<typename T>
struct identity {
    typedef T type;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename TL>
    void Push(unsigned int count) {
        Push(count, identity<TL>());
    }

    inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

    inline unsigned int GetStride() const { return m_Stride; }

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

    template<typename TL>
    void Push(unsigned int count, identity<TL>) {
        static_assert(true, "");
    }

    void Push(unsigned int count, identity<float>) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::SizeOf(GL_FLOAT) * count;
    }

    void Push(unsigned int count, identity<unsigned int>) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::SizeOf(GL_UNSIGNED_INT) * count;
    }

    void Push(unsigned int count, identity<unsigned char>) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::SizeOf(GL_UNSIGNED_BYTE) * count;
    }
};

