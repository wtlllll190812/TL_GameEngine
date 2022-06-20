#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Screen.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

class Camera :public Component
{
public:
	float fov = 120.0f;

	Camera(Screen*, GameObject*);
	~Camera();

	/// <summary>
	/// ��ȡ�۲����
	/// </summary>
	/// <returns>�۲����</returns>
	glm::mat4 GetViewMatrix();

	/// <summary>
	/// ��ȡ͸�Ӿ���
	/// </summary>
	/// <returns>��ȡ͸�Ӿ���</returns>
	glm::mat4 GetProjMatrix();

private:
	Screen* currentScreen;
};
Camera::Camera(Screen* s,GameObject* gameobject) :Component(gameobject), currentScreen(s)
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 position = gameobject->transform->position;
	glm::vec3 front= gameobject->transform->GetFront();
	glm::vec3 up = gameobject->transform->GetUp();
	
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjMatrix()
{
	return glm::perspective(fov, (float)currentScreen->width / (float)currentScreen->heigth, 0.1f, 100.0f);
}

