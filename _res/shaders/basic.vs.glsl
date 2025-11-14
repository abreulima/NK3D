#version 330 core

layout(location = 0) in vec3 position;

out vec3 frag_pos;
out vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(void)
{
    frag_pos = vec3(model * vec4(position, 1.0));

    gl_Position = projection * view * vec4(frag_pos, 1.0);
    //gl_Position = vec4(position, 1.0);
}
