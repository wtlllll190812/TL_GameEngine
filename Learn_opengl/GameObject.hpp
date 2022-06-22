#pragma once
#include<vector>
#include<string>
#include<iostream>
#include "Component.hpp"
#include "Transform.hpp"

class GameObject
{
public:
	Transform* transform;

	GameObject();
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
private:
	std::vector<Component*> components;
};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
	if (transform == nullptr)transform = dynamic_cast<Transform*>(comp);
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		(*i)->OnUpdate();
	}
}