#pragma once

class ElementBuffer {
private:
    unsigned int m_ID;
    unsigned int m_Count;
public:
    ElementBuffer(const unsigned int *data, unsigned int count);

    ~ElementBuffer();

    void Bind() const;

    static void Unbind();

    inline unsigned int GetCount() const { return m_Count; }
};
