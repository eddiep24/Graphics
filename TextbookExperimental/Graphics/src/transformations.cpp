#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include <iostream>
using namespace std;

#define numVAOs 1

float x = 0.0f; // location of triangle on x axis
float inc = 0.01f;
GLuint renderingProgram;
GLuint VAO[numVAOs];


string readShaderSource(string filePath)
{
	string output{};
	ifstream fileStream(filePath);
	string temp{};
	while(getline(fileStream, temp))
	{
		output += temp + '\n';
	}
	return output;
}

GLuint createShaderProgram()
{
	string vertShaderSrc = readShaderSource("res/shaders/transformations/basic.vert");
	string fragShaderSrc = readShaderSource("res/shaders/transformations/basic.frag");

	const char* vertShaderStr = vertShaderSrc.c_str();
	const char* fragShaderStr = fragShaderSrc.c_str();
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vertShaderStr, NULL);
	glShaderSource(fShader, 1, &fragShaderStr, NULL);

	glCompileShader(vShader);
	glCompileShader(fShader);

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}

void init()
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, VAO);
	glBindVertexArray(VAO[0]);
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	
	x += inc; // move the triangle along x axis
	if(x > 1.0f) inc = -0.01f;
	if(x < -1.0f) inc = 0.01f;
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "TRANSFORM"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
	if(!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "transform", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);
	init();
	while(!glfwWindowShouldClose(window))
	{
		
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_FAILURE);
}