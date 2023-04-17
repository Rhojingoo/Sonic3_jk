#include "jk_Snake.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "SonicState.h"
#include "jk_BaseBullet.h"
#include "jk_Animal.h"
#include "jk_Object.h"

double TimeSinceStart()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	return static_cast<double>(counter.QuadPart) / static_cast<double>(frequency.QuadPart);
}



namespace jk
{
	Snake::Snake(Gameobject* owner)
		: mCenterpos(Vector2(8370.f, 3250.f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(150.0f)
		, mMonmaxdistance_x(200.0f)
		, mMonmaxdistance_y(50.0f)
		, mDir_x(1)
		, mDir_y(1)
	{
	}
	//3000
	Snake::~Snake()
	{
	}

	void Snake::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_head", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_head", mImage, Vector2{ 158.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_head", mImage, Vector2{ 24.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		mAnimator->Play(L"RSnake_head", true);



		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"snake_deth", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"deth2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);


		Gameobject::Initialize();
	}

	void Snake::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos( );

			
 		switch (mState)
		{
		case jk::Snake::eSnake::Idle:
			idle();
			break;
		
		case jk::Snake::eSnake::Right_Up:
			right_up();
			break;
		
		case jk::Snake::eSnake::Right_Down:
			right_down();
			break;
		
		case jk::Snake::eSnake::Left_Up:
			left_up();
			break;

		case jk::Snake::eSnake::Left_Down:
			left_down();
			break;

		case jk::Snake::eSnake::Deth:
			deth();
			break;
		
		default:
			break;
		}
		Gameobject::Update();
	}

	void Snake::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Snake::Release()
	{
		Gameobject::Release();
	}

	void Snake::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"snake_deth", true);
				mAnimator->GetCompleteEvent(L"snake_deth") = std::bind(&Snake::deth, this); //Canon_death2
			}
		}
	}

	void Snake::OnCollisionStay(Collider* other)
	{
	}

	void Snake::OnCollisionExit(Collider* other)
	{
	}

	Vector2 Snake::GetPrevPos()
	{
		return prevPos;
	}



	void Snake::idle()
	{
		mState = eSnake::Right_Up;
	}

	void Snake::right_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mCurpos = pos;
		Vector2 snake;
		Vector2 mDistance = Vector2{ mMonmaxdistance_x, mMonmaxdistance_y };

		//배회거리 기준량을 넘어섰는지 확인		
		//fDist = abs(mCenterpos.y - pos.y) - mMonmaxdistance_y;
		//pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_y;
		//pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_x;
		//
		//if (fDist >= 30.0f)
		//{
		//	mState = eSnake::Right_Down;
		//	mDir_y*-1;
		//}
		float time = static_cast<float>(TimeSinceStart());
		float speed = 50.0f;  // 이동 속도
		float amplitude = 100.0f;  // 진폭
		float frequency = 2.f;  // 주파수
		pos.x += speed * static_cast<float>(Time::DeltaTime());
		pos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());

		float fDist_x = abs(mCenterpos.x - pos.x) - mMonmaxdistance_x;
		if (fDist_x >= 300.0f)
		{
			mState = eSnake::Left_Up;
			mDir_x * -1;
			mAnimator->Play(L"LSnake_head", true);
		}


		tr->SetPos(pos);
	}

	void Snake::right_down()
	{
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		//mCurpos = pos;
		//Vector2 snake;
		////Vector2 mDistance = Vector2{ mMonmaxdistance_x, mMonmaxdistance_y };

		////배회거리 기준량을 넘어섰는지 확인		
		//fDist = abs(mCenterpos.y - pos.y) - mMonmaxdistance_y;
		//pos.y += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_y;
		//pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_x;

		//if (fDist <= -30.0f)
		//{
		//	mState = eSnake::Right_Up;
		//	mDir_y * -1;
		//}

		//float fDist_x = abs(mCenterpos.x - pos.x) - mMonmaxdistance_x;
		//if (fDist_x >= 300.0f)
		//{
		//	mState = eSnake::Left_Up;
		//	mDir_x * -1;
		//	mAnimator->Play(L"LSnake_head", true);
		//}
		//tr->SetPos(pos);
	}

	void Snake::left_up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mCurpos = pos;
		Vector2 snake;
		//Vector2 mDistance = Vector2{ mMonmaxdistance_x, mMonmaxdistance_y };

		//배회거리 기준량을 넘어섰는지 확인		
		//fDist = abs(mCenterpos.y - pos.y) - mMonmaxdistance_y;
		//pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_y;
		//pos.x -= mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_x;

		//if (fDist >= 30.0f)
		//{
		//	mState = eSnake::Left_Down;
		//	mDir_y * -1;
		//}
		float time = static_cast<float>(TimeSinceStart());
		float speed = 50.0f;  // 이동 속도
		float amplitude = 100.0f;  // 진폭
		float frequency = 2.f;  // 주파수
		pos.x -= speed * static_cast<float>(Time::DeltaTime());
		pos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());



		float fDist_x = abs(mCenterpos.x - pos.x) - mMonmaxdistance_x;
		if (fDist_x <= -100.0f)
		{
			mState = eSnake::Right_Up;
			mDir_x * -1;
			mAnimator->Play(L"RSnake_head", true);
		}
		tr->SetPos(pos);
	}

	void Snake::left_down()
	{
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		//mCurpos = pos;
		//Vector2 snake;
		////Vector2 mDistance = Vector2{ mMonmaxdistance_x, mMonmaxdistance_y };

		////배회거리 기준량을 넘어섰는지 확인		
		//fDist = abs(mCenterpos.y - pos.y) - mMonmaxdistance_y;
		//pos.y += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_y;
		//pos.x -= mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir_x;

		//if (fDist <= -30.0f)
		//{
		//	mState = eSnake::Left_Up;
		//	mDir_y * -1;
		//}

		//float fDist_x = abs(mCenterpos.x - pos.x) - mMonmaxdistance_x;
		//if (fDist_x <= -100.0f)
		//{
		//	mState = eSnake::Right_Up;
		//	mDir_x * -1;
		//	mAnimator->Play(L"RSnake_head", true);
		//}

		//tr->SetPos(pos);
	}

	void Snake::deth()
	{
		jk::object::Destory(this);

		Snake::release_animal();
	}

	void Snake::throw_CompleteEvent()
	{
	}

	void Snake::release_animal()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(mOwner);

		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);
		return;
	}
}
