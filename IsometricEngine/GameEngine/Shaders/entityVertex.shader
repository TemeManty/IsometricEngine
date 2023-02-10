#version 330 core

#define CHUNK_WIDTH 16

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 i_textureCoords;
layout (location = 2) in vec4 entityData;

uniform vec3 cameraPos;
uniform int renderDistance;

out vec2 textureCoords;
out float textureIndex;
out float layer;
out float depth;

void main(){
	textureCoords = i_textureCoords;
	textureIndex = entityData.w;
	float layer = entityData.z;

	float scale = cameraPos.z;

	vec2 blockSize = vec2(0.2, 0.2);
	vec2 drawOffset = vec2(((renderDistance * renderDistance) / 2.0), 
						   ((renderDistance * renderDistance) / 2.0));
	vec2 gridCoords = vec2(entityData.x, entityData.y);

	mat2 isometricTransform = mat2(0.5, 0.25, -0.5, 0.25);
	vec2 isomCamera = isometricTransform * vec2(cameraPos.x, cameraPos.y);
	vec2 isomOffset = isometricTransform * drawOffset;
	vec2 isomPos = isometricTransform * (gridCoords);

	depth = (((isomPos.y + 1) - (layer / 6.0)) / (renderDistance * CHUNK_WIDTH));
	
	isomPos = isomPos - isomOffset + isomCamera;


	gl_Position = vec4(
		(vertexPos.x * scale) + (isomPos.x * scale * blockSize.x)  ,
		(vertexPos.y * scale) + (isomPos.y * scale * blockSize.y) + (layer * ((0.2 * scale) / 2.0)),
		0.5, 1.0);

}