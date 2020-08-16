#include "TestTriangle.h"
#include "ShaderUtil.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void TestTriangle::Initialize()
{
	m_turningAngle = 0.0f;
	//vertices von dem dreieck, steht senkrecht zur z-achse
	const float positions[] = { -1.0f, -1.0f, 0.0f,
								1.0f, -1.0f, 0.0f,
								0.0f, 1.0f, 0.0f }; 

	//erste was wir anlegen ist das letzte was wir loschen, in ClearResources()
	m_shaderProgram = ShaderUtil::CreateShaderProgram("VSimple.glsl", "FSimple.glsl"); //erstellen hier shader
	m_transformLocation = glGetUniformLocation(m_shaderProgram, "transformation"); //holt die location von transformation

	glGenVertexArrays(1, &m_arrayBufferObject); // erstelle an den adressen die beiden objekte
	glGenBuffers(1, &m_vertexBufferObject);

	//"gl ist state machine, kann sachen binden, dann mit bind(0) wieder freigeben"
	//"macht sinn bind(0) nachdem wir was machen aufzurufen, damit kann man fehler vermeiden"
	glBindVertexArray(m_arrayBufferObject); //binde erst das vertex array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject); //dann den vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); //kopiere die dreieckspositionen in das gl array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //wegen im vshader "layout (location = 0)". Argumente: position, menge von elementen, typ, obs normalisiert wird (auf bereich 0-1) (spater relevant?), stride (wie weit muss ich zwischen 2 positionen weitergehen (da 3 floats, 3x sizeof float)), optional relativer offset
	glEnableVertexAttribArray(0); //explizit die position 0 einschalten beim array (muss bei jeder verwendeten position
	glBindVertexArray(0); //erst vertex array unbinden, sonst wenn andersrum schwierigkeiten
	glBindBuffer(GL_ARRAY_BUFFER, 0); //wie oben reihenfolge wichtig


}

void TestTriangle::Render(float aspectRatio)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_arrayBufferObject); //bindet verhaltniss aus inhalt vom vertexbuffer in assoziation vom shader, als auch buffer selber (?)

	//baue mir eine transformationsmatrix zusammen (perspektivische transf. * lookat)
	glm::mat4 globalTransformation = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f) * 
									glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
									* glm::rotate(glm::mat4(1.0f), m_turningAngle, glm::vec3(0.0f, 0.0f, 1.0f)); //hier noch drehwinkel ran

	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(globalTransformation)); //binde matrix an parameter in meinem vertex shader (deswegen haben wir vorher die transform location ermittelt)
	glDrawArrays(GL_TRIANGLES, 0, 3); //hier zeichnen wir (unindiziert) (es gibt 2 arten) zeichenmodus, anfangsindex, wie viele vertices

	glBindVertexArray(0); //damit spater keine fehler kommen weil wir vergessen was zu binden
	glUseProgram(0);

}


void TestTriangle::ClearResources()
{
	//analog zur erstellung wird alles auch geloscht
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteVertexArrays(1, &m_arrayBufferObject);
	glDeleteProgram(m_shaderProgram);
}

void TestTriangle::Update(double deltaTime)
{
	m_turningAngle += glm::radians(120.0f) * (float) deltaTime; //dreht 120 grad pro sekunde



}
