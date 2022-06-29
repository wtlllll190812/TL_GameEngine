#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "TLEngineCG.h"
#include<memory>

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
	void (*RenderCallback)(Shader*, Material*);

	Material(const GLchar*, const GLchar*);
	Material();
	~Material();

	void SetRenderCallback(void (*f)(Shader*, Material*));
	void Render(shared_ptr<Mesh>);
};
