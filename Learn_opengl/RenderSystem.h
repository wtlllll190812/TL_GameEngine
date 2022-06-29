#pragma once
#include<queue>
#include<vector>
#include"System.h"

class Component;
class Renderer;
class RenderSystem :public System, public Singleton<RenderSystem>
{
public:
	RenderSystem();
	~RenderSystem();

	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	static std::priority_queue <Renderer*, std::vector<Renderer*>> renderQueue;

	/// <summary>
	/// ÿ֡ˢ��
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// �̶�ʱ��ˢ��
	/// </summary>
	virtual void FixedUpdate() override;

	/// <summary>
	/// ע�����
	/// </summary>
	virtual void RegisterComponent(Component*) override;

	/// <summary>
	/// �Ƴ����
	/// </summary>
	virtual void RemoveComponent(Component*) override;

	/// <summary>
	/// ���
	/// </summary>
	void Clear();
};