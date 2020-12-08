#version 130

out vec4 colorOut;

// Variables que se recibiran desde CPU
uniform vec2 screen_size;
uniform vec2 center;
uniform float zoom;

void main()
{
	vec2 c;
	float screen_ratio = screen_size.x/screen_size.y;
	c.x = screen_ratio * (gl_FragCoord.x / screen_size.x - 0.5);
	c.y = (gl_FragCoord.y / screen_size.y - 0.5);
	c.x /= zoom;
	c.y /= zoom;
	c.x += center.x;
	c.y += center.y;

	// CODIFICAR ACA

	float zx = 0.0f;
	float zy = 0.0f;

	float zxnext = zx;
	float zynext = zy;

	for (int i=0; i<1000; i++){

		zxnext = zx*zx - zy*zy + c.x;
		zynext = 2*zy*zx + c.y;
		zx = zxnext;
		zy = zynext;
	}

	float absolute_val = sqrt((zx*zx) + (zy*zy));

	if(absolute_val>0.0f && absolute_val<0.2f){
		colorOut = vec4(0.0f, 1.0f, 0.0f, 1.0f);


	}
	
	else if(absolute_val>0.2f && absolute_val<0.8f){
		colorOut = vec4(0.0f, 0.0f, 1.0, 1.0f);
 
	}else if(absolute_val>0.8&& absolute_val<1.5f){
		colorOut = vec4(0.0f, 0.0f, 0.0f, 1.0f);
 
	}
	else{
		colorOut = vec4(1.0, 0.0f, 0.0f, 1.0f);
 
	}
	
}
