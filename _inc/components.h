#include <memory>
#include <string>
#include <manager_mesh.h>
#include <manager_shader.h>
#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

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
