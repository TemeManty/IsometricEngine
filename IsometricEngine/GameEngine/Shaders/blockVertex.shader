#version 330 core

#define CHUNK_WIDTH 16

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 i_textureCoords;
layout (location = 2) in ivec3 chunkCoords; //chunkX, chunkY, WORLD_HEIGHT
layout (location = 3) in float i_textureIndex;

uniform vec3 cameraPos;
uniform int renderDistance;

out vec2 textureCoords;
out float textureIndex;
out float layer;
out float depth;

void main(){
	textureCoords = i_textureCoords;
	textureIndex = i_textureIndex;

	int layerSize = CHUNK_WIDTH * CHUNK_WIDTH;
	float scale = cameraPos.z;

	int blockNum = gl_InstanceID % layerSize;
	layer = float((gl_InstanceID % (CHUNK_WIDTH * CHUNK_WIDTH * chunkCoords.z)) / layerSize);

	mat2 isometricTransform = mat2(0.5, 0.25, -0.5, 0.25);
	vec2 drawOffset = vec2(((renderDistance * renderDistance) / 2.0), 
						   ((renderDistance * renderDistance) / 2.0));
	vec2 blockSize = vec2(0.2, 0.2); //block size in renderer
	
	vec2 blockCoords = vec2(float(blockNum % CHUNK_WIDTH) + (float(chunkCoords.x) * 16.0), 
							float(blockNum / CHUNK_WIDTH) + (float(chunkCoords.y) * 16.0));
	
	vec2 isomPos = (isometricTransform * (blockCoords));
	depth = (((isomPos.y + 1) - (layer / 6.0)) / (renderDistance * CHUNK_WIDTH));

	vec2 isomOffset = isometricTransform * drawOffset;
	vec2 isomCamera = isometricTransform * vec2(cameraPos.x, cameraPos.y);

	isomPos = isomPos - isomOffset + isomCamera;

	gl_Position = vec4(
		vertexPos.x * scale + (isomPos.x * scale * blockSize.x),
		vertexPos.y * scale + (isomPos.y * scale * blockSize.y) + (layer * ((0.2 * scale) / 2.0)),
		0.5, 1.0);
}