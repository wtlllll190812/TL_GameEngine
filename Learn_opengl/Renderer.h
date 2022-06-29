#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include<memory>

//extern std::priority_queue < Renderer*, std::vector<Renderer*>> renderQueue;

class GameObject;
class Renderer :public Component
{
public:
	/// <summary>
	/// ģ��Mesh
	/// </summary>
	shared_ptr<Mesh> mesh;

	/// <summary>
	/// ����
	/// </summary>
	shared_ptr<Material> material;

	Renderer(Mesh*, Material*);
	Renderer();
	~Renderer();

	/// <summary>
	/// ������Ⱦ
	/// </summary>
	void Render();

	/// <summary>
	/// �����ʱ
	/// </summary>
	void Awake() override;

	bool operator>(const Renderer& r)
	{
		return r.material->renderQueueIndex > material->renderQueueIndex;
	}

	// ͨ�� Component �̳�
	virtual TLxml* Serialize() override;

	// ͨ�� Component �̳�
	virtual void Instantiate(TiXmlNode*) override;
};

