#include <GLFW/glfw3.h>
#include "view/config.h"
#include "view/operator_handler.h"
#include "model/replace_pattern.h"
int main()
{
	PatternHandler pattern("test/rule.txt");
	pattern.replace();
	OperatorHandler op(pattern.getOps());
	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(
		config::height,
		config::width,
		"Self Similarity Demo",
		nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	// 告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		//get the current width and height of the window,
		//in case the window is resized by the user
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		//Set up the viewport (using the width and height of the window)
		//and clear the screen color buffer.
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		//Set up the camera matrix. Note: further details on the camera model will be discussed in Chapter 3
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, 1.f);
		//void glOrtho(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near,GLdouble far);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//绘制
		op.Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
