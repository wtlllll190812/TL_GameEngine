#pragma once
#include <vector>
#include "TLxml.h"
#include"Reflection.h"
#include"Transform.h"


class GameObject
{
public:
	Transform* transform;
	std::string name;//��������
	int guid;//�����ʶ

	GameObject();
	GameObject(TiXmlNode*);
	~GameObject();

	/// <summary>
	/// ����ˢ��
	/// </summary>
	void Update();

	/// <summary>
	/// ���л�
	/// </summary>
	TLxml* Serialize();

	/// <summary>
	/// ��ȡhashֵ
	/// </summary>
	int GetHash();

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
				(*it)->OnRemove();
				delete (*it);
			}
		}
		std::cout << "Component is not exist" << std::endl;
		return nullptr;
	}

	bool operator==(const GameObject& g)const {
		return g.guid == this->guid;
	}
private:
	std::vector<Component*> components;
};

