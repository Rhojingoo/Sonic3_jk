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
		std::vector<Gameobject*> deleteGameobjects = {};
		for (Layer& layer : mLayers)
		{		
			std::vector<Gameobject*>& gameobjects
				= layer.GetGameobjects();			

			for (std::vector<Gameobject*>::iterator iter = gameobjects.begin();
				iter != gameobjects.end();)
			{
				if ((*iter)->GetState() == Gameobject::eState::Death)
				{
					deleteGameobjects.push_back((*iter));
					iter = gameobjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
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