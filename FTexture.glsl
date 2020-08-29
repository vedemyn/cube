#version 330

uniform samplerCube cubemap;

in vec3 textureDir;
in vec3 color;
out vec4 FragColor;

void main() 
{
	FragColor = texture(cubemap, textureDir) * vec4(color, 1.0);
}
