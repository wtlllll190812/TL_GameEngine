#pragma once
#include "TLxml.h"
#include <string>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	/// <summary>
	/// ��ȡ����ʼ������
	/// </summary>
	/// <param name="">�����ļ�·��</param>
	Scene(std::string);
	~Scene();

	/// <summary>
	/// ���泡��
	/// </summary>
	void Save();
	
	/// <summary>
	/// �ڳ�����Ѱ�Ҷ���
	/// </summary>
	/// <param name="">��������</param>
	GameObject* Find(std::string);
private:
	/// <summary>
	/// �����ļ�·��
	/// </summary>
	std::string path;

	/// <summary>
	/// ����������ļ���
	/// </summary>
	std::vector<GameObject*> gameobjects;
	
	/// <summary>
	/// �����ļ�����
	/// </summary>
	TLxml xml;
};
