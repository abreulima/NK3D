#version 330 core

in vec3 frag_pos;

out vec4 fragColor;

void main(void)
{
    fragColor = vec4(min(1.0, frag_pos.x), min(1.0, frag_pos.y), min(1.0, fragColor.z), 1.0);
}
