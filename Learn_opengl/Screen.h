#pragma once
#include<iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
using namespace std;

class Screen
{
public:
	GLFWwindow* window;
	const GLuint width;
	const GLuint heigth;

	Screen(GLuint,  GLuint);
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
