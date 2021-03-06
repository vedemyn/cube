#version 330

uniform mat4 transformation;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;

out vec3 textureDir;
out vec3 color;

void main()
{
	gl_Position = transformation * vec4(position, 1.0);
	textureDir = position;
	color = inColor;
}