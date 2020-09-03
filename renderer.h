#include "vertex_array.h"
#include "shader.h"
#include "index_buffer.h"

class Renderer {
public:
    static void Clear();

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
