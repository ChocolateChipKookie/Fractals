#type vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColour;

out vec3 colour;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    colour = aColour;
}

#type fragment
#version 330 core
in vec3 colour;
out vec4 FragColor;

void main()
{
    FragColor = vec4(colour, 1.0);
}