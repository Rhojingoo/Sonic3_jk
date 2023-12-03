#include "jk_Cylinder.h"
#include "jk_Resources.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Camera.h"
#include "jk_SONIC.h"

namespace jk
{
	Cylinder::Cylinder()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eState::Idle)
		, mRigidbody(nullptr)
	{
	}
	Cylinder::~Cylinder()
	{
	}

	void Cylinder::Initialize()
	{
		mImage = Resources::Load<Image>(L"Cylinder", L"..\\Resources\\Cylinder.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Cylinder_on", mImage, Vector2(11, 43), Vector2(256, 512), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Cylinder_off", mImage, Vector2(275, 43), Vector2(256, 512), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"Cylinder_on", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(768.0f, 1536.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}


	void Cylinder::Update()
	{
		switch (mState)
		{
		case Cylinder::eState::Idle:
			idle();
			break;

		case Cylinder::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}

	void Cylinder::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Cylinder::Release()
	{
		Gameobject::Release();
	}

	void Cylinder::OnCollisionEnter(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mState = eState::Death;
			mAnimator->Play(L"Cylinder_off", true);
		}
	}
	void Cylinder::OnCollisionStay(Collider* other)
	{
	}
	void Cylinder::OnCollisionExit(Collider* other)
	{
	}
	void Cylinder::idle()
	{
	}
	void Cylinder::death()
	{
	}
}
