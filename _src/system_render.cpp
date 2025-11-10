
#include <entity.h>
#include <components.h>
#include <systems.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

void SystemRender::update(float dt, std::vector<Entity>& entities)
{
    for (auto& entity : entities)
    {
        if (entity.has_component<Mesh>())
        {
            auto& transform = entity.get_component<Transform>();
            auto& mesh = entity.get_component<Mesh>();
            auto& shader = entity.get_component<Shader>();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::scale(model, transform.scale);
            // rotation

            shader.shader_data->set_uniform<glm::mat4>("model", model);
            shader.shader_data->set_uniform<glm::mat4>("view", model);
            shader.shader_data->set_uniform<glm::mat4>("projection", model);


            glUseProgram(shader.shader_data->program_id);
            glBindVertexArray(mesh.mesh_data->VAO);
            glDrawElements(GL_TRIANGLES, mesh.mesh_data->index_count, GL_UNSIGNED_INT, 0);
        }
    }
}
