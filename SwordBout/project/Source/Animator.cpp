#include "Animator.h"
#include <string>
#include <assert.h>
#include "../Library/myDxLib.h"
#include "../Library/time.h"

Animator::Animator(int model)
{
    baseModel = model;
    fileInfos.clear();
    playSpeed = 1.0f;
    blendTime = 0.0f;
    blendTimeMax = 0.0f;
    finished = true;
}

Animator::~Animator()
{
    if (before.attachID >= 0)
    {
        MV1DetachAnim(baseModel, before.attachID);
    }
    if (current.attachID >= 0)
    {
        MV1DetachAnim(baseModel, current.attachID);
    }
    for (auto& inf : fileInfos)
    {
        if (inf.second.hModel > 0)
        {
            MV1DeleteModel(inf.second.hModel);
            inf.second.hModel = -1;
        }
    }
    fileInfos.clear();
}

void Animator::Update()
{
    if (current.attachID >= 0)
    { // current
        const FileInfo& f = fileInfos[current.fileID];
        current.frame += Time::DeltaTime() * playSpeed * f.playSpeed * 30.0f;
        if (current.frame >= f.maxFrame)
        {
            if (f.loop)
            {
                current.frame -= f.maxFrame;
            }
            else
            {
                current.frame = f.maxFrame;
                finished = true;
            }
        }
        MV1SetAttachAnimTime(baseModel, current.attachID, current.frame);
    }
    if (before.attachID>=0)
    { // before
        blendTime += Time::DeltaTime();
        if (blendTime >= blendTimeMax)
        {
            MV1SetAttachAnimBlendRate(baseModel, current.attachID, 1.0f);
            MV1SetAttachAnimBlendRate(baseModel, before.attachID, 0.0f);
            MV1DetachAnim(baseModel, before.attachID);
            before.attachID = -1;
            before.fileID = -1;
            return;
        }
        const FileInfo& f = fileInfos[before.fileID];
        before.frame += Time::DeltaTime() * playSpeed * f.playSpeed * 30.0f;
        if (before.frame >= f.maxFrame)
        {
            if (f.loop) {
                before.frame -= f.maxFrame;
            }
            else {
                before.frame = f.maxFrame;
            }
        }
        MV1SetAttachAnimTime(baseModel, before.attachID, before.frame);

        float rate = blendTime / blendTimeMax;
        MV1SetAttachAnimBlendRate(baseModel, current.attachID, rate);
        MV1SetAttachAnimBlendRate(baseModel, before.attachID, 1.0f - rate);
    }
}

void Animator::AddFile(int id, std::string filename, bool loop, float speed)
{
    FileInfo inf;
    inf.hModel = MV1LoadModel(filename.c_str());
    assert(inf.hModel > 0);
    inf.loop = loop;
    inf.playSpeed = speed;
    if (inf.hModel > 0)
    {
        inf.maxFrame = MV1GetAnimTotalTime(inf.hModel, 0);
    }
    if (fileInfos.count(id) > 0)
    {
        MessageBox(nullptr, 
            (std::string("ID=") + std::to_string(id) + "‚ÍŽg‚í‚ê‚Ä‚¢‚Ü‚·").c_str(),
            "Animator", MB_OK);
        assert(false);
    }
    fileInfos.emplace(id, inf); // “o˜^
}

void Animator::Play(int id, float margeTime)
{
    if (current.fileID == id)
    {
        return;
    }
    if (before.attachID >= 0)
    {
        MV1DetachAnim(baseModel, before.attachID);
        before.attachID = -1;
        before.fileID = -1;
    }
    if (current.attachID >= 0)
    {
        before = current;
        blendTimeMax = margeTime;
        blendTime = 0.0f;
    }
    else
    {
        blendTimeMax = 0.0f;
    }
    current.fileID = id;
    if (fileInfos.count(id) > 0)
    {
        current.attachID = MV1AttachAnim(baseModel, 0, fileInfos[id].hModel);
        current.frame = 0.0f;
        finished = false;
        MV1SetAttachAnimTime(baseModel, current.attachID, 0.0f);
        if (before.attachID >= 0)
        {
            MV1SetAttachAnimBlendRate(baseModel, current.attachID, 0.0f);
            MV1SetAttachAnimBlendRate(baseModel, before.attachID, 1.0f);
        }
        else 
        {
            MV1SetAttachAnimBlendRate(baseModel, current.attachID, 1.0f);
        }
    }
}

void Animator::SetPlaySpeed(float speed)
{
    playSpeed = speed;
}

float Animator::GetPlaySpeed()
{
    return playSpeed;
}

bool Animator::IsFinish()
{
    return finished;
}

int Animator::GetCurrentID()
{
    return current.fileID;
}

float Animator::GetCurrentFrame()
{
    return current.frame;
}

float Animator::GetMaxFrame()
{
    if (current.attachID >= 0)
    {
        return fileInfos[current.fileID].maxFrame;
    }
    return 0.0f;
}
