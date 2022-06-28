#pragma once
#include<vector>
#include<string>
#include<iostream>
#include "Transform.h"
#include "TLxml.h"

class GameObject
{
public:
	Transform* transform;
	std::string name;
	int guid;

	GameObject();
	~GameObject();

	/// <summary>
	/// 添加组件
	/// </summary>
	/// <param name=""></param>
	void AddComponent(Component*);

	/// <summary>
	/// 获取组件
	/// </summary>
	/// <typeparam name="T">组件类型</typeparam>
	/// <returns>组件对象</returns>
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
	/// 移除组件
	/// </summary>
	/// <typeparam name="T">组件类型</typeparam>
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
private:
	std::vector<Component*> components;
};