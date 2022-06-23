#pragma once

class GameObject;
class Component
{
public:
	GameObject* gameobject;

	Component(GameObject* gameobject) :gameobject(gameobject) {}
	
	/*template <class T>
	T* GetComponent()
	{
		return gameobject->GetComponent<T>();
	}*/
	
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