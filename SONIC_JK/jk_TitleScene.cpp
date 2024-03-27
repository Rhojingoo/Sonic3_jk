#include "jk_TitleScene.h"
#include "jk_Title.h"
#include "jk_Titlesonic.h"
#include "jk_Airplanetails.h"
#include "jk_TitleSN.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"


#include "jk_Input.h"
#include "jk_Object.h"
#include "jk_Blending.h"



namespace jk
{
	TitleScene::TitleScene()
		: mScenImage(nullptr)
		, mainTheme(nullptr)
		, choice_music(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{			
		mainTheme = Resources::Load<Sound>(L"Opening", L"..\\Resources\\Sound\\Opening.wav");
		choice_music = Resources::Load<Sound>(L"Character_choice", L"..\\Resources\\Sound\\Character_choice.wav");		

		Title* title_bg = new Title();
		AddGameobeject(title_bg, jk_LayerType::BG);

		Airplanetails* aiplane1 = new Airplanetails();
		AddGameobeject(aiplane1, jk_LayerType::BG);
	
		Titlesonic* titlesonic = new Titlesonic();
		AddGameobeject(titlesonic, jk_LayerType::BG);
			
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			mainTheme->Stop(false);
			choice_music->Play(true);
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
		mainTheme->Play(true);
	}

	void TitleScene::OnExit()
	{
	}
	void TitleScene::CreateBlending()
	{
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}
}

