#version 330 core

out vec4 FragColor;
in vec4 gl_FragCoord;

uniform float x00;
uniform float y00;

void main() {
    // esquerra
	if (gl_FragCoord.x < x00){
        // amunt 
        if (gl_FragCoord.y > y00) {
    		FragColor = vec4(1, 0, 0, 1);
        }
        //abaix
        if (gl_FragCoord.y < y00){
	    	FragColor = vec4(1, 1, 0, 1);
        }

    }
    //dreta
	if (gl_FragCoord.x > x00) {
        // amunt 
        if (gl_FragCoord.y > y00) {
    		FragColor = vec4(0, 0, 1, 1);
        }
        //abaix
        if (gl_FragCoord.y < y00) {
    		FragColor = vec4(0, 1, 0, 1);
        }
    }
}

