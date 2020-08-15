#include "GameInterface.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Collection of test classes.
GameInterface gDummyTest;


GameInterface* gUsedInterface;


GLFWwindow* InitializeSystem()
{
	glfwInit(); //zuerst
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //was fur eine opengl version will ich haben: 3.3 vertex shader und frag vorhanden
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ^
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //will die version haben die barebones ist, keine extras, nicht ruckwarts kompatibel

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Rubiks Cube", nullptr, nullptr); //wir erstellen unser fenster
	glfwMakeContextCurrent(window); //die renderbefehle die hiernach kommen beziehen sich jetzt auf das fenster

	glewExperimental = GL_TRUE; // kann mit opengl function pointern arbeiten?
	glewInit();
	
	gUsedInterface->Initialize();

	return window;
}

void RunCoreloop(GLFWwindow* window)
{
	double lastTime = glfwGetTime();
	double timeDifference = 0.0f;

	//core loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //damit glfw tastendrucke und anderen input behandeln kann

		gUsedInterface->Update(timeDifference);

		int screenWidth, screenHeight;
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight); //brauchen wir um auf grossenaenderungen zu reagieren
		float aspectRatio = (float)screenWidth / (float)screenHeight;
		glViewport(0, 0, screenWidth, screenHeight);
		glEnable(GL_DEPTH_TEST); //tiefentest einschalten
		glDepthFunc(GL_LEQUAL);
		glClearColor(0.39f, 0.58f, 0.92f, 1.0f); //background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gUsedInterface->Render(aspectRatio);
		glfwSwapBuffers(window); //front und back buffer umschalten


		double currentTime = glfwGetTime();
		timeDifference = currentTime - lastTime;
		lastTime = currentTime;
	}
}

void ShutdownSystem()
{
	gUsedInterface->ClearResources();
	glfwTerminate(); //beendet die library
}

int main()
{
	gUsedInterface = &gDummyTest;
	GLFWwindow* window = InitializeSystem();
	RunCoreloop(window);
	ShutdownSystem();
}

