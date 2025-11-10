#include <cstddef>
#include <manager_shader.h>
#include <memory>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<ShaderData> ManagerShader::load_shader(const std::string& name, const char *vertex_source, const char *fragment_source)
{
    auto shader = std::make_shared<ShaderData>();

    shader->vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    shader->fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    shader->program_id = create_program(shader->vertex_shader, shader->fragment_shader);

    shaders[name] = shader;
    return (shader);
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


void ManagerShader::set_matrix4(unsigned int program, std::string name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(
        glGetUniformLocation(program, name.c_str()),
        1,
        false,
        glm::value_ptr(matrix)
    );
}

void ManagerShader::set_integer(unsigned int program, std::string name, int value)
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void ManagerShader::set_float(unsigned int program, std::string name, int value)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
