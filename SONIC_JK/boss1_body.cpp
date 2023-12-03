#include "boss1_body.h"
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

#include "jk_Object.h"
#include "jk_Ground.h"
#include "jk_Time.h"


namespace jk
{
	jk::boss1_body::boss1_body()
		: Boss_Hit(nullptr)
		, Boss_Bomb(nullptr)
		, Boss_Start(nullptr)
		, Act6_music(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, boss_ob(nullptr)

		, pos(0.f,0.f)
		, sonicState()
		, mState(eBossState::Idle)
		, Damege_check(0)
		, Death_point(0)
		, time(0)
		, check_map(0)
	{
	}

	jk::boss1_body::~boss1_body()
	{
	}

	void jk::boss1_body::Initialize()
	{
		Boss_Hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		Boss_Bomb = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
		Boss_Start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		Act6_music = Resources::Load<Sound>(L"Act6_bg", L"..\\Resources\\Sound\\Act6_bg.wav");

		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Boss1_open", mImage, Vector2{ 597,120 }, Vector2{ 64,96 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_up", mImage, Vector2{ 665,120 }, Vector2{ 68,96 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_hurt", mImage, Vector2{ 869,226 }, Vector2{68,96}, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"Boss1_idle", mImage, Vector2{ 869,120 }, Vector2{ 64,96 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"Boss1_death", mImage, Vector2{ 324,378 }, Vector2{ 64,48 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->Play(L"Boss1_open", true);


		mAnimator->GetCompleteEvent(L"Boss1_up") = std::bind(&boss1_body::idle, this);
		mAnimator->GetCompleteEvent(L"Boss1_hurt") = std::bind(&boss1_body::idle, this);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(180.0f, 60.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (2.3f) * size.y });
	

		Gameobject::Initialize();
	}
	

	void jk::boss1_body::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		check_map = check->Get_map_check();
		mGroundImage = check->GetGroundImage4();


		switch (mState)
		{

		case jk::boss1_body::eBossState::Move:move();
			break;

		case jk::boss1_body::eBossState::Death:death();
			break;

		case jk::boss1_body::eBossState::Attack_Up:attack_up();
			break;

		case jk::boss1_body::eBossState::Attack_Down:attack_down();
			break;

		default:
			break;
		}


		Gameobject::Update();
	}

	void jk::boss1_body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void jk::boss1_body::Release()
	{
		Gameobject::Release();
	}

	void jk::boss1_body::OnCollisionEnter(Collider* other)
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
			boss_ob = new boss1_object(this);
			boss_ob->SetName(L"boss_ob");
			curScene->AddGameobeject(boss_ob, jk_LayerType::BOSS);
			boss_ob->GetComponent<Transform>()->SetPos(Vector2{ 6050.f, 5560.f });
			boss_ob->SetGroundImage(mGroundImage);
		}


		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				Damege_check += 1;
				Boss_Hit->Play(false);
				

				if (Damege_check <= 6)
				{
					hurt();
					mAnimator->Play(L"Boss1_hurt", false);
				}

				if (Damege_check >= 7)
				{
					mAnimator->Play(L"Boss1_death", true);
					mState = eBossState::Death;					
				}	
			}
		}
	}

	void jk::boss1_body::OnCollisionStay(Collider* other)
	{
	}

	void jk::boss1_body::OnCollisionExit(Collider* other)
	{
	}

	void jk::boss1_body::idle()
	{
		mAnimator->Play(L"Boss1_idle", false);
	}

	void jk::boss1_body::move()
	{
	}

	void boss1_body::hurt()
	{

	}

	void boss1_body::death()
	{
		Collider* collider =GetComponent<Collider>();
		collider->SetSize(Vector2(0.0f, 0.0f));

		Boss_Start->Stop(true);		
		Boss_Bomb->Play(false);

		Boss_act1_boomb* boomb = new Boss_act1_boomb(this);
		if (Death_point == 0)
		{
			Scene* curScene1 = SceneManager::GetActiveScene();
			Boss_act1_boomb* boomb = new Boss_act1_boomb(this);
			boomb->SetName(L"boomb_boss1");
			curScene1->AddGameobeject(boomb, jk_LayerType::Effect);
			boomb->GetComponent<Transform>()->SetPos(pos);

			Death_point = 1;
			boss_ob->Set_Deathpoint(Death_point);
		}

		else if (Death_point == 1)
		{
			time += Time::DeltaTime();
			if (time >= 3)
			{
				mRigidbody = AddComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				mRigidbody->SetVelocity(Vector2{ 0.f,-1500.f });
				mRigidbody->SetGround(false);
				boss_ob->Set_Deathpoint(Death_point);
			}
		}
		boss_ob->Set_Deathpoint(Death_point);
	}

	void jk::boss1_body::attack_up()
	{
	}

	void jk::boss1_body::attack_down()
	{
	}
}