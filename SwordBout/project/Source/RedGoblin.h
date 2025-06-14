#pragma once
#include "Object3D.h"
#include "Animator.h"

class RedGoblin : public Object3D {
public:
	RedGoblin();
	RedGoblin(const VECTOR& pos, float rot);
	~RedGoblin();
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