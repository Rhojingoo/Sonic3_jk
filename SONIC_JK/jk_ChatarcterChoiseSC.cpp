#include "jk_ChatarcterChoiseSC.h"
#include "jk_Choice_select.h"
#include "jk_CharaterChoice.h"
#include "jk_ChoiceCC.h"
#include "jk_Blending.h"

#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Input.h"
#include "jk_Object.h"
#include "jk_Image.h"
#include "jk_Sound.h"

namespace jk
{
	ChatarcterChoiseSC::ChatarcterChoiseSC()
		: mScenImage(nullptr)
		 ,choice_music(nullptr)
		, Act1_music(nullptr)
	    , Selec(nullptr)

	{
	}
	ChatarcterChoiseSC::~ChatarcterChoiseSC()
	{
	}
	void ChatarcterChoiseSC::Initialize()
	{
		choice_music = Resources::Load<Sound>(L"Character_choice", L"..\\Resources\\Sound\\Character_choice.wav");
		Act1_music = Resources::Load<Sound>(L"Act1_bg", L"..\\Resources\\Sound\\Act1_bg.wav");
		Selec = Resources::Load<Sound>(L"Selec", L"..\\Resources\\Sound\\Sonic\\Selec.wav");

		CharaterChoice* ch_bg = new CharaterChoice();
		ch_bg->SetName(L"ss");
		AddGameobeject(ch_bg, jk_LayerType::BG);

		ChoiceCC* Ccchoice = new ChoiceCC();
		Ccchoice->SetName(L"charator_box");
		AddGameobeject(Ccchoice, jk_LayerType::BG);

		Choice_select* choice_select = new Choice_select();
		choice_select->SetName(L"charator_redbox_cc");
		AddGameobeject(choice_select, jk_LayerType::BG);
		
		Scene::Initialize();

	}
	void ChatarcterChoiseSC::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			choice_music->Stop(true);
			Selec->Play(false);
			Act1_music->Play(true);
			SceneManager::LoadScene(jk_SceneType::GamePlay);
			CreateBlending();
		}
		Scene::Update();
	}
	void ChatarcterChoiseSC::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void ChatarcterChoiseSC::Release()
	{
		Scene::Release();
	}
	void ChatarcterChoiseSC::OnEnter()
	{
	}
	void ChatarcterChoiseSC::OnExit()
	{
	}
	void ChatarcterChoiseSC::CreateBlending()
	{
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}
}