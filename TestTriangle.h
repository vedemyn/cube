#pragma once
#include "GameInterface.h"
#include <GL/glew.h>

class TestTriangle : 
	public GameInterface
{
public:

	virtual void Initialize();
	virtual void Render(float aspectRatio);
	virtual void ClearResources();
	virtual void Update(double deltaTime);

private:
	GLuint m_shaderProgram; //shader programm eben
	GLuint m_vertexBufferObject; //enthalt daten von unseren vertices
	GLuint m_arrayBufferObject; //beinhalted vertexbufferobject, und info wie es zu interpretieren ist (also wie es auf die parameter vom vertexshader gemappt wird
	GLint m_transformLocation; //hinweis dadrauf, wo die transformation vorhanden ist??

	float m_turningAngle; 
};

