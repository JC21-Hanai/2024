#pragma once
#include "Object3D.h"
#include "Animator.h"

class Goblin : public Object3D {
public:
	Goblin();
	Goblin(const VECTOR& pos, float rot);
	~Goblin();
	void Update() override;
private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_WALK,
		A_RUN,
		A_ATTACK1,
		A_DAMAGE,
		A_BLOW_IN,
		A_BLOW_LOOP,
		A_BLOW_OUT,
		A_DOWN,
	};
	Animator* animator;
};