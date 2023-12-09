#include "Robotnic_machine.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"

#include "jk_SONIC.h"

#include "jk_Blending.h"
#include "jk_Time.h"
#include "jk_Camera.h"


namespace jk
{
	Robotnic_machine::Robotnic_machine()
		:mSpeed(250)
		, pos(0.f, 0.f)
		, mImage()
		, mAnimator()
		, mState()
	{
	}
	Robotnic_machine::~Robotnic_machine()
	{
	}
	void Robotnic_machine::Initialize()
	{
		mImage = Resources::Load<Image>(L"fly_event", L"..\\Resources\\ActBG_6\\fly_event.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"fly_event_idle", mImage, Vector2(0, 0), Vector2(68, 64), Vector2(4, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"fly_event", mImage, Vector2(0, 0), Vector2(68, 64), Vector2(4, 0), 2, 1, 2, Vector2::Zero, 0.3f);

		mAnimator->Play(L"fly_event_idle", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(192.0f, 80.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (0.7f) * size.y });

		Gameobject::Initialize();
	}
	void Robotnic_machine::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();


		switch (mState)
		{
		case Robotnic_machine::eState::Idle:
			idle();
			break;

		case Robotnic_machine::eState::Move:
			move();
			break;

		case Robotnic_machine::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}


	void Robotnic_machine::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void Robotnic_machine::Release()
	{
		Gameobject::Release();
	}


	void Robotnic_machine::OnCollisionEnter(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			if (mSonic == nullptr)
				return;



			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
		}
	}


	void Robotnic_machine::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
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

			mState = eState::Move;
			mAnimator->Play(L"fly_event", true);


			float fLen = fabs(sonic_Pos.y - groundPos.y);
			float fSize = (mSonic_Col->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			if (fLen < fSize)
			{
				sonic_Pos.y -= (fSize - fLen) - 0.5f;
				sonicTr->SetPos(Vector2{ groundPos.x + groundCol->GetSize().y / 2.0f ,groundPos.y - groundCol->GetSize().y });
			}

			if ((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt))
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -550.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();
				sonicTr->SetPos(Vector2{ sonic_Pos.x,sonic_Pos.y - 100 });
			}
		}
	}

	void Robotnic_machine::OnCollisionExit(Collider* other)
	{
	}

	void Robotnic_machine::idle()
	{
	}

	void Robotnic_machine::move()
	{
		Transform* tr = GetComponent<Transform>();

		pos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		tr->SetPos(pos);
	}

	void Robotnic_machine::death()
	{
	}
}