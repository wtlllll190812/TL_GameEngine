#include"GameObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Transform.h"
#include "Debug.h"
#include "Reflection.h"

REFLECTION(GameObject, GameObject);

GameObject::GameObject()
{
	name = "GameObject";
	guid = GetHash();
	transform = new Transform();
	components.push_back(transform);
	transform->gameobject = this;
	transform->Awake();
}

GameObject::GameObject(TiXmlNode* xml, Scene* s)
{
	owner = s;
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	name = element->Attribute("name");
	for (auto node = element->FirstChild(); node != 0; node = node->NextSibling())
	{
		auto element = node->ToElement();
		Debug::GetEngineLogger()->info("Scene Load {0}", element->Value());
		if (strcmp(element->Value(), "Transform") != 0)
		{
			auto comp = (Component*)ReflectionManager::instance().getClassByName(element->Value());
			comp->Instantiate(element);
			if (strcmp(element->Value(), "Camera") == 0)
			{
				s->camera = (Camera*)comp;
			}
			AddComponent(comp);
		}
		else
		{
			transform = new Transform();
			transform->Instantiate(element);
			AddComponent(transform);
		}
	}
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
	comp->gameobject = this;
	comp->Awake();
	if (transform == nullptr)transform = dynamic_cast<Transform*>(comp);
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); ++i)
	{
		(*i)->OnUpdate();
	}
}

TLxml* GameObject::Serialize()
{
	TLxml* xml = new TLxml(name);
	for (auto i : components)
	{
		xml->pRoot->SetAttribute("name", name);
		xml->pRoot->SetAttribute("guid", std::to_string(guid));
		xml->AddChild(i->Serialize()->pRoot);
	}
	return xml;
}

int GameObject::GetHash()
{
	std::hash<GameObject*> h;
	return (h(this));
}