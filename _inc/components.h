#include <memory>
#include <string>
#include <manager_mesh.h>
#include <manager_shader.h>

struct Transform
{
    float x = 0;
    float y = 0;
    float z = 0;
};

struct Velocity
{
    float dx = 0;
    float dy = 0;
    float dz = 0;
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
