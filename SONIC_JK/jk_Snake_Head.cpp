#include "jk_Snake.h"
#include "jk_Snake_Head.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Object.h"

#include "jk_Animal.h"

#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Sound.h"


namespace jk
{
	Snake_Head::Snake_Head(Vector2 _Pos)
		:  mCenterpos(_Pos)
		, mCurpos(Vector2(_Pos))
		, mMonmaxdistance_x(200.0f)
		, mMonmaxdistance_y(50.0f)
		, mDir_x(1)
		, mDir_y(1)
		, mState(eSnake::Idle)
		, sonicState()
		, tailsState()
		, mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
	{
	}

	Snake_Head::Snake_Head()
		:  mCenterpos(0.f, 0.f)
		, mCurpos(Vector2(0.f, 0.f))
		, mMonmaxdistance_x(200.0f)
		, mMonmaxdistance_y(50.0f)
		, mDir_x(1)
		, mDir_y(1)
		, mState(eSnake::Idle)
		, sonicState()
		, tailsState()
		, mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
	{
	}

	Snake_Head::~Snake_Head()
	{
	}

	void Snake_Head::Initialize()
	{
		Death = Resources::Load<Sound>(L"Monster_Death", L"..\\Resources\\Sound\\Sonic\\Monster_Death.wav");
		Death->Play(false);

		mImage = Resources::Load<Image>(L"Snake_head", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_head", mImage, Vector2{ 158.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_head", mImage, Vector2{ 24.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);

		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"snake_deth", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"deth2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);

		mAnimator->Play(L"RSnake_head", true);
		mAnimator->GetCompleteEvent(L"snake_deth") = std::bind(&Snake_Head::deth, this); 

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(75.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });

		tr = GetComponent<Transform>();
		mCenterpos = tr->GetPos();
		Gameobject::Initialize();
	}

	void Snake_Head::Update()
	{
		mCurpos = tr->GetPos();
		SetposSnake(mCurpos);

		switch (mState)
		{
		case jk::Snake_Head::eSnake::Idle:
			idle();
			break;

		case jk::Snake_Head::eSnake::Right:
			right();
			break;

		case jk::Snake_Head::eSnake::Left:
			left();
			break;

		case jk::Snake_Head::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}

	void Snake_Head::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Snake_Head::Release()
	{
		Gameobject::Release();
	}

	void Snake_Head::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"snake_deth", true);
				Death->Play(false);
			}
		}
		else if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			tailsState = tails->GetTails_state();

			if (tailsState == Tails::eTailsState::Dash || tailsState == Tails::eTailsState::Jump || tailsState == Tails::eTailsState::Spin || tailsState == Tails::eTailsState::Movejump)
			{
				mAnimator->Play(L"snake_deth", false);
				Death->Play(false);
			}
		}


	}
	void Snake_Head::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Head::OnCollisionExit(Collider* other)
	{
	}


	void Snake_Head::idle()
	{
		mState = eSnake::Right;
	}

	void Snake_Head::right()
	{
		Vector2 snake;
		Vector2 mDistance = Vector2{ mMonmaxdistance_x, mMonmaxdistance_y };

		float time = static_cast<float>(TimeSinceStart());
		float speed = 50.0f;
		float amplitude = 100.0f;
		float frequency = 2.f;
		mCurpos.x += speed * static_cast<float>(Time::DeltaTime());
		mCurpos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());

		float fDist_x = abs(mCenterpos.x - mCurpos.x) - mMonmaxdistance_x;
		if (fDist_x >= 300.0f)
		{
			mState = eSnake::Left;
			mDir_x = mDir_x * -1;
			mAnimator->Play(L"LSnake_head", true);
		}
		tr->SetPos(mCurpos);
	}


	void Snake_Head::left()
	{
		float time = static_cast<float>(TimeSinceStart());
		float speed = 50.0f;  // 이동 속도
		float amplitude = 100.0f;  // 진폭
		float frequency = 2.f;  // 주파수
		mCurpos.x -= speed * static_cast<float>(Time::DeltaTime());
		mCurpos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());

		float fDist_x = abs(mCenterpos.x - mCurpos.x) - mMonmaxdistance_x;
		if (fDist_x <= -100.0f)
		{
			mState = eSnake::Right;
			mDir_x = mDir_x * -1;
			mAnimator->Play(L"RSnake_head", true);
		}
		tr->SetPos(mCurpos);
	}


	void Snake_Head::deth()
	{		
		SetLife(false);
		release_animal();
	}


	void Snake_Head::release_animal()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(this);

		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);
		return;
	}
}
