#version 330 core

in vec3 fcolor;
in vec3 NormSCO;
in vec4 vertexSCO;
in vec4 focusSCO0;
in vec4 focusSCO1;
in vec4 focusSCO2;
in vec4 focusSCOReactor;
out vec4 FragColor;

in vec3 matambFrag;
in vec3 matdiffFrag;
in vec3 matspecFrag;
in float matshinFrag;

uniform vec3 colFocus0;
uniform vec3 colFocus1;
uniform vec3 colFocus2;
uniform vec3 colFocusReactor;
uniform vec3 posFocus0;
uniform vec3 posFocus1;
uniform vec3 posFocus2;
uniform vec3 posFocusReactor;
uniform vec3 llumAmbient;

// Valors per als components que necessitem dels focus de llum

vec3 Lambert (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // colFocus * matdiff * max (0, N*L)
    return colFocus * matdiffFrag * max(0.0, dot (L, NormSCO));
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
    //  matspecFrag * colFocus *  max(0,dot (R,v)^matshinFrag
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    float shine = pow(max(0.0, dot(R, V)), matshinFrag);
    return (matspecFrag * colFocus * shine);
}

void main()
{

    vec4 L0 = focusSCO0 - vertexSCO;
    vec3 Lxyz0 = normalize(L0.xyz);
    vec4 L1 = focusSCO1 - vertexSCO;
    vec3 Lxyz1 = normalize(L1.xyz);
    vec4 L2 = focusSCO2 - vertexSCO;
    vec3 Lxyz2 = normalize(L2.xyz);

    vec4 LR = focusSCOReactor - vertexSCO;
    vec3 LxyzR = normalize(LR.xyz);

    // LLUM AMBIENT
    vec3 amb = llumAmbient * matambFrag;

    // Lambert
    vec3 lam = Lambert (NormSCO, Lxyz0, colFocus0);
    lam = lam + Lambert (NormSCO, Lxyz1, colFocus1);
    lam = lam + Lambert (NormSCO, Lxyz2, colFocus2);
    lam = lam + Lambert (NormSCO, LxyzR, colFocusReactor);

    // Phong
    vec3 phong = Phong (NormSCO, Lxyz0, vertexSCO, colFocus0);
    phong = phong + Phong (NormSCO, Lxyz1, vertexSCO, colFocus1);
    phong = phong + Phong (NormSCO, Lxyz2, vertexSCO, colFocus2);

    vec3 fcolorFrag = amb + lam + phong;
	FragColor = vec4(fcolorFrag,1);
}

