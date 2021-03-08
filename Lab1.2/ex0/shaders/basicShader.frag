#version 330 core

out vec4 FragColor;
in vec4 gl_FragCoord;

void main() {
    FragColor = vec4(1);
    if (gl_FragCoord.x > 354)
    //if (gl_FragCoord.x > int(gl_FragCoord.x)/2)
        FragColor = vec4(0);
}

