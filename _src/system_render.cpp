
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <entity.h>
#include <components.h>
#include <systems.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <iostream>

void SystemRender::update(KEngine *k, float dt, std::vector<Entity>& entities)
{

    float zNear = 0.1f;
    float zFar = 20.f;
    glm::vec3 camera_position;
    glm::vec3 target_position;
    glm::mat4 view;


    auto player = k->entityManager.get_entitiy<Player>();
    if (player)
        target_position= player->get_component<Transform>().position;
    else
        target_position = glm::vec3(0.0f, 0.0f, 0.0f);

    camera_position = glm::vec3(5.0f, 5.0f, 5.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

    view = glm::lookAt(target_position + camera_position, target_position, camera_up);

    float scale = 5.0f;
	float aspect = static_cast<float>(800) / static_cast<float>(600);
	glm::mat4 projection = glm::ortho(-aspect * scale, aspect * scale, -scale, scale, zNear, zFar);

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
            shader.shader_data->set_uniform<glm::mat4>("view", view);
            shader.shader_data->set_uniform<glm::mat4>("projection", projection);

            glUseProgram(shader.shader_data->program_id);
            glBindVertexArray(mesh.mesh_data->VAO);
            glDrawArrays(GL_TRIANGLES, 0, mesh.mesh_data->vertex_count);
        }
        else if(entity.has_component<Sprite>())
        {
            auto& tranform = entity.get_component<Transform>();
            auto& shader = entity.get_component<Shader>();
            auto& sprite = entity.get_component<Sprite>();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, tranform.position);
            model = glm::scale(model, tranform.scale);

            shader.shader_data->set_uniform<glm::mat4>("model", model);
            shader.shader_data->set_uniform<glm::mat4>("projection", projection);
            //set integer

            glUseProgram(shader.shader_data->program_id);

        }
    }
}
