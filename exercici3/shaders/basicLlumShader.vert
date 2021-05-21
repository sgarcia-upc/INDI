#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

out vec3 color;

void main()
{	
    color = matdiff;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
