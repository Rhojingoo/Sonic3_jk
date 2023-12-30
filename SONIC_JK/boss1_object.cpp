#include "boss1_object.h"


#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"
#include "jk_Pixel_Ground.h"

#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"

#include "jk_Boss.h"
#include "boss_come.h"
#include "First_Boss.h"
#include "act6_bullet1.h"
#include "jk_SONIC.h"

namespace jk
{
	boss1_object::boss1_object(Gameobject* owner)
		: mDir(1)
		, mTime(0)
		, mAttack_lotation(0)
		, mAttack_check(1)
		, mDeath_point(0)
		, mBullet_check(0)
		, mPos(0.f, 0.f)
		, mState(eBossState::Idle)
		, mBoss(nullptr)
		, mBullet1(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mBullet(nullptr)

	{
		mBoss = dynamic_cast<First_Boss*>(owner);

		mBullet1 = Resources::Load<Sound>(L"Bullet1", L"..\\Resources\\Sound\\Bullet1.wav");

		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"boss1_idle_ob", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_OPEN_Up", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_OPEN_Down", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_CLOSE", mImage, Vector2{ 665,453 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);

		mAnimator->GetCompleteEvent(L"Boss1_OPEN_Up") = std::bind(&boss1_object::attack_up, this);
		mAnimator->GetCompleteEvent(L"Boss1_OPEN_Down") = std::bind(&boss1_object::attack_down, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(0.0f, 0.0f));
		Vector2 size = mCollider->GetSize();
		mCollider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.85f) * size.y });


		Scene* curScene = SceneManager::GetActiveScene();
		mBullet = new act6_bullet1();
		mBullet->SetName(L"bullet_boss1");
		mBullet->SetState(eState::Active);
		//mBullet->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 52.f, mPos.y + 50 });
		mBullet->SetGroundImage(mGroundImage);
		curScene->AddGameobeject(mBullet, jk_LayerType::Bullet);
		mBullet->SetState(eState::Pause);
	}

	boss1_object::~boss1_object()
	{
	}

	void boss1_object::Initialize()
	{
		Gameobject::Initialize();
	}



	void boss1_object::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		mDeath_point = mBoss->Get_BossDeath();


		if (mDeath_point == 1)
		{
			object::Destory(this);
		}

		if (mDeath_point == 0)
		{
			switch (mState)
			{
			case jk::boss1_object::eBossState::Idle:idle();
				break;

			case jk::boss1_object::eBossState::Up:up();
				break;

			case jk::boss1_object::eBossState::Down:down();
				break;

			default:
				break;
			}
		}
		Gameobject::Update();
	}


	void boss1_object::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void boss1_object::Release()
	{
		Gameobject::Release();
	}


	void boss1_object::OnCollisionEnter(Collider* other)
	{

	}


	void boss1_object::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);

			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_Pos = mSonic_Col->Getpos();

			Vector2 groundPos = mCollider->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);

			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.y = mCollider->Getpos().y - mCollider->GetSize().y - 50;
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


	void boss1_object::OnCollisionExit(Collider* other)
	{
	}


	void boss1_object::idle()
	{

		if (mDir == 1)
		{
			mState = eBossState::Up;
			if (mAttack_check == 1)
			{
				mAnimator->Play(L"Boss1_OPEN_Up", false);
				mAttack_check = -1;
			}

			else if (mAttack_check == -1)
			{
				mAnimator->Play(L"Boss1_OPEN_Down", false);
				mAttack_check = 1;
			}

			mCollider->SetSize(Vector2(144.0f, 60.0f));
			Vector2 size = mCollider->GetSize();
			mCollider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.85f) * size.y });
		}
		else if (mDir == 0)
		{
			mState = eBossState::Down;
			mAnimator->Play(L"Boss1_CLOSE", false);

			mCollider = GetComponent<Collider>();
			mCollider->SetSize(Vector2(0.f, 0.0f));
		}
	}


	void boss1_object::up()
	{
		if (mAttack_lotation == 0)
		{
			mAttack_lotation = 1;
		}
		if (mBullet_check >= 1)
		{
			mTime += static_cast<float>(Time::DeltaTime());
			if (mTime >= 3)
			{
				mState = eBossState::Idle;
				mTime = 0;
				mBullet_check = 0;
				mDir = 0;
			}
		}
	}
	void boss1_object::down()
	{
		mTime += static_cast<float>(Time::DeltaTime());
		if (mTime >= 3)
		{
			mState = eBossState::Idle;
			mTime = 0;
			mDir = 1;
			mAttack_lotation = 0;
		}
	}

	void boss1_object::attack_up()
	{
		if (mBullet_check == 0)
		{
			mBullet1->Play(false);
			mBullet->SetState(eState::Active);
			mBullet->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 52.f, mPos.y - 100.f });
			mBullet->SetGroundImage(mGroundImage);
			mBullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,-150.f });
			mBullet->GetComponent<Rigidbody>()->SetGround(false);

			mBullet_check = 1;
		}
	}

	void boss1_object::attack_down()
	{
		if (mBullet_check == 0)
		{
			mBullet1->Play(false);
			mBullet->SetState(eState::Active);
			mBullet->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 52.f, mPos.y + 50 });
			mBullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,0.f });
			mBullet->GetComponent<Rigidbody>()->SetGround(false);

			mBullet_check = 1;
		}


		mTime += static_cast<int>(Time::DeltaTime());
		if (mTime >= 3)
		{
			mState = eBossState::Idle;
			mTime = 0;
			mBullet_check = 0;
			mDir = 0;
		}
	}
}