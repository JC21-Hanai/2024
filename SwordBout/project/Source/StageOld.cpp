#include "Stage.h"
#include <assert.h>
#include "Sky.h"
#include "Player.h"
#include "Goblin.h"
#include "Bee.h"
#include "Golem.h"
#include "RedGoblin.h"
#include "Needle.h"
#include "StageObject.h"

Stage::Stage(int number)
{
	char filename[16];
	sprintf_s<16>(filename, "Stage%02d", number);
	new StageObject(filename, VGet(0,0,0), VGet(0,0,0), VGet(1,1,1));
	ReadMappingData(filename);
	if (number == 0) {
		new Sky("Stage00_sky");
	}
}

Stage::~Stage()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}
void Stage::ReadMappingData(std::string filename)
{
	VECTOR pos = VECTOR3(0, 50, 0);
	float ang = 0;
	new Player(pos, ang);
}