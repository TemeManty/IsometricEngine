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
		FragColor = vec4(depth, depth, depth, 0.0);
		gl_FragDepth = 1.0;
	}else{
		FragColor = texture(textureArray, vec3(textureCoords.xy, textureIndex));
//FragColor = vec4(0.0,0.0,1.0,1.0);
		if(FragColor.w == 0.0){
			gl_FragDepth = 1.0;
		}else{
			gl_FragDepth = depth;
		}
		//FragColor = FragColor * vec4(layer / 5.0, layer / 5.0, layer / 5.0, 1.0);
	}
}