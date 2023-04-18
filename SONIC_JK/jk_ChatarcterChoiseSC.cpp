#include "jk_ChatarcterChoiseSC.h"
#include "jk_Title.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_CharaterChoice.h"
#include "jk_ChoiceCC.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_Choice_select.h"


namespace jk
{
	ChatarcterChoiseSC::ChatarcterChoiseSC()
	{
	}
	ChatarcterChoiseSC::~ChatarcterChoiseSC()
	{
	}
	void ChatarcterChoiseSC::Initialize()
	{

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
			SceneManager::LoadScene(jk_SceneType::GamePlay);
			//CreateBlending();
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