#version 330 core

in vec3 vertex;
uniform float val;
uniform mat4 TG;

in vec3 colors;
out vec4 out_colors;

void main()  {
    gl_Position = TG * vec4 (vertex * val, 1);
    out_colors = vec4(colors, 1.0);
}
