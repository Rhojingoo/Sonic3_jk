#include "finall_stage.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "Rigidbody.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Ground.h"


namespace jk
{
	finall_stage::finall_stage()
		:check_map(0)
		, mSpeed(50)
	{
	}
	finall_stage::~finall_stage()
	{
	}
	void finall_stage::Initialize()
	{
		mImage = Resources::Load<Image>(L"Last_stage", L"..\\Resources\\ActBG_6\\last_stage.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Last_stage", mImage, Vector2{ 0,0 }, Vector2{1920,640 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Last_stage", true);

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
	}
	void finall_stage::OnCollisionExit(Collider* other)
	{
	}

	void finall_stage::idle()
	{
		if (check_map == 1)
		{
			mState = eBossState::Move;
		}
	}


	void finall_stage::move()
	{
		Transform* tr = GetComponent<Transform>();

		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		//pos.x += mSpeed/2 * static_cast<float>(Time::DeltaTime());

		if (pos.y <= 4950.0f)
		{
			check_map = 2;
			mState = eBossState::Idle;
		}

		tr->SetPos(pos);
	}

	void finall_stage::death()
	{
	}
}