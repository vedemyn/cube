#pragma once
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <vector>



class CubieRenderer
{
public:
	void Initialize();
	void Render(const glm::mat4& transformationMatrix); //transformationMatrix gibt uns den mittelpunkt vom cubie
	void ClearResources();
	void SetColors(glm::vec3 left, glm::vec3 right, glm::vec3 up, glm::vec3 down, glm::vec3 front, glm::vec3 back);

	float GetCubieExtension() const { return 2.0f * m_offset; }

private:

	const float m_offset = 0.5f; //praktisch halbe kantenlange: von -offset bis +offset

	void AddSidePosition(int sideType, int direction, std::vector<glm::vec3>& positionArray);
	void AddSideColor(int sideType, int direction, std::vector<glm::vec3>& colorArray);
	void TranscribeToFloatArray(std::vector<glm::vec3>& vecArray, float* floatArray);


	GLuint m_arrayBufferObject;
	GLuint m_vertexBufferObject[2]; //2 weil position UND farbe
	GLuint m_shaderProgram;
	GLint m_transformLocation;
};

