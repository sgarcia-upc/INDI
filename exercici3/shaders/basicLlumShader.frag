#version 330 core

in vec3 fcolor;
in vec3 NormSCO;
in vec4 vertexSCO;
in vec4 focusSCO;
out vec4 FragColor;

in vec3 matambFrag;
in vec3 matdiffFrag;
in vec3 matspecFrag;
in float matshinFrag;

uniform vec3 colFocus;
uniform vec3 posFocus;
uniform vec3 llumAmbient;

//vec3 llumAmbient = vec3(0.1,0.1,0.1);

// Valors per als components que necessitem dels focus de llum

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matambFrag;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdiffFrag * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if ((dot(NormSCO,L) < 0) || (matshinFrag == 0))
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshinFrag);
    return (colRes + matspecFrag * colFocus * shine); 
}

void main()
{	
    vec4 L = focusSCO - vertexSCO;
    vec3 Lxyz = normalize(L.xyz);
    vec3 fcolorFrag = Phong (NormSCO, Lxyz, vertexSCO);   
	FragColor = vec4(fcolorFrag,1);	
}

