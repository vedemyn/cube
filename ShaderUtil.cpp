#include "ShaderUtil.h"
#include <iostream>
#include <fstream>

GLuint ShaderUtil::CreateShaderProgram(const char* vertexFilename, const char* fragmentFilename)
{
	std::string vertexProgram = LoadFile(vertexFilename); //Lade erst mal die datei rein
	const char* vertexString = vertexProgram.c_str(); //hier brauchen wir den c-string raus
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //erzeuge vertex shader
	glShaderSource(vertexShader, 1, &vertexString, NULL); //binde den string an den erzeugten shader, 1 bedeuted dass da nur ein shader drin ist
	PrintOGlErrors(); //tut was drauf steht
	glCompileShader(vertexShader); //kompiliere den shader
	PrintOGlErrors(); //wieder errors
	int vertCompiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompiled); //schreibe den compilestatus des shaders in vertcompiled rein
	if (vertCompiled != 1) //wenn 1 dann erfolgreich, hier fehler"behandlung"
	{
		std::cout << "Vertex shader error " << std::endl;
		PrintShaderLog(vertexShader);
	}

	//hier praktisch das selbe wie oben nur fur den fragment shader
	std::string fragmentProgram = LoadFile(fragmentFilename);
	const char* fragmentString = fragmentProgram.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentString, NULL);

	PrintOGlErrors();
	glCompileShader(fragmentShader);
	PrintOGlErrors();
	int fragCompiled;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		std::cout << "Fragment Shader error " << std::endl;
		PrintShaderLog(fragmentShader);
	}

	GLuint shaderProgram = glCreateProgram(); //erzeuge ein shader program
	glAttachShader(shaderProgram, vertexShader); //attache vertex shader (zuerst?)
	glAttachShader(shaderProgram, fragmentShader); //attache dann fragment shader
	glLinkProgram(shaderProgram); //das ganze wird hiermit aufgerufen
	PrintOGlErrors(); //fehler konnen auftauchen wenn eingabedaten vom frag nicht zu ausgabe von vert passen
	int linked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked); //wie eben
	if (linked != 1)
	{
		std::cout << "Linking failed: " << std::endl;
		PrintProgramLog(shaderProgram);
	}

	glDeleteShader(vertexShader); //optimierung
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::string ShaderUtil::LoadFile(const char* fileName)
{
	std::string result;
	std::ifstream fileStream(fileName, std::ios::in);
	while (!fileStream.eof())
	{
		std::string line;
		std::getline(fileStream, line);
		result.append(line + "\n");
	}
	fileStream.close();
	return result;
}

void ShaderUtil::PrintShaderLog(GLuint shader)
{
	int memLength;
	int messageLength;
	char* log;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &memLength);
	if (memLength == 0)
		return;
	log = (char*)malloc(memLength);
	glGetShaderInfoLog(shader, memLength, &messageLength, log);
	std::cout << "Shader Info Log: " << log << std::endl;
	free(log);
}

void ShaderUtil::PrintProgramLog(GLuint program)
{
	int memLength;
	int messageLength;
	char* log;

	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &memLength);
	if (memLength == 0)
		return;
	log = (char*)malloc(memLength);
	glGetShaderInfoLog(program, memLength, &messageLength, log);
	std::cout << "Program Info Log: " << log << std::endl;
	free(log);
}

void ShaderUtil::PrintOGlErrors()
{
	int error = glGetError();
	while (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error: " << error << std::endl;
		error = glGetError();
	}
}
