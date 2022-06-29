#pragma once
#include"Component.h"

class Behaviour:public Component
{
	// ͨ�� Component �̳�
	virtual void Instantiate(TiXmlNode*) override;
	virtual TLxml* Serialize() override;

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};
};