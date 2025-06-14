#include "Transform.h"

const MATRIX& Transform::MakeLocalMatrix()
{
    MATRIX ms = MGetScale(scale);
    MATRIX mrx = MGetRotX(rotation.x);
    MATRIX mry = MGetRotY(rotation.y);
    MATRIX mrz = MGetRotZ(rotation.z);
    MATRIX mt = MGetTranslate(position);
    rotMatrix = ms * mrz * mrx * mry;
    localMatrix = rotMatrix * mt;
    return localMatrix;
}