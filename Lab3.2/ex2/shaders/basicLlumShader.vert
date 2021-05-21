#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 matambFrag;
out vec3 matdiffFrag;
out vec3 matspecFrag;
out float matshinFrag;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform vec3 colFocus;
uniform vec3 posFocus;

out vec3 fcolor;
out vec3 NormSCO;
out vec4 vertexSCO;
out vec4 focusSCO;

void main()
{	
    fcolor = matdiff;
    mat3 nMatrix = inverse(transpose(mat3(view * TG)));
    NormSCO = normalize(nMatrix * normal);
    vertexSCO = view * TG * vec4(vertex, 1.0);
    focusSCO = vec4(posFocus, 1.0);

     matambFrag  = matamb;
     matdiffFrag = matdiff;
     matspecFrag = matspec;
     matshinFrag = matshin;
    


    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
