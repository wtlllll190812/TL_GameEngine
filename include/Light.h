#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class GameObject;
class Light :public Component
{
public:
	Light(float, glm::vec3);
	Light();
	~Light();

	/// <summary>
	/// ���ǿ��
	/// </summary>
	float intensity;

	/// <summary>
	/// �����ɫ
	/// </summary>
	glm::vec3 color;

	/// <summary>
	/// ���л�
	/// </summary>
	virtual TLxml* Serialize() override;

	/// <summary>
	/// ͨ��xmlʵ����
	/// </summary>
	virtual void Instantiate(TiXmlNode*) override;

	/// <summary>
	/// �����ʱ
	/// </summary>
	virtual void Awake() override;
};