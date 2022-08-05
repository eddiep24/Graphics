#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;
/*
Note: 
OpenGL Shading Language (GLSL)
Window management: GLUT, freeglut, CPW, GLOW, GLUI, GLFW
Extension Library: Glee, GLLoader, GLEW, GL3W, GLAD
Math Library: GLM
Texture Management: Glraw, SOIL2, FreeImage, DevIL, SOIL
Optional: Assimp, tinyobjloader
*/

void init (GLFWwindow* window) {}

void display (GLFWwindow* window, double currentTime)
	{
	
	glClearColor (1.0, 1.0, 0.0, 0.2); // Specify the color placed in the color buffer
	glClear (GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT references the color buffer which we just set.  The buffer is cleared after the call.
	}


int main (void)
	{
	if (!glfwInit ()) { exit (EXIT_FAILURE); }
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow (600, 600, "redWindow", NULL, NULL);
	glfwMakeContextCurrent (window);
	if (glewInit () != GLEW_OK) { exit (EXIT_FAILURE); }
	glfwSwapInterval (1);
	init (window);
	while (!glfwWindowShouldClose (window)) // While the exit button is yet to be pressed
		{
		display (window, glfwGetTime ());
		glfwSwapBuffers (window); // Paints the screen.
		glfwPollEvents (); // Handles window-related events such as a key being pressed
		}
	glfwDestroyWindow (window);
	glfwTerminate ();
	exit (EXIT_FAILURE);
	}