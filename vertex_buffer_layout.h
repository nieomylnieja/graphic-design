#ifndef GRAPHIC_DESIGN_VERTEX_BUFFER_LAYOUT_BUFFER_H
#define GRAPHIC_DESIGN_VERTEX_BUFFER_LAYOUT_BUFFER_H

#include <vector>
#include <glad/glad.h>
#include "identity.h"
#include "vertex.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    int offset;

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

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename TL>
    void Push(unsigned int count) {
        Push(count, 0, identity<TL>());
    }

    template<typename TL>
    void Push(unsigned int count, int offset) {
        Push(count, offset, identity<TL>());
    }

    inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

    inline void SetStride(unsigned int stride) { m_Stride = stride; };
    inline unsigned int GetStride() const { return m_Stride; }

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

    template<typename TL>
    void Push(unsigned int count, int offset, identity<TL>) {
        static_assert(true, "");
    }

    void Push(unsigned int count, int offset, identity<float>) {
        unsigned int size = VertexBufferElement::SizeOf(GL_FLOAT);
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE, static_cast<int>(offset * size)});
        m_Stride += size * count;
    }

    void Push(unsigned int count, int offset, identity<Vertex>) {
        unsigned int size = sizeof(Vertex);
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE, offset});
        m_Stride = size;
    }

    void Push(unsigned int count, int offset, identity<unsigned int>) {
        unsigned int size = VertexBufferElement::SizeOf(GL_UNSIGNED_INT);
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE, static_cast<int>(offset * size)});
        m_Stride += size * count;
    }

    void Push(unsigned int count, int offset, identity<unsigned char>) {
        unsigned int size = VertexBufferElement::SizeOf(GL_UNSIGNED_BYTE);
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE, static_cast<int>(offset * size)});
        m_Stride += size * count;
    }
};

#endif