#pragma once
#include "jk_Gameobject.h"
#include "jk_Scene.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"

namespace jk::object
{
		template <typename T>//ĳ����.cpp���� ĳ���ͻ����� �ۼ��Ͽ� �ڵ�����
static inline T* Instantiate(jk_LayerType type)
{
	T* gameobj = new T();
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddGameobeject(gameobj, type);
	gameobj->Initialize();
	return gameobj;
}

template <typename T>//��ġ��� �÷��̽�, Ÿ��Ʋ�� � �ۼ��ϸ��
static inline T* Instantiate(Vector2 pos, jk_LayerType type)
{
	T* gameobj = new T;
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddGameobeject(gameobj, type);
	gameobj->Gameobject::GetComponent<Transform>()->SetPos(pos);
	gameobj->Initialize();
	return gameobj;
}

template <typename T>//��ġ��� �÷��̽�, Ÿ��Ʋ�� � �ۼ��ϸ��
static inline T* Instantiate(Vector2 pos, jk_LayerType type, jk_SceneType stype)
{
	T* gameobj = new T;
	Scene* scene = SceneManager::FindScene(stype);
	scene->AddGameobeject(gameobj, type);
	gameobj->Gameobject::GetComponent<Transform>()->SetPos(pos);
	gameobj->Initialize();
	return gameobj;
}

static void Destory(Gameobject* obj)
{
	obj->SetState(Gameobject::eState::Death);
}
}


