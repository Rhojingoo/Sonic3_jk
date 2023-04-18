#include "jk_TitleScene.h"
#include "jk_Title.h"
#include "jk_Titlesonic.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_Airplanetails.h"
#include "jk_TitleSN.h"
#include "jk_Blending.h"
#include "jk_Object.h"

namespace jk
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{			
		Title* title_bg = new Title();
		AddGameobeject(title_bg, jk_LayerType::BG);

		Airplanetails* aiplane1 = new Airplanetails();
		AddGameobeject(aiplane1, jk_LayerType::BG);
	
		Titlesonic* titlesonic = new Titlesonic();
		AddGameobeject(titlesonic, jk_LayerType::BG);

	/*	TitleSN* TTsm = new TitleSN();
		AddGameobeject(TTsm, jk_LayerType::BG);*/
			
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::CharacterChoice);
			CreateBlending();
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{
		Scene::Release();
	}


	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
	}
	void TitleScene::CreateBlending()
	{
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}
}

