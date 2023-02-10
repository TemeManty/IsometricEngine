#version 330 core

uniform sampler2DArray textureArray;

in vec2 textureCoords;
in float textureIndex;
in float layer;
in float depth;

out vec4 FragColor;
out float gl_FragDepth;

void main(){
	if(textureIndex == 0.0){
		//if transparent
		FragColor = vec4(depth, depth, depth, 0.0);
		gl_FragDepth = 1.0;
	}else{
		//texture
		FragColor = texture(textureArray, vec3(textureCoords.xy, textureIndex));

		//set frag depth to 1 for trasparent pixels
		if(FragColor.w == 0.0){
			gl_FragDepth = 1.0;
		}else{
			gl_FragDepth = depth;
		}
	}
	//FragColor = vec4(1.0, 1.0, 1.0, 0.4);
}