#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include<iostream>

class Screen
{
public:
	GLFWwindow* window;
	const GLuint width;
	const GLuint heigth;

	Screen(GLuint, GLuint);
	/// <summary>
	/// ��ʾ����
	/// </summary>
	void Display();

	/// <summary>
	/// �����Ƿ�ر�
	/// </summary>
	/// <returns>�Ƿ�ر�</returns>
	bool isClosed();
};

