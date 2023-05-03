#include "jk_Last_Bridge.h"


#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Camera.h"
#include "jk_Time.h"
#include "jk_Object.h"
#include "jk_Blending.h"

#include "jk_SONIC.h"
#include "jk_Tails.h"

#include "jk_BaseBullet.h"

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

		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			if (tails == nullptr)
				return;

			Rigidbody* rb = tails->GetComponent<Rigidbody>();
			rb->SetGround(true);
		}

		if (BaseBullet* basebullet = dynamic_cast<BaseBullet*>(other->GetOwner()))
		{
			object::Destory(this);
		}
	}

	void Last_Bridge::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_colPos = mSonic_Col->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Transform* grTr = this->GetComponent<Transform>();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 ground_colPos = groundCol->Getpos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);


			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.y = groundCol->Getpos().y - groundCol->GetSize().y - 50;
				sonicTr->SetPos(sonic_Pos);
			}

			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -650.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();
				sonicTr->SetPos(sonic_Pos);
			}
		}
		//if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		//{
		//	if (mSonic == nullptr)
		//		return;
		//	Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		//	rb->SetGround(true);
		//	Collider* mSonic_Col = mSonic->GetComponent<Collider>();
		//	Vector2 mSonic_Pos = mSonic_Col->Getpos();
		//	Transform* sonicTr = mSonic->GetComponent<Transform>();
		//	Vector2 sonic_Pos = sonicTr->GetPos();
		//	Collider* groundCol = this->GetComponent<Collider>();
		//	Vector2 groundPos = groundCol->Getpos();	
		//	Transform* grTr = this->GetComponent<Transform>();
		//	//	실험해볼것
		//	float fLen = fabs(sonic_Pos.y - groundPos.y);
		//	float fSize = (mSonic_Col->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);
		//	if (fLen < fSize)
		//	{
		//		sonic_Pos.y -= (fSize - fLen) - 0.5f;
		//		sonicTr->SetPos(sonic_Pos);
		//	}
		//	if ((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt))
		//	{
		//		Vector2 velocity = rb->GetVelocity();
		//		velocity.y = -550.0f;
		//		rb->SetVelocity(velocity);
		//		rb->SetGround(false);
		//		sonic_Pos = sonicTr->GetPos();
		//		//sonic_Pos = sonic_Pos + Vector2{ 350.f ,-350.f };
		//		sonicTr->SetPos(sonic_Pos);
		//	}
		//}

		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			if (tails == nullptr)
				return;

			Rigidbody* rb = tails->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Collider* tails_Col = tails->GetComponent<Collider>();
			Vector2 tails_colPos = tails_Col->Getpos();
			Transform* tailsTr = tails->GetComponent<Transform>();
			Vector2 tails_Pos = tailsTr->GetPos();


			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->Getpos();
			Transform* grTr = this->GetComponent<Transform>();


			//	실험해볼것
			float fLen = fabs(tails_Pos.y - groundPos.y);
			float fSize = (tails_Col->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			if (fLen < fSize)
			{
				tails_Pos.y -= (fSize - fLen) - 0.5f;
				tailsTr->SetPos(tails_Pos);
			}

			if (!((tails->GetTails_state() == Tails::eTailsState::Jump) || (tails->GetTails_state() == Tails::eTailsState::Movejump) || (tails->GetTails_state() == Tails::eTailsState::Hurt)))
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -550.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				tails_Pos = tailsTr->GetPos();
				tailsTr->SetPos(tails_Pos);
			}
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