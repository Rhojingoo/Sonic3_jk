#include "jk_LoadingScene.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_LoadingBg.h"

#include "jk_Input.h"
#include "jk_Object.h"
#include "jk_Blending.h"

namespace jk
{
	LoadingScene::LoadingScene()
		: mScenImage(nullptr)	
	{
	}

	LoadingScene::~LoadingScene()
	{
	}

	void LoadingScene::Initialize()
	{

		LoadingBg* LOAD_bg = new LoadingBg();
		AddGameobeject(LOAD_bg, jk_LayerType::BG);

		Scene::Initialize();
	}

	void LoadingScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::Tittle);
			CreateBlending();
		}
	}

	void LoadingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LoadingScene::Release()
	{
		Scene::Release();
	}

	void LoadingScene::OnEnter()
	{
	}

	void LoadingScene::OnExit()
	{
	}

	void LoadingScene::CreateBlending()
	{
	}
}


