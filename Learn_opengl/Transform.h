#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Component.h"

class GameObject;
class Transform :public Component
{
public:
	static const  glm::vec3 forward;
	static const  glm::vec3 back;
	static const  glm::vec3 left;
	static const  glm::vec3 right;
	static const  glm::vec3 up;
	static const  glm::vec3 down;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(GameObject*);
	Transform(glm::vec3, GameObject*);
	~Transform();

	/// <summary>
	/// ��ȡ��ǰ����
	/// </summary>
	glm::vec3 GetFront();

	/// <summary>
	/// ��ȡ���ҷ���
	/// </summary>
	glm::vec3 GetRight();

	/// <summary>
	/// ��ȡ���Ϸ���
	/// </summary>
	glm::vec3 GetUp();

	/// <summary>
	/// ��ǰ�ƶ�
	/// </summary>
	void Translate(float);

	/// <summary>
	/// ��ĳ�������ƶ�
	/// </summary>
	/// <param name="">�ƶ�����</param>
	/// <param name="">λ�ƴ�С</param>
	void Translate(glm::vec3, float);
};