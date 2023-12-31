#include "jk_Item_Fire.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	Item_Fire::Item_Fire(Gameobject* owner)
		: mOwner(owner)
		, mItemcheck(1)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, itemmState(eState::Idle)
		, sonicState()
	{
	}
	Item_Fire::~Item_Fire()
	{
	}
	void Item_Fire::Initialize()
	{
		mImage = Resources::Load<Image>(L"Item", L"..\\Resources\\Item.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Fire_Item", mImage, Vector2(528, 131), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"ItemDeath", mImage, Vector2(460, 216), Vector2(32, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Fire_Item", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();

	}
	void Item_Fire::Update()
	{
		switch (itemmState)
		{
		case Item_Fire::eState::Idle:
			idle();
			break;

		case Item_Fire::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Item_Fire::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Item_Fire::Release()
	{
		Gameobject::Release();
	}
	void Item_Fire::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				itemmState = eState::Death;
				mAnimator->Play(L"ItemDeath", true);
			}
		}
	}
	void Item_Fire::OnCollisionStay(Collider* other)
	{
	}
	void Item_Fire::OnCollisionExit(Collider* other)
	{
	}
	void Item_Fire::CreateBlending()
	{
	}
	void Item_Fire::idle()
	{
	}
	void Item_Fire::death()
	{
		mItemcheck = 2;
	}
}