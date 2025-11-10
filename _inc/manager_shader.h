#ifndef MANAGER_SHADER_H
#define MANAGER_SHADER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

struct ShaderData
{
    unsigned int program_id;
    unsigned int vertex_shader;
    unsigned int fragment_shader;

    template <typename T>
    void set_uniform(const std::string &name, const T& value)
    {
        if constexpr (std::is_same_v<T, glm::mat4>)
        {
            glUniformMatrix4fv(
                glGetUniformLocation(program_id, name.c_str()),
                1,
                false,
                glm::value_ptr(value)
            );
        }
    }

};

class ManagerShader
{
    public:
        std::unordered_map<std::string, std::shared_ptr<ShaderData>> shaders;
        std::shared_ptr<ShaderData> load_shader_from_file(const std::string path_vertex, const std::string path_fragment);
        std::shared_ptr<ShaderData> load_shader(const std::string& name, const char *vertex_source, const char *fragment_source);
        std::shared_ptr<ShaderData> get_shader(const std::string& name);
        void use_shader(const std::string& name);
        void set_matrix4(unsigned int program, std::string name, const glm::mat4 &matrix);
        void set_integer(unsigned int program, std::string name, int value);
        void set_float(unsigned int program, std::string name, int value);

    private:
        unsigned int compile_shader(unsigned int type, const char *source);
        unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader);
};

#endif
