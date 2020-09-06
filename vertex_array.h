#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
private:
    unsigned int m_ID;
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;
    void Bind() const;
    static void Unbind();
};
