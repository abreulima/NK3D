
#include <entity.h>
#include <components.h>
#include <systems.h>
#include <GL/glew.h>
#include <cstdio>

void SystemRender::update(float dt, std::vector<Entity>& entities)
{
    for (auto& entity : entities)
    {
        if (entity.has_component<Mesh>())
        {
            auto& mesh = entity.get_component<Mesh>();
            auto& shader = entity.get_component<Shader>();

            glUseProgram(shader.shader_data->program_id);
            glBindVertexArray(mesh.mesh_data->VAO);
            glDrawElements(GL_TRIANGLES, mesh.mesh_data->index_count, GL_UNSIGNED_INT, 0);
        }
    }
}
