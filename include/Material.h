#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "TLEngineCG.h"
#include<memory>

class GameObject;
class Material
{
public:
	Shader* shader;
	
	/// <summary>
	/// ��Ⱦ���д���
	/// </summary>
	int renderQueueIndex = (int)RendererQueue::Geometry;
	
	/// <summary>
	/// ��Ⱦʱ�ص�
	/// </summary>
	void (*RenderCallback)(GameObject* ,Shader*, Material*);

	Material(const GLchar*, const GLchar*);
	Material();
	~Material();

	void SetRenderCallback(void (*f)(GameObject* ,Shader*, Material*));
	void Render(GameObject*,shared_ptr<Mesh>);
};
