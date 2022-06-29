#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include<iostream>
#include"Singleton .h"


class Screen :public Singleton<Screen>
{
public:
	GLFWwindow* window;
	int width;
	int heigth;

	Screen(int, int);
	Screen();
	/// <summary>
	/// ��ʾ����
	/// </summary>
	void Display();

	/// <summary>
	/// �����Ƿ�ر�
	/// </summary>
	/// <returns>�Ƿ�ر�</returns>
	bool isClosed();

private:
	void Init();
};
