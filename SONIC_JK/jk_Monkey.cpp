#include "jk_Monkey.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Animator.h"

#include "jk_Object.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Pixel_Ground.h"
#include "jk_Monkey_Bullet.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Sound.h"
#include "jk_Animal.h"


namespace jk
{
	Monkey::Monkey(Gameobject* owner)
		: mState()
		, mCenterpos(Vector2(12280.0f, 3111.0f))
		, mPos(0.f, 0.f)
		, mSonic_Pos(0.f, 0.f)
		, mMonspeed(50.0f)
		, mMonmaxdistance(70.0f)
		, fDist(0.f)
		, mDir(1)
		, mDeath_point(0)
		, mAnimal_point(0)
		, mSonicPattern(-1)
		, sonicState()
		, tailsState()
		, mOwner(owner)
		, mPixel_Ground(nullptr)
		, mDeath(nullptr)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mTr(nullptr)
		, mBullet(nullptr)
		, mBullet_tr(nullptr)
		, mBullet_rb(nullptr)

	{


	}
	Monkey::~Monkey()
	{
	}
	void Monkey::Initialize()
	{
		mDeath = Resources::Load<Sound>(L"Monster_Death", L"..\\Resources\\Sound\\Sonic\\Monster_Death.wav");


		mImage = Resources::Load<Image>(L"MONKEY", L"..\\Resources\\Monster2.bmp");
		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RMonkey", mImage, Vector2{ 20.f,150.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LMonkey", mImage, Vector2{ 20.f,18.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RMonkey_throw", mImage, Vector2{ 20.f,213.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"LMonkey_throw", mImage, Vector2{ 20.f,81.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.05f);

		mAnimator->CreateAnimation(L"death", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"deth2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);

		mAnimator->GetCompleteEvent(L"LMonkey_throw") = std::bind(&Monkey::throw_CompleteEvent, this);
		mAnimator->GetCompleteEvent(L"death") = std::bind(&Monkey::release_animal, this);

		mAnimator->Play(L"LMonkey", true);

		mTr = GetComponent<Transform>();

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(153.0f, 130.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });


		mBullet = new Monkey_Bullet(mOwner);
		mBullet_tr = mBullet->GetComponent<Transform>();
		mBullet_rb = mBullet->GetComponent<Rigidbody>();
		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameobeject(mBullet, jk_LayerType::Bullet);
		mBullet->SetState(eState::Pause);

		Gameobject::Initialize();
	}

	void Monkey::Update()
	{
		mGroundImage = mPixel_Ground->GetGroundImage();
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		if (mDeath_point == 1)
		{
			mState = eMonkey::Death;
			mAnimator->Play(L"death", false);
		}


		mSonic_Pos = mOwner->GetComponent<Transform>()->GetPos();
		if (mSonic_Pos.x <= mPos.x)
		{
			mSonicPattern = -1;
		}
		else if (mSonic_Pos.x > mPos.x)
		{
			mSonicPattern = 1;
		}

		switch (mState)
		{
		case jk::Monkey::eMonkey::L_Move_UP:
			Lmove_up();
			break;

		case jk::Monkey::eMonkey::L_Move_DOWN:
			Lmove_down();
			break;

		case jk::Monkey::eMonkey::L_Throw:
			Lthrows();
			break;

		case jk::Monkey::eMonkey::R_Throw:
			Rthrows();
			break;

		case jk::Monkey::eMonkey::Turn:
			turn();
			break;

		case jk::Monkey::eMonkey::Death:
			death();
			break;

		default:
			break;
		}

		Setpos_monster(mPos);
		Gameobject::Update();
	}

	void Monkey::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Monkey::Release()
	{
		Gameobject::Release();
	}

	void Monkey::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"death", false);
				mSonicPattern;
				mDeath_point = 1;
				mDeath->Play(false);
			}
		}

		else if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			tailsState = tails->GetTails_state();

			if (tailsState == Tails::eTailsState::Dash || tailsState == Tails::eTailsState::Jump || tailsState == Tails::eTailsState::Spin || tailsState == Tails::eTailsState::Movejump)
			{
				mDeath->Play(false);
				mAnimator->Play(L"death", false);
				mDeath_point = 1;
			}
		}


	}
	void Monkey::OnCollisionStay(Collider* other)
	{
	}
	void Monkey::OnCollisionExit(Collider* other)
	{
	}


	void Monkey::Lmove_up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
		mPos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist >= 30.0f)
		{
			mState = eMonkey::L_Throw;
			mAnimator->Play(L"LMonkey_throw", false);
			mDir *= -1;
		}

		tr->SetPos(mPos);
	}

	void Monkey::Lmove_down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
		mPos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -100.0f)
		{
			mState = eMonkey::L_Throw;
			mAnimator->Play(L"LMonkey_throw", false);
			mDir *= -1;
		}

		tr->SetPos(mPos);
	}

	void Monkey::Lthrows()
	{
	}

	void Monkey::Rthrows()
	{
	}

	void Monkey::turn()
	{
		if (mDir == -1)
		{
			mState = eMonkey::L_Move_UP;
			mAnimator->Play(L"LMonkey", true);
		}
		if (mDir == 1)
		{
			mState = eMonkey::L_Move_DOWN;
			mAnimator->Play(L"LMonkey", true);
		}
	}


	void Monkey::death()
	{
		if (mAnimal_point == 0)
		{
			mDeath_point = 2;
		}
	}

	void Monkey::throw_CompleteEvent()
	{
		if (mSonicPattern == -1)
		{
			mBullet->SetState(eState::Active);
			mBullet_tr->SetPos(Vector2{ mTr->GetPos() });
			mBullet_rb->SetVelocity(Vector2{ 0.f, 0.f });
			mBullet_rb->SetVelocity(Vector2{ -300.0f, -300.0f });
			mBullet->SetGroundImage(mGroundImage);
		}
		else if (mSonicPattern == 1)
		{
			mBullet->SetState(eState::Active);
			mBullet_tr->SetPos(Vector2{ mTr->GetPos() });
			mBullet_rb->SetVelocity(Vector2{ 0.f, 0.f });
			mBullet_rb->SetVelocity(Vector2{ 300.0f, -300.0f });
			mBullet->SetGroundImage(mGroundImage);
		}

		mState = eMonkey::Turn;
	}

	void Monkey::release_animal()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(mOwner);
		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);

		object::Destory(this);
	}
}

