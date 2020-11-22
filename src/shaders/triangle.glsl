#type vertex
#version 330 core
layout (location = 0) in vec2 aPos;
out vec2 pos;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    pos = aPos;
}

#type fragment
#version 330 core
uniform vec3 colour;
in vec2 pos;
out vec4 FragColor;

void main()
{
    FragColor = vec4((pos + 1.0) / 2.0, 0.0, 1.0);
}