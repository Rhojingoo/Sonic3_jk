#include "jk_Scene.h"
#include "jk_SceneManager.h"

namespace jk
{
	Scene::Scene()
	{	
		mLayers.resize((UINT)jk_LayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		SceneManager::SetActiveScene(this);

		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			 layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}
	void Scene::Destory()
	{
		std::vector<Gameobject*> deleteGameObjects = {};
		for (Layer& layer : mLayers)
		{
			std::vector<Gameobject*>& gameObjects
				= layer.GetGameobjects();

			for (std::vector<Gameobject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->GetState() == Gameobject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		// 죽은 위치에서 충돌중인 다른 충돌체가 있었다면 Exit를
		// 호출 해준후에 삭제 해주어야한다.

		for (Gameobject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}
	}

	void Scene::Release()
	{	
		for (Layer& layer : mLayers)
		{
			layer.Release();
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameobeject(Gameobject* obj, jk_LayerType layer)
	{
		mLayers[(UINT)layer].AddGameobject(obj);
	}

	std::vector<Gameobject*>& Scene::GetGameobjects(jk_LayerType layer)
	{
		return mLayers[(UINT)layer].GetGameobjects();
	}
}