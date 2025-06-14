#include "Golem.h"
#include <assert.h>

Golem::Golem() : Golem(VGet(0,0,0), 0.0f){}

Golem::Golem(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Golem/";

	hModel = MV1LoadModel((folder + "Golem.mv1").c_str());
	assert(hModel > 0);

	animator = new Animator(hModel);
	assert(animator != nullptr);
	animator->AddFile(A_NEUTRAL, folder + "Anim_Neutral.mv1", true);
	animator->AddFile(A_WALK,    folder + "Anim_Walk.mv1",    true);
	animator->AddFile(A_ATTACK1, folder + "Anim_Attack1.mv1", false);
	animator->AddFile(A_ATTACK2, folder + "Anim_Attack2.mv1", false);
	animator->AddFile(A_ATTACK3, folder + "Anim_Attack3.mv1", false);
	animator->AddFile(A_DOWN,    folder + "Anim_Down.mv1",    true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;
}

Golem::~Golem()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Golem::Update()
{
}