#include <cstddef>
#include <GL/glew.h>
#include <manager_shader.h>
#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include <iterator>
#include <string>
#include <fstream>

std::shared_ptr<ShaderData> ManagerShader::load_shader(const std::string& name, const char *vertex_source, const char *fragment_source)
{
    auto shader = std::make_shared<ShaderData>();

    shader->vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    shader->fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    shader->program_id = create_program(shader->vertex_shader, shader->fragment_shader);

    shaders[name] = shader;
    return (shader);
}

std::shared_ptr<ShaderData> ManagerShader::load_shader_from_file(const std::string& name, const std::string path_vertex, const std::string path_fragment)
{

    auto&& stream_vertex = std::ifstream(path_vertex);
    auto&& stream_frag = std::ifstream(path_fragment);

    std::string vertex_source = std::string((std::istreambuf_iterator<char>(stream_vertex)), std::istreambuf_iterator<char>());
    std::string fragment_source = std::string((std::istreambuf_iterator<char>(stream_frag)), std::istreambuf_iterator<char>());

    auto shader = ManagerShader::load_shader(name, vertex_source.c_str(), fragment_source.c_str());
    return shader;
}

std::shared_ptr<ShaderData> ManagerShader::get_shader(const std::string& name)
{
    return shaders.at(name);
}

void ManagerShader::use_shader(const std::string& name)
{
    auto shader = shaders.at(name);
    glUseProgram(shader->program_id);
}

unsigned int ManagerShader::compile_shader(unsigned int type, const char *source)
{
    unsigned int shader;
    int success;
    char info_log[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for erros
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf("Shader compilation error: %s\n", info_log);
    }

    return shader;
}


unsigned int ManagerShader::create_program(unsigned int vertex_shader, unsigned int fragment_shader)
{
    unsigned int id;
    char info_log[512];
    int success;


    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);

    // Check for errors
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return (id);
}
