class VertexBuffer {
private:
    unsigned int m_ID{};
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    static void Unbind();
};
