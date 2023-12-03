#include "JK_TitleSN.h"
#include "jk_Titlesonic.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_Time.h"
#include "jk_Input.h"

namespace jk
{
	TitleSN::TitleSN()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 300.0f,505.0f });
		mImage = Resources::Load<Image>(L"TTSN", L"..\\Resources\\Title\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"TTSN", mImage, Vector2(671, 534), Vector2(297, 99), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"TTSN", true);
		
	}

	TitleSN::~TitleSN()
	{
	}

	void TitleSN::Initialize()
	{
		Gameobject::Initialize();
	}

	void TitleSN::Update()
	{
		Gameobject::Update();
	}

	void TitleSN::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void TitleSN::Release()
	{
		Gameobject::Release();
	}
}