#version 330

uniform mat4 transformation;

layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 inColor;

out vec3 textureDir;
//out vec2 texCoord;

void main()
{
	gl_Position = transformation * vec4(position, 1.0);
	//texCoord = (position.xy + vec2(1.0, 1.0)) * 0.5; //fur das triangle
	//texCoord = (position.xy + vec2(0.5, 0.5));
	textureDir = position;
}