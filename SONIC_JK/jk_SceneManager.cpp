#include "jk_SceneManager.h"
#include "jk_PlayScene.h"
#include "jk_PlayScene2.h"
#include "jk_TitleScene.h"
#include "jk_EndingScene.h"
#include "jk_ChatarcterChoiseSC.h"
#include "jk_CollisionManager.h"
#include "jk_MinigameScene.h"

namespace jk
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene= nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)jk_SceneType::END);


		mScenes[(UINT)jk_SceneType::Tittle] = new TitleScene();
		mScenes[(UINT)jk_SceneType::Tittle]->SetName(L"Tittle");
		mScenes[(UINT)jk_SceneType::CharacterChoice] = new ChatarcterChoiseSC();
		mScenes[(UINT)jk_SceneType::CharacterChoice]->SetName(L"CharacterChoice");
		mScenes[(UINT)jk_SceneType::GamePlay] = new PlayScene();
		mScenes[(UINT)jk_SceneType::GamePlay]->SetName(L"Act1-1");
		mScenes[(UINT)jk_SceneType::GamePlay2] = new PlayScene2();
		mScenes[(UINT)jk_SceneType::GamePlay2]->SetName(L"Act1-2");
		mScenes[(UINT)jk_SceneType::MiniGameplay] = new MinigameScene();
		mScenes[(UINT)jk_SceneType::MiniGameplay]->SetName(L"MiniGameplay");
		mScenes[(UINT)jk_SceneType::Ending] = new EndingScene();
		mScenes[(UINT)jk_SceneType::Ending]->SetName(L"Ending");

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}		
		mActiveScene = mScenes[(UINT)jk_SceneType::Tittle];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();	
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);	
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			delete scene;
			//scene->Release();			
		}
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destory();
	}

	void SceneManager::LoadScene(jk_SceneType type)
	{
		// ÇöÀç¾À
		mActiveScene->OnExit();
		//CollisionManager::Clear();
		//´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];

		mActiveScene->OnEnter();
	}
}