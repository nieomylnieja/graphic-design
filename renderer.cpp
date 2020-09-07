#include "renderer.h"

void Renderer::Draw(const ShaderProgram &program, const VertexArray &va, const ElementBuffer &eb) {
    program.Use();
    va.Bind();
    eb.Bind();
    glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const ShaderProgram &program, const VertexArray &va) {
    program.Use();
    va.Bind();
    glDrawArrays(GL_TRIANGLES, 0, GL_UNSIGNED_INT);
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}
