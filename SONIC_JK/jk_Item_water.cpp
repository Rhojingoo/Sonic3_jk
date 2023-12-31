#include "jk_Item_water.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	Item_water::Item_water(Gameobject* owner)
		: mOwner(owner)
		, mItemcheck(1)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, itemmState(eState::Idle)
		, sonicState()
	{
	}
	Item_water::~Item_water()
	{
	}
	void Item_water::Initialize()
	{
		mImage = Resources::Load<Image>(L"Item", L"..\\Resources\\Item.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Water_Item", mImage, Vector2(492, 131), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"ItemDeath", mImage, Vector2(460, 216), Vector2(32, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Water_Item", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();
	}
	void Item_water::Update()
	{
		switch (itemmState)
		{
		case Item_water::eState::Idle:
			idle();
			break;

		case Item_water::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Item_water::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Item_water::Release()
	{
		Gameobject::Release();
	}
	void Item_water::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();


			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				if (itemmState == eState::Death)
					return;

				itemmState = eState::Death;
				mAnimator->Play(L"ItemDeath", true);
			}
		}
	}
	void Item_water::OnCollisionStay(Collider* other)
	{
	}
	void Item_water::OnCollisionExit(Collider* other)
	{
	}
	void Item_water::CreateBlending()
	{
	}
	void Item_water::idle()
	{
	}
	void Item_water::death()
	{
		mItemcheck = 2;
	}
}