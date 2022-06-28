#pragma once
#include <vector>


#include "Transform.h"
#include "TLxml.h"
#include"Reflection.h"

class GameObject
{
public:
	Transform* transform;
	std::string name;
	int guid;

	GameObject();
	GameObject(TiXmlNode*);
	~GameObject();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void AddComponent(Component*);

	/// <summary>
	/// ��ȡ���
	/// </summary>
	/// <typeparam name="T">�������</typeparam>
	/// <returns>�������</returns>
	template <class T>
	T* GetComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			auto com = dynamic_cast<T*>(*it);
			if (com)
			{
				return com;
			}
		}
		std::cout << "Component is not exist" << std::endl;
		return nullptr;
	}

	/// <summary>
	/// �Ƴ����
	/// </summary>
	/// <typeparam name="T">�������</typeparam>
	template <class T>
	void RemoveComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if (dynamic_cast<T*>(*it))
			{
				delete (*it);
			}
		}
		std::cout << "Component is not exist" << std::endl;
		return nullptr;
	}

	void Update();
	
	TLxml* Serialize();

	int GetHash();

	bool operator==(const GameObject& g)const {
		return g.guid == this->guid;
	}
private:
	std::vector<Component*> components;
};

