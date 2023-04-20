#include "jk_Last_Bridge.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"

namespace jk
{
	Last_Bridge::Last_Bridge()
	{
	}
	Last_Bridge::~Last_Bridge()
	{
	}


	void Last_Bridge::Initialize()
	{
		mImage = Resources::Load<Image>(L"bridge_last", L"..\\Resources\\last_bridge.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"bridge_last", mImage, Vector2(622, 91), Vector2(192, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"bridge_last", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(576.0f, 48.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}


	void Last_Bridge::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
	

		switch (mState)
		{
		case Last_Bridge::eState::Idle:
			idle();
			break;

		case Last_Bridge::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}

	void Last_Bridge::Render(HDC hdc)
	{



		Gameobject::Render(hdc);
	}

	void Last_Bridge::Release()
	{
		Gameobject::Release();
	}

	void Last_Bridge::OnCollisionEnter(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);


	}

	void Last_Bridge::OnCollisionStay(Collider* other)
	{
		
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* mSonic_Col = mSonic->GetComponent<Collider>();
		Vector2 mSonic_Pos = mSonic_Col->Getpos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->Getpos();

		Transform* sonicTr = mSonic->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();
		Vector2 sonic_Pos = sonicTr->GetPos();


	//	실험해볼것
		float fLen = fabs(sonic_Pos.y - groundPos.y);
		float fSize = (mSonic_Col->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			sonic_Pos.y -= (fSize - fLen) - 0.5f;
			sonicTr->SetPos(sonic_Pos);
		}

		if ((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt))
		{	
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -550.0f;

			rb->SetVelocity(velocity);
			rb->SetGround(false);

			sonic_Pos = sonicTr->GetPos();
			//sonic_Pos = sonic_Pos + Vector2{ 350.f ,-350.f };
			sonicTr->SetPos(sonic_Pos);

		}


	}

	void Last_Bridge::OnCollisionExit(Collider* other)
	{
	}

	void Last_Bridge::idle()
	{
	}

	void Last_Bridge::death()
	{
	}
}