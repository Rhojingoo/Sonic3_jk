#include "finall_stage.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "Rigidbody.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"

#include "jk_Time.h"
#include "jk_Tails.h"




namespace jk
{
	finall_stage::finall_stage()
		:check_map(0)
		, mSpeed(30)
		, pos(0.f,0.f)
		, end(0)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, Rocket_Start(nullptr)
		, mState()
	{
	}
	finall_stage::~finall_stage()
	{
	}
	void finall_stage::Initialize()
	{
		Rocket_Start = Resources::Load<Sound>(L"Rocket_Start", L"..\\Resources\\Sound\\Rocket_Start.wav");

		mImage = Resources::Load<Image>(L"Last_stage", L"..\\Resources\\ActBG_6\\last_stage.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Last_stage", mImage, Vector2{ 0,0 }, Vector2{1920,640 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Last_stage_end", mImage, Vector2{ 0,0 }, Vector2{ 1924,640 }, Vector2{ 4,0 }, 4, 2, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Last_stage_ending", mImage, Vector2{ 5772,640 }, Vector2{ 1920,640 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Last_stage", true);
		mAnimator->GetCompleteEvent(L"Last_stage_end") = std::bind(&finall_stage::Ending, this);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(960.0f, 100.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (3.85f) * size.x, (6.0f) * size.y });

		Gameobject::Initialize();
	}
	void finall_stage::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();		

		switch (mState)
		{
		case jk::finall_stage::eBossState::Idle:idle();
			break;

		case jk::finall_stage::eBossState::Move:move();
			break;


		case jk::finall_stage::eBossState::Death:death();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}

	void finall_stage::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void finall_stage::Release()
	{
		Gameobject::Release();
	}


	void finall_stage::OnCollisionEnter(Collider* other)
	{
	}
	void finall_stage::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);


			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_Pos = mSonic_Col->Getpos();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);


			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.y = groundCol->Getpos().y- groundCol->GetSize().y;
				sonicTr->SetPos(sonic_Pos);
			}

			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -550.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();
				sonicTr->SetPos(sonic_Pos);

			}
		}

		if (Tails* mTails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Rigidbody* rb = mTails->GetComponent<Rigidbody>();
			rb->SetGround(true);


			Collider* mTails_Col = mTails->GetComponent<Collider>();
			Vector2 mTails_Pos = mTails_Col->Getpos();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 groundPos = groundCol->Getpos();
			Transform* mTailsTr = mTails->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 Tails_Pos = mTailsTr->GetPos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);
		

			if (!((mTails->GetTails_state() == Tails::eTailsState::Jump) || mTails->GetTails_state() == Tails::eTailsState::Movejump))
			{
				Tails_Pos.y = groundCol->Getpos().y - groundCol->GetSize().y;
				mTailsTr->SetPos(Tails_Pos);
			}
			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -550.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				Tails_Pos = mTailsTr->GetPos();
				mTailsTr->SetPos(Tails_Pos);
			}
		}
	}
	void finall_stage::OnCollisionExit(Collider* other)
	{
	}

	void finall_stage::Bomb()
	{
	}


	void finall_stage::idle()
	{
		if (check_map == 1)
		{
			mState = eBossState::Move;
		}
		if (end == 1)
		{
			mState = eBossState::Death;
			mAnimator->Play(L"Last_stage_end", false);			
		}
	}


	void finall_stage::move()
	{
		Transform* tr = GetComponent<Transform>();

		pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		Rocket_Start->Play(true);

		if (pos.y <= 4950.0f)
		{
			check_map = 2;
			mState = eBossState::Idle;
			Rocket_Start->Stop(false);
		}

		tr->SetPos(pos);
	}

	void finall_stage::death()
	{
		end = 2;
		mState = eBossState::Idle;
	}
	void finall_stage::Ending()
	{
	}
}