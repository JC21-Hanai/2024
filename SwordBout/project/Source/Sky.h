#pragma once
#include "Object3D.h"

class Sky : public Object3D {
public:
	Sky();
	Sky(std::string file);
	~Sky();
	void Draw() override;
};