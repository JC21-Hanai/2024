#pragma once
#include "Object3D.h"

class Needle : public Object3D {
public:
	Needle();
	Needle(const VECTOR& pos, float rot);
	~Needle();
	void Update() override;
};