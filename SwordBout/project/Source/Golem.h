#pragma once
#include "Object3D.h"
#include "Animator.h"

class Golem : public Object3D {
public:
	Golem();
	Golem(const VECTOR& pos, float rot);
	~Golem();
	void Update() override;
private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_WALK,
		A_ATTACK1,
		A_ATTACK2,
		A_ATTACK3,
		A_DOWN,
	};
	Animator* animator;
};