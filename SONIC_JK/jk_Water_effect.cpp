#include "jk_Water_effect.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Image.h"

#include "jk_Object.h"
#include "jk_SONIC.h"


namespace jk
{
	Water_effect::Water_effect()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eState::Idle)
	{
		mImage = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Water_Effect_act1", mImage, Vector2(24, 370), Vector2(40, 32), Vector2(8, 0), 7, 1, 7, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Water_Effect_act1", false);
		mAnimator->GetCompleteEvent(L"Water_Effect_act1") = std::bind(&Water_effect::water_splashes, this);
	}
	Water_effect::~Water_effect()
	{
	}
	void Water_effect::Initialize()
	{
		Gameobject::Initialize();
	}

	void Water_effect::Update()
	{
		switch (mState)
		{
		case Water_effect::eState::Idle:
			idle();
			break;

		case Water_effect::eState::Death:
			death();
			break;
		default:
			break;
		}
		Gameobject::Update();
	}

	void Water_effect::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Water_effect::Release()
	{
		Gameobject::Release();
	}

	void Water_effect::idle()
	{
	}

	void Water_effect::death()
	{
		object::Destory(this);
	}

	void Water_effect::water_splashes()
	{
		mState = eState::Death;
	}
}