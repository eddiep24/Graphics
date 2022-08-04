#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

// FOR ERROR HANDLING
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
	}

void GLGetError() {
	while (GLenum error = glGetError())
		{
		cout << "Found Error: " << error << endl;
		}
	}

// FOR READING IN SHADER EXTERNAL
string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
		}
	fileStream.close();
	return content;
	}

GLuint createShaderProgram() {
	GLint vertCompiled, fragCompiled, linked;

	string vertShaderStr = readShaderSource("vertShader.glsl");
	string fragShaderStr = readShaderSource("fragShader.glsl");
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vertShaderSrc, nullptr);
	glShaderSource(fShader, 1, &fragShaderSrc, nullptr);
	GLClearError();
	glCompileShader(vShader);
	GLGetError();
	glCompileShader(fShader);
	GLGetError();

	GLuint vfProgram = glCreateProgram();
	GLClearError();
	glAttachShader(vfProgram, vShader);
	GLGetError();
	glAttachShader(vfProgram, fShader);
	GLGetError();

	glLinkProgram(vfProgram);
	return vfProgram;
	}
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	}
void display(GLFWwindow* window, double currentTime) {
	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, 1);
	}
int main(void) {
	cout << "Hello Error" << endl;
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);
	init(window);
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
		}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	}