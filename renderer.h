#include "vertex_array.h"
#include "shader.h"
#include "element_buffer.h"
#include "shader_program.h"

class Renderer {
public:
    static void Clear();

    static void Draw(const ShaderProgram &program, const VertexArray &va, const ElementBuffer &eb);
    static void Draw(const ShaderProgram &program, const VertexArray &va, unsigned int count);
};
