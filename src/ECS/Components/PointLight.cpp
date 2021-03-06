#include "PointLight.h"
#include "GameObject.h"
#include "Transform.h"
#include "imgui.h"
#include "Reflection.h"

REFLECTION(PointLight, Component);

float PointLight::constant = 1;
float PointLight::linear = 0.09;
float PointLight::quadratic = 0.032;

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

float PointLight::GetAtten(glm::vec3 objPos)const
{
	float dis = glm::distance(gameobject->transform->position,objPos);
	return intensity / (constant + linear * dis + quadratic * dis * dis);
}

TLxml* PointLight::Serialize()
{
	auto xml = new TLxml(GetName());
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->pRoot->SetAttribute("intensity", std::to_string(intensity));
	xml->AddChild(TLxml::Serialize(color, "color")->pRoot);
	return xml;
}

void PointLight::GuiDisPlay()
{
	float col[3] = { color.x,color.y,color.z };
	ImGui::DragFloat("Intensity", &intensity);
	ImGui::DragFloat("Range", &range);
	ImGui::ColorEdit3("Color", col);
	color = glm::vec3(col[0], col[1], col[2]);
}

void PointLight::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	intensity = std::stof(element->Attribute("intensity"));
	color = TLxml::DeSerialize(xml->FirstChild());
}

