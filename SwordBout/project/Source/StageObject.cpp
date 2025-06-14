#include "StageObject.h"
#include <assert.h>

StageObject::StageObject(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale)
{
	const std::string folder = "data/model/Stage/";
	hModel = MV1LoadModel((folder+fileName+".mv1").c_str());
	assert(hModel>0);

	hitModel = MV1LoadModel((folder + fileName + "_c.mv1").c_str());
//	assert(hitModel > 0);

	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;
	transform.MakeLocalMatrix();
	MV1SetMatrix(hModel, transform.GetLocalMatrix());

	MV1SetupCollInfo(hitModel);
	MV1SetMatrix(hitModel, transform.GetLocalMatrix());
	MV1RefreshCollInfo(hitModel);
}

StageObject::~StageObject()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

bool StageObject::CollideLine(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit)
{
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hitModel, -1, pos1, pos2);
	if (ret.HitFlag == false)
		return false;
	if (hit != nullptr) {
		*hit = ret.HitPosition;
	}
	return true;
}
