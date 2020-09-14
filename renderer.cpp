#include "renderer.h"

void Renderer::Draw(const ShaderProgram &program, const VertexArray &va, const ElementBuffer &eb) {
    program.Use();
    va.Bind();
    eb.Bind();
    glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const ShaderProgram &program, const VertexArray &va, unsigned int count) {
    program.Use();
    va.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::Clear() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
