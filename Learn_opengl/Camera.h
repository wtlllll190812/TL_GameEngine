#pragma once
#include <string>
#include "Component.h"

class Screen;
class Camera :public Component
{
public:
	/// <summary>
	/// �ӽǴ�С
	/// </summary>
	float fov = 120.0f;

	Camera(Screen*);
	Camera();
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
	/// <summary>
	/// ��ǰ����
	/// </summary>
	Screen* currentScreen;

	/// <summary>
	/// ���л�
	/// </summary>
	virtual TLxml* Serialize() override;

	/// <summary>
	/// ͨ��xmlʵ����
	/// </summary>
	/// <param name=""></param>
	virtual void Instantiate(TiXmlNode*) override;
};
