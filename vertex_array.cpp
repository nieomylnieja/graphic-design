#include <glad/glad.h>
#include "vertex_array.h"

VertexArray::VertexArray() : m_ID(0) {
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray() {
//    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
    Bind();
    vb.Bind();
    unsigned int i = 0;
    for (const auto element : layout.GetElements()) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                              (void *) (size_t) element.offset);
        i++;
    }
}

void VertexArray::Bind() const {
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}
