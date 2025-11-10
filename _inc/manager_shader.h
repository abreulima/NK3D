#ifndef MANAGER_SHADER_H
#define MANAGER_SHADER_H

#include <memory>
#include <string>
#include <unordered_map>

struct ShaderData
{
    unsigned int program_id;
    unsigned int vertex_shader;
    unsigned int fragment_shader;
};

class ManagerShader
{
    public:
        std::unordered_map<std::string, std::shared_ptr<ShaderData>> shaders;
        std::shared_ptr<ShaderData> load_shader_from_file(const std::string path_vertex, const std::string path_fragment);
        std::shared_ptr<ShaderData> load_shader(const std::string& name, const char *vertex_source, const char *fragment_source);
        std::shared_ptr<ShaderData> get_shader(const std::string& name);
        void use_shader(const std::string& name);

    private:
        unsigned int compile_shader(unsigned int type, const char *source);
        unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader);
};

#endif
