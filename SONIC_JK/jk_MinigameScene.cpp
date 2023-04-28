#include "jk_MinigameScene.h"
#include "jk_Minigame.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_EmeraldSonic.h"
#include "jk_CollisionManager.h"
#include "jk_MGEmerald.h"
#include "jk_Camera.h"
#include "jk_Blending.h"
#include "jk_Object.h"


namespace jk
{
	MinigameScene::MinigameScene()
	{
	}

	MinigameScene::~MinigameScene()
	{
	}

	void MinigameScene::Initialize()
	{
		MGEmerald* emerald = new MGEmerald();
		emerald->SetName(L"Mg_Emerald");
		EmeraldSonic* emsonic = new EmeraldSonic();
		emsonic->SetName(L"Mg_Sonic");
		Minigame* Mini_bg = new Minigame();
		Mini_bg->SetName(L"Mg_BG");
		//Camera::SetTarget(emsonic);
		AddGameobeject(emsonic, jk_LayerType::Player);
		AddGameobeject(Mini_bg, jk_LayerType::BG);
		AddGameobeject(emerald, jk_LayerType::Item);
		Scene::Initialize();
	}

	void MinigameScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::Ending);
			CreateBlending();
		}
	}


	void MinigameScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}


	void MinigameScene::Release()
	{
		Scene::Release();
	}
	

	void MinigameScene::OnEnter()
	{
		//Camera::SetTarget(Mini_bg);
		//CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Item, true);//¸µ, ¿¡¸Þ¶öµå ¸ÔÀ»¶§ ÇÊ¿ä
	}

	void MinigameScene::OnExit()
	{
	}
	void MinigameScene::CreateBlending()
	{
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}
}