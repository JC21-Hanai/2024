#include "Object3D.h"

Object3D::~Object3D()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Object3D::Draw()
{
	if (hModel > 0)
	{
		const MATRIX& m = transform.MakeLocalMatrix();
		if (parent != nullptr)
		{
			MV1SetMatrix(hModel, m * parent->GetTransform().GetLocalMatrix());
		}
		else
		{
			MV1SetMatrix(hModel, m);
		}
		MV1DrawModel(hModel);
	}
}
