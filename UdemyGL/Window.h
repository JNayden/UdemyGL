#pragma once
#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


class Window
{
public:
	Window();
	Window(int windowWidth, int windowHeight);

	int Initialise();

	float getBufferWidth() { return bufferWidth; }
	float getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;
	int width, height;
	int bufferWidth, bufferHeight;
};

