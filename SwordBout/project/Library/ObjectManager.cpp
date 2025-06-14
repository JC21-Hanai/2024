#include "ObjectManager.h"
#include "GameObject.h"
#include <algorithm>
#include <assert.h>

namespace
{
	std::list<GameObject*>* objects;
	bool needSortDraw;
	GameObject* running;
};

void ObjectManager::Init()
{
	objects = new std::list<GameObject*>;
	objects->clear();
	needSortDraw = false;
	running = nullptr;
}

void ObjectManager::Update()
{
	for (auto itr = objects->begin(); itr != objects->end(); itr++)
	{
		GameObject* obj = *itr;
		if (obj == nullptr)
			continue;
		if (not obj->DestroyRequested())
		{
			running = obj;
			obj->Update();
			running = nullptr;
		}
		if (obj->DestroyRequested())
		{
			delete obj;
			*itr = nullptr;
		}
	}
	for (auto itr = objects->begin(); itr != objects->end();)
	{
		if (*itr == nullptr)
		{
			itr = objects->erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void ObjectManager::Draw()
{
	if (needSortDraw)
	{
		objects->sort([](GameObject* a, GameObject* b) {return a->GetDrawOrder() > b->GetDrawOrder(); });
		needSortDraw = false;
	}
	for (GameObject* obj : *objects)
	{
		if (obj == nullptr || obj->DestroyRequested())
			continue;
		obj->Draw();
	}
}

void ObjectManager::Release()
{
	while (objects->size() > 0)
	{
		auto itr = objects->begin();
		if (*itr != nullptr)
		{
			delete *itr;
		}
		objects->erase(itr);
	}
	objects->clear();
	delete objects;
	objects = nullptr;
}

void ObjectManager::Push(GameObject* obj)
{
	objects->push_back(obj);
	needSortDraw = true;
}

void ObjectManager::SortByDrawOrder()
{
	needSortDraw = true;
}

void ObjectManager::Pop(GameObject* obj)
{
	assert(running != obj);

	for (auto itr = objects->begin(); itr != objects->end(); itr++)
	{
		if (*itr == obj)
		{
			*itr = nullptr;
		}
	}
}

void ObjectManager::DeleteAllGameObject()
{
	assert(running == nullptr);

	for (auto itr = objects->begin(); itr != objects->end(); itr++)
	{
		GameObject* obj = *itr;
		if (not obj->IsDontDestroy())
		{
			delete obj;
			*itr = nullptr;
		}
	}
	for (auto itr = objects->begin(); itr != objects->end();)
	{
		if (*itr == nullptr) {
			itr = objects->erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

const std::list<GameObject*>& ObjectManager::GetAllObject()
{
	return *objects;
}
