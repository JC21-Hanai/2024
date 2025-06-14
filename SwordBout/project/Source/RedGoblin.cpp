#include "RedGoblin.h"
#include <assert.h>

RedGoblin::RedGoblin() : RedGoblin(VGet(0,0,0), 0.0f){}

RedGoblin::RedGoblin(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/RedGoblin/";
	hModel = MV1LoadModel((folder + "RedGoblin.mv1").c_str());
	assert(hModel > 0);

	animator = new Animator(hModel);
	assert(animator != nullptr);
	animator->AddFile(A_NEUTRAL,   folder + "Anim_Neutral.mv1",   true);
	animator->AddFile(A_WALK,      folder + "Anim_Walk.mv1", true);
	animator->AddFile(A_RUN,       folder + "Anim_Run.mv1",       true);
	animator->AddFile(A_ATTACK1,   folder + "Anim_Attack1.mv1",   false);
	animator->AddFile(A_DAMAGE,    folder + "Anim_Damage.mv1",    false);
	animator->AddFile(A_BLOW_IN,   folder + "Anim_Blow_In.mv1",   false);
	animator->AddFile(A_BLOW_LOOP, folder + "Anim_Blow_Loop.mv1", true);
	animator->AddFile(A_BLOW_OUT,  folder + "Anim_Blow_Out.mv1",  false);
	animator->AddFile(A_DOWN,      folder + "Anim_Down_Loop.mv1",      true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;
}

RedGoblin::~RedGoblin()
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

void RedGoblin::Update()
{
}