#pragma once
#include "Object3D.h"

class StageObject : public Object3D {
public:
	StageObject(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale);
	~StageObject();

	bool CollideLine(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit = nullptr);
private:
	int hitModel;
};