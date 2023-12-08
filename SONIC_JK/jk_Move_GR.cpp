#include "jk_Move_GR.h"

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

namespace jk
{
	Move_GR::Move_GR()
		: mCenterpos(Vector2(0.0f, 0.0f))	
		, pos(Vector2(0.0f, 0.0f))
		, mMonspeed(100.0f)
		, mMonmaxdistance(200.0f)
		, fDist(0.f)
		, mDir(1)	
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState()
	{
	}
	Move_GR::~Move_GR()
	{
	}
	void Move_GR::Initialize()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform2", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"small_gr", mImage, Vector2(660, 682), Vector2(64, 40), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"small_gr", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(192.0f, 40.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });		

		Gameobject::Initialize();
	}
	void Move_GR::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();


		switch (mState)
		{
		case Move_GR::eState::Up:
			up();
			break;

		case Move_GR::eState::Down:
			down();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Move_GR::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Move_GR::Release()
	{
		Gameobject::Release();
	}

	void Move_GR::OnCollisionEnter(Collider* other)
	{
		

	}
	void Move_GR::OnCollisionStay(Collider* other)
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
		
		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Rigidbody* rb = tails->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Collider* tails_Col = tails->GetComponent<Collider>();
			Vector2 tails_colPos = tails_Col->Getpos();
			Transform* tailsTr = tails->GetComponent<Transform>();
			Vector2 tails_Pos = tailsTr->GetPos();


			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Transform* grTr = this->GetComponent<Transform>();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 ground_colPos = groundCol->Getpos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);


			if (!((tails->GetTails_state() == Tails::eTailsState::Jump) || (tails->GetTails_state() == Tails::eTailsState::Movejump) || (tails->GetTails_state() == Tails::eTailsState::Hurt)))
			{
				tails_Pos.y = groundCol->Getpos().y - groundCol->GetSize().y - 50;
				tailsTr->SetPos(tails_Pos);
			}

			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -650.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				tails_Pos = tailsTr->GetPos();
				tailsTr->SetPos(tails_Pos);
			}
		}
	}
	void Move_GR::OnCollisionExit(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}

	void Move_GR::up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= mMonmaxdistance)
		{
			mState = eState::Down;
			mDir *= -1;
		}
		tr->SetPos(pos);

	}
	void Move_GR::down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -mMonmaxdistance)
		{
			mState = eState::Up;
			mDir *= -1;
		}
		tr->SetPos(pos);
	}
}