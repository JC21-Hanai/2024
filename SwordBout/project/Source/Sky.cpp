#include "Sky.h"
#include <assert.h>

Sky::Sky()
{
}

Sky::Sky(std::string file)
{
	const std::string folder = "data/model/Stage/";
	hModel = MV1LoadModel((folder + file + ".mv1").c_str());
	assert(hModel > 0);
}

Sky::~Sky()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Sky::Draw()
{
	Object3D::Draw();
}
