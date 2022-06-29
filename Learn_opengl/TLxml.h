#pragma once
#include <string>
#include <tinyxml.h>
#include <glm/glm.hpp>

class TLxml
{
public:
	TiXmlElement* pRoot;

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="">·��</param>
	/// <param name="">��Ԫ������</param>
	TLxml(std::string, std::string);
	/// <summary>
	/// ������ļ��ڵ�
	/// </summary>
	/// <param name="">��Ԫ������</param>
	TLxml(std::string);
	~TLxml();

	/// <summary>
	/// ����ӽڵ�
	/// </summary>
	void AddChild(TiXmlElement*);
	
	/// <summary>
	/// �����ļ�
	/// </summary>
	void Save() { pDoc->SaveFile(path); }
	
	/// <summary>
	/// ���л�����
	/// </summary>
	/// <param name="">����</param>
	/// <param name="">�ڵ���</param>
	static TLxml* Serialize(glm::vec3&, std::string);
	
	/// <summary>
	/// �����л�����
	/// </summary>
	/// <param name="">����</param>
	/// <returns>�ڵ���</returns>
	static glm::vec3 DeSerialize(TiXmlNode*);
private:
	std::string path;
	TiXmlDocument* pDoc;
};

/// <summary>
/// �����л�����ӿ�
/// </summary>
class Serializable
{
	virtual TLxml* Serialize()=0;
	virtual void DeSerialize(TiXmlNode*)=0;
};