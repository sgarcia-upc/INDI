#version 330 core

out vec4 FragColor;
in vec4 gl_FragCoord;

void main() {
    // esquerra

    if (int(gl_FragCoord.y) % 20 <= 10) {
	    if (gl_FragCoord.x < 354){
            // amunt 
            if (gl_FragCoord.y > 354) {
        		FragColor = vec4(1, 0, 0, 1);
            }
            //abaix
            if (gl_FragCoord.y < 354){
	        	FragColor = vec4(1, 1, 0, 1);
            }

        }
        //dreta
	    if (gl_FragCoord.x > 354) {
            // amunt 
            if (gl_FragCoord.y > 354) {
        		FragColor = vec4(0, 0, 1, 1);
            }
            //abaix
            if (gl_FragCoord.y < 354){
        		FragColor = vec4(0, 1, 0, 1);
            }
        }
    } else {
        FragColor = vec4(0.5, 0.7, 1.0, 1.0);
    }
}

