#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 1

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];


GLuint vLoc, tfLoc, projLoc;
int width, height, displayLoopi;
float aspect;
float timeFactor;
glm::mat4 pMat, vMat, tMat, rMat, mMat, modelViewMatrix;

void setupVertices (void)
    {

    float vertexPositions[108] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
        };
    glGenVertexArrays (1, vao);  // creates VAO and returns the integer ID
    glBindVertexArray (vao[0]);
    glGenBuffers (numVBOs, vbo);  // creates VBO and returns the integer ID

    glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);

    // loads the cube vertices into the 0th VBO buffer
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertexPositions), vertexPositions, GL_STATIC_DRAW);
    }

// once
void init (GLFWwindow* window)
    {
    renderingProgram = Utils::createShaderProgram (
        "res/shaders/squares/basic.vert",
        "res/shaders/squares/basic.frag");

    glfwGetFramebufferSize (window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective (1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians == 60 degrees

    // position the camera further down the positive Z axis (to see all of the cubes)
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 32.0f;
    setupVertices ();
    }

// repeatedly
void display (GLFWwindow* window, double currentTime)
    {
    glClear (GL_DEPTH_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glUseProgram (renderingProgram);

    vMat = glm::translate (glm::mat4 (1.0f), glm::vec3 (-cameraX, -cameraY, -cameraZ));

    vLoc = glGetUniformLocation (renderingProgram, "v_matrix");
    projLoc = glGetUniformLocation (renderingProgram, "proj_matrix");

    glUniformMatrix4fv (vLoc, 1, GL_FALSE, glm::value_ptr (vMat));
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (pMat));


    timeFactor = ((float)currentTime);
    tfLoc = glGetUniformLocation (renderingProgram, "tf");
    glUniform1f (tfLoc, (float)timeFactor);

    glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer (0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray (0);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    glDrawArraysInstanced (GL_TRIANGLES, 0, 36, 500);
    }


int main (void)
    {
    if (!glfwInit ()) { exit (EXIT_FAILURE); }
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow (600, 600, "Squares", nullptr, nullptr);
    glfwMakeContextCurrent (window);
    if (glewInit () != GLEW_OK) { exit (EXIT_FAILURE); }
    glfwSwapInterval (1);

    init (window);

    while (!glfwWindowShouldClose (window)) // rate that display gets called is the frame rate
        {
        display (window, glfwGetTime ());
        glfwSwapBuffers (window);
        glfwPollEvents ();
        }

    glfwDestroyWindow (window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
    }