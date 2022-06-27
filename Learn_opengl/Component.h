#pragma once

class GameObject;
class Component
{
public:
	GameObject* gameobject;

	Component(GameObject* gameobject) :gameobject(gameobject) {}
	
	/// <summary>
	/// ˢ��ʱ
	/// </summary>
	virtual void OnUpdate() {};
	
	/// <summary>
	/// ���ʱ
	/// </summary>
	virtual void OnAdd() {};
	
	/// <summary>
	/// �Ƴ�ʱ
	/// </summary>
	virtual void OnRemove() {};

};