#pragma once
#include "TLxml.h"
#include <string>
#include <functional>


class GameObject;
class Component
{
public:
	GameObject* gameobject;
	int guid;

	Component() :gameobject(nullptr),guid(GetHash()) {}
	
	virtual void Instantiate(TiXmlNode*)=0;

	/// <summary>
	/// ˢ��ʱ
	/// </summary>
	virtual void OnUpdate() {};
	
	/// <summary>
	/// ���ʱ
	/// </summary>
	virtual void Awake() {};
	
	/// <summary>
	/// �Ƴ�ʱ
	/// </summary>
	virtual void OnRemove() {};

	/// <summary>
	/// ���л�
	/// </summary>
	virtual TLxml* Serialize()=0;

	/// <summary>
	/// ��ȡ��ϣֵ
	/// </summary>
	int GetHash()
	{
		std::hash<Component*> h;
		return (h(this));
	}
};