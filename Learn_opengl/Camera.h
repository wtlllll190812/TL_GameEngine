#pragma once
#include <string>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Screen.h"
#include "Transform.h"
#include "Component.h"
#include "GameObject.h"

class Camera:public Component
{
public:
	float fov = 120.0f;

	Camera(Screen*, GameObject*);
	~Camera();
	void OnUpdate()override;
	void OnAdd()override;
	void OnRemove()override;
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();

private:
	Screen* currentScreen;
};