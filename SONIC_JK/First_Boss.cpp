#include "First_Boss.h"
#include "boss1_object.h"
#include "boss_come.h"
#include "Boss_act1_boomb.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"

#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"
#include "jk_Object.h"
#include "jk_Pixel_Ground.h"
#include "jk_Time.h"


namespace jk
{
	jk::First_Boss::First_Boss()
		: mBoss_Hit(nullptr)
		, mBoss_Bomb(nullptr)
		, mBoss_Start(nullptr)
		, mAct6_music(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mBoss_Object(nullptr)

		, mPos(0.f, 0.f)
		, sonicState()
		, mState(eBossState::Idle)
		, mDamege_check(0)
		, mDeath_point(0)
		, mTime(0)
		, mCheck_Map(0)
	{
	}

	jk::First_Boss::~First_Boss()
	{
	}

	void jk::First_Boss::Initialize()
	{
		mBoss_Hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		mBoss_Bomb = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
		mBoss_Start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		mAct6_music = Resources::Load<Sound>(L"Act6_bg", L"..\\Resources\\Sound\\Act6_bg.wav");

		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Boss1_open", mImage, Vector2{ 597,120 }, Vector2{ 64,96 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_up", mImage, Vector2{ 665,120 }, Vector2{ 68,96 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_hurt", mImage, Vector2{ 869,226 }, Vector2{ 68,96 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"Boss1_idle", mImage, Vector2{ 869,120 }, Vector2{ 64,96 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"Boss1_death", mImage, Vector2{ 324,378 }, Vector2{ 64,48 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->Play(L"Boss1_open", true);

		mAnimator->GetCompleteEvent(L"Boss1_up") = std::bind(&First_Boss::idle, this);
		mAnimator->GetCompleteEvent(L"Boss1_hurt") = std::bind(&First_Boss::idle, this);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGround(true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(180.0f, 60.0f));
		Vector2 size = mCollider->GetSize();
		mCollider->SetCenter(Vector2{ (-0.1f) * size.x, (2.3f) * size.y });


		Gameobject::Initialize();
	}


	void jk::First_Boss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		mCheck_Map = mPixelGround->Get_map_check();
		mGroundImage = mPixelGround->GetGroundImage4();


		switch (mState)
		{

		case First_Boss::eBossState::Move:
			move();
			break;

		case First_Boss::eBossState::Death:
			death();
			break;

		case First_Boss::eBossState::Attack_Up:
			attack_up();
			break;

		case First_Boss::eBossState::Attack_Down:
			attack_down();
			break;

		default:
			break;
		}


		Gameobject::Update();
	}

	void jk::First_Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void jk::First_Boss::Release()
	{
		Gameobject::Release();
	}

	void jk::First_Boss::OnCollisionEnter(Collider* other)
	{

		if (boss_come* robotnic = dynamic_cast<boss_come*>(other->GetOwner()))
		{
			mAnimator->Play(L"Boss1_up", false);
			mState = eBossState::Move;

			Collider* collider = GetComponent<Collider>();
			collider->SetSize(Vector2(180.0f, 282.0f));
			Vector2 size = collider->GetSize();
			collider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.3f) * size.y });



			Scene* curScene = SceneManager::GetActiveScene();
			mBoss_Object = new boss1_object(this);
			mBoss_Object->SetName(L"boss_ob");
			curScene->AddGameobeject(mBoss_Object, jk_LayerType::BOSS);
			mBoss_Object->GetComponent<Transform>()->SetPos(Vector2{ 6050.f, 5560.f });
			mBoss_Object->SetGroundImage(mGroundImage);
		}


		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mDamege_check += 1;
				mBoss_Hit->Play(false);


				if (mDamege_check <= 1)
				{
					hurt();
					mAnimator->Play(L"Boss1_hurt", false);
				}

				if (mDamege_check >= 1)
				{
					mAnimator->Play(L"Boss1_death", true);
					mState = eBossState::Death;
				}
			}
		}
	}

	void jk::First_Boss::OnCollisionStay(Collider* other)
	{
	}

	void jk::First_Boss::OnCollisionExit(Collider* other)
	{
	}

	void jk::First_Boss::idle()
	{
		mAnimator->Play(L"Boss1_idle", false);
	}

	void jk::First_Boss::move()
	{
	}

	void First_Boss::hurt()
	{

	}

	void First_Boss::death()
	{
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(0.0f, 0.0f));

		mBoss_Start->Stop(true);
		mBoss_Bomb->Play(false);

		if (mDeath_point == 0)
		{
			Scene* curScene1 = SceneManager::GetActiveScene();
			Boss_act1_boomb* boomb = new Boss_act1_boomb(this);
			boomb->SetName(L"boomb_boss1");
			curScene1->AddGameobeject(boomb, jk_LayerType::Effect);
			boomb->GetComponent<Transform>()->SetPos(mPos);

			mDeath_point = 1;
			mBoss_Object->Set_Deathpoint(mDeath_point);
		}

		else if (mDeath_point == 1)
		{
			mTime += static_cast<float>(Time::DeltaTime());
			if (mTime >= 3)
			{
				mRigidbody->SetGround(false);
				mRigidbody->SetVelocity(Vector2{ 0.f,-1500.f });
				mBoss_Object->Set_Deathpoint(mDeath_point);
			}
		}
		mBoss_Object->Set_Deathpoint(mDeath_point);
	}

	void jk::First_Boss::attack_up()
	{
	}

	void jk::First_Boss::attack_down()
	{
	}
}