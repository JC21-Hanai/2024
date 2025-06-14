#include "Needle.h"
#include <assert.h>

Needle::Needle() : Needle(VGet(0,0,0), 0.0f){}

Needle::Needle(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Needle/";
	hModel = MV1LoadModel((folder + "Needle.mv1").c_str());
	assert(hModel > 0);

	transform.position = pos;
	transform.rotation.y = rot;
}

Needle::~Needle()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Needle::Update()
{
}