#include "jk_EndingScene.h"
#include "jk_Ending.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_Object.h"
#include "EndingBlend.h"

namespace jk
{
	EndingScene::EndingScene()
	{
	}


	EndingScene::~EndingScene()
	{
	}


	void EndingScene::Initialize()
	{

		Ending* END_bg = new Ending();
		END_bg->SetName(L"EndBG");
		AddGameobeject(END_bg, jk_LayerType::BG);

		Scene::Initialize();
	}


	void EndingScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			CreateBlending();			
		}

		Scene::Update();
		if (Input::GetKeyState(eKeyCode::L) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::Tittle);
		}
		
	}


	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}


	void EndingScene::Release()
	{
		Scene::Release();
	}


	void EndingScene::OnEnter()
	{
	}


	void EndingScene::OnExit()
	{
	}
	void EndingScene::CreateBlending()
	{
		object::Instantiate<EndingBlend>(jk_LayerType::Blend);
	}
}