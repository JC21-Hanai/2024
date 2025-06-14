#pragma once
#include "Object3D.h"
class SphereCollider;

class Stage : public Object3D {
public:
	Stage(int number = 0);
	~Stage();
	struct ColliderRet {
		VECTOR3 VPush; // ‚’¼•ûŒü‚Ì‰Ÿ‚µo‚µ
		VECTOR3 HPush; // …•½•ûŒü‚Ì‰Ÿ‚µo‚µ
	};
	ColliderRet CollideSphere(const SphereCollider& base) const;
	bool CollideLine(const VECTOR3& pos1, const VECTOR3& pos2, VECTOR3* hit = nullptr) const;
private:
	void ReadMappingData(std::string filename);
};