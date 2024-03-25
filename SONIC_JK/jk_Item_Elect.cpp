#include "jk_Item_Elect.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	Item_Elect::Item_Elect(Gameobject* owner)
		: mOwner(owner)
		, mItemcheck(1)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, itemmState(eState::Idle)
		, sonicState()
	{

	}

	Item_Elect::~Item_Elect()
	{
	}

	void Item_Elect::Initialize()
	{
		mImage = Resources::Load<Image>(L"Item", L"..\\Resources\\Item.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"ElectItem", mImage, Vector2(565, 131), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"ItemDeath", mImage, Vector2(460, 216), Vector2(32, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"ElectItem", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();

	}
	void Item_Elect::Update()
	{
		switch (itemmState)
		{
		case Item_Elect::eState::Idle:
			idle();
			break;

		case Item_Elect::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}

	void Item_Elect::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Item_Elect::Release()
	{
		Gameobject::Release();
	}

	void Item_Elect::OnCollisionEnter(Collider* other)
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

	void Item_Elect::OnCollisionStay(Collider* other)
	{
	}

	void Item_Elect::OnCollisionExit(Collider* other)
	{
	}

	void Item_Elect::CreateBlending()
	{
	}

	void Item_Elect::idle()
	{
	}

	void Item_Elect::death()
	{
		mItemcheck = 2;
	}
}
