#include "CubieRenderer.h"
#include "ShaderUtil.h"
#include <glm/gtc/type_ptr.hpp>

void CubieRenderer::Initialize()
{
	float floatArray[6 * 6 * 3];
	std::vector<glm::vec3> positionField;
	std::vector<glm::vec3> colorField;

	// Build the cube information
	for (int sideType = 0; sideType < 3; ++sideType)
	{
		for (int direction = -1; direction < 2; direction += 2)
		{
			AddSidePosition(sideType, direction, positionField);
			AddSideColor(sideType, direction, colorField);
		}
	}

	m_shaderProgram = ShaderUtil::CreateShaderProgram("VColor.glsl", "FColor.glsl");
	m_transformLocation = glGetUniformLocation(m_shaderProgram, "transformation");

	glGenVertexArrays(1, &m_arrayBufferObject);
	glGenBuffers(2, m_vertexBufferObject); //wir wollen 2, pos + col


	glBindVertexArray(m_arrayBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[0]);
	TranscribeToFloatArray(positionField, floatArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floatArray), floatArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[1]);
	TranscribeToFloatArray(colorField, floatArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floatArray), floatArray, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CubieRenderer::Render(const glm::mat4& transformationMatrix)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_arrayBufferObject);

	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

	glBindVertexArray(0);
	glUseProgram(0);
}

void CubieRenderer::ClearResources()
{
	glDeleteBuffers(2, m_vertexBufferObject); 
	glDeleteVertexArrays(1, &m_arrayBufferObject);
	glDeleteProgram(m_shaderProgram);
}

void CubieRenderer::AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray)
{
	glm::vec3 cornerPoints[2][2];

	int localXDim = (sideType + 1) % 3;
	int localYDim = (sideType + 2) % 3;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			glm::vec3 localPoint(direction * m_offset);
			localPoint[localXDim] = (2 * i - 1) * m_offset;
			localPoint[localYDim] = (2 * j - 1) * m_offset;
			cornerPoints[i][j] = localPoint;
		}
	}

	positionArray.push_back(cornerPoints[0][0]);
	positionArray.push_back(cornerPoints[1][0]);
	positionArray.push_back(cornerPoints[0][1]);
	positionArray.push_back(cornerPoints[1][0]);
	positionArray.push_back(cornerPoints[0][1]);
	positionArray.push_back(cornerPoints[1][1]);
 }

void CubieRenderer::AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray)
{
	glm::vec3 color = glm::vec3(0.0f);

	if (direction == 1)
	{
		if (sideType == 0)
			//left, orange
			color = glm::vec3(1.0f, 0.349f, 0.0f);
		if (sideType == 1) 
			//up (down actually?), white
			color = glm::vec3(1.0f, 1.0f, 1.0f);
		if (sideType == 2) 
			//back, blue
			color = glm::vec3(0.0f, 0.271f, 0.678f);
	}
	else
	{
		if (sideType == 0)
			//right, red
			color =  glm::vec3(1.0, 0.0, 0.0);//glm::vec3(0.725f, 0.0f, 0.0f);
		if (sideType == 1) 
			//down (up actually), yellow
			color = glm::vec3(1.0f, 0.835f, 0.0f);
		if (sideType == 2) 
			//front, green
			color = glm::vec3(0.0f, 0.608f, 0.282f);
	}

	for (int i = 0; i < 6; ++i)
		colorArray.push_back(color);
}


void CubieRenderer::SetColors(glm::vec3 left, glm::vec3 right, glm::vec3 up, glm::vec3 down, glm::vec3 front, glm::vec3 back)
{
	float floatArray[6 * 6 * 3];
	std::vector<glm::vec3> colorField;
	
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(right);
	}
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(left);
	}
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(down);
	}
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(up);
	}
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(front);
	}
	for (int i = 0; i < 6; i++)
	{
		colorField.push_back(back);
	}



	glBindVertexArray(m_arrayBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[1]);
	TranscribeToFloatArray(colorField, floatArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floatArray), floatArray, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CubieRenderer::TranscribeToFloatArray(std::vector<glm::vec3>& vecArray, float* floatArray)
{
	int writingCounter = 0;
	for (int i = 0; i < 36; ++i)
		for (int coord = 0; coord < 3; ++coord)
		{
			floatArray[writingCounter++] = vecArray[i][coord];
		}
}
