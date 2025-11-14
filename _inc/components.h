#include "glm/fwd.hpp"
#include <memory>
#include <string>
#include <manager_mesh.h>
#include <manager_shader.h>
#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation;

    Transform(  float p_x, float p_y, float p_z,
                float s_x = 1.0f, float s_y = 1.0f, float s_z = 1.0f)
        : position(glm::vec3(p_x, p_y, p_z)), scale(glm::vec3(s_x, s_y, s_z)) {}

};

struct Player {};
struct Camera {};
struct Keyboard {};

struct Velocity
{
    glm::vec3 velocity;
};

struct Mesh
{
    std::shared_ptr<MeshData> mesh_data;
    std::string mesh_name;

    Mesh(std::shared_ptr<MeshData> mesh_ptr, const std::string& name = "")
        : mesh_data(mesh_ptr), mesh_name(name) {}

};

struct Shader
{
    std::shared_ptr<ShaderData> shader_data;
    std::string shader_name;

    Shader(std::shared_ptr<ShaderData> shader_ptr, const std::string& name = "")
        : shader_data(shader_ptr), shader_name(name) {}
};


struct Sprite {
    std::string path;
};
