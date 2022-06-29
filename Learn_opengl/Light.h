#pragma once
#include <glm/glm.hpp>
#include "TLEngineCG.h"
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

	// ͨ�� Component �̳�
	virtual void Instantiate(TiXmlNode*) override;

	virtual void Awake() override;
};