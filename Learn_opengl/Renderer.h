#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include<memory>

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

	/// <summary>
	/// ���л�Ϊxml
	/// </summary>
	/// <returns></returns>
	virtual TLxml* Serialize() override;

	/// <summary>
	/// ͨ��xmlʵ����
	/// </summary>
	/// <param name=""></param>
	virtual void Instantiate(TiXmlNode*) override;

	bool operator>(const Renderer& r)
	{
		return r.material->renderQueueIndex > material->renderQueueIndex;
	}
};
