#version 330

//uniform sampler2D baseColor;
uniform samplerCube cubemap;

//in vec2 texCoord;
in vec3 textureDir;
out vec4 FragColor;

void main() 
{
	FragColor = texture(cubemap, textureDir);
	//color = texture(baseColor, texCoord);
	//color = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
}
