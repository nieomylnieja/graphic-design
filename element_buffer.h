#ifndef GRAPHIC_DESIGN_ELEMENT_BUFFER_BUFFER_H
#define GRAPHIC_DESIGN_ELEMENT_BUFFER_BUFFER_H

class ElementBuffer {
private:
    unsigned int m_Count;
public:
    ElementBuffer() = default;
    ElementBuffer(const unsigned int *data, unsigned int count);

    ~ElementBuffer();

    void Bind() const;

    static void Unbind();

    inline unsigned int GetCount() const { return m_Count; }
    unsigned int m_ID;
};

#endif