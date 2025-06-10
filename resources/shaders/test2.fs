#version 330 core

out vec4 FragOut;
in vec3 vertexColor;

void main()
{
    FragOut = vec4(vertexColor, 1.0);
}