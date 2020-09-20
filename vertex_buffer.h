#ifndef GRAPHIC_DESIGN_VERTEX_BUFFER_H
#define GRAPHIC_DESIGN_VERTEX_BUFFER_H

class VertexBuffer {
private:
    unsigned int m_ID{};
public:
    inline VertexBuffer() = default;;
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    static void Unbind();
};

#endif