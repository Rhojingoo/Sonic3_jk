#include "jk_Rock_big.h"
#include "jk_Rock_Pice.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Object.h"

#include "jk_Ground.h"
#include "jk_SONIC.h"

float timer_RB = 0.0f; // 타이머 변수
float Rb_DisappearTime = 20.0f; // 링이 사라지는 시간 (초)
float bounceForce_Rb = 500.0f;
int check_ground_BR = 0;

float Random_big_rock(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}


namespace jk
{
	Rock_big::Rock_big()
	{
	}

	Rock_big::~Rock_big()
	{
	}

	void Rock_big::Initialize()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Big_Rock", mImage, Vector2(276, 578), Vector2(48, 80), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"Big_Rock", true);


		Collider* collider = AddComponent<Collider>();		
		collider->SetSize(Vector2(144.0f, 240.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}

	void Rock_big::Update()
	{
		switch (mState)
		{
		case Rock_big::eState::Idle:
			idle();
			break;

		case Rock_big::eState::Up:
			up();
			break;

		case Rock_big::eState::Death:
			death();
			break;

		default:
			break;
		}

		Transform* ROCK_TR = GetComponent<Transform>();
		Rigidbody* ROCK_rb = GetComponent<Rigidbody>();
		mGroundImage = check->GetGroundImage();

		if (ROCK_TR && ROCK_rb && mGroundImage)
		{
			Vector2 ROCK_ps = ROCK_TR->GetPos();
			COLORREF RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y + 160);
			if (RING_Color == RGB(0, 0, 0))
			{
				COLORREF RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y + 160);

				while (RING_Color == RGB(0, 0, 0))
				{
					ROCK_ps.y -= 1;
					RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y + 160);
					ROCK_TR->SetPos(ROCK_ps);
					ROCK_rb->SetGround(true);
					check_ground_BR = 1;
				}
			}
		}

		Gameobject::Update();
	}

	void Rock_big::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Rock_big::Release()
	{
		Gameobject::Release();
	}

	void Rock_big::OnCollisionEnter(Collider* other)
	{
		Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
		sonicState = sonic->Getsonicstate();

		if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
		{

			Transform* tr = GetComponent<Transform>();
			Scene* curScene = SceneManager::GetActiveScene();

			const int numRings = 8; // 생성할 돌의 개수
			const float minAngle = -45.0f; // 돌이 떨어지는 최소 각도
			const float maxAngle = 45.0f; // 돌이 떨어지는 최대 각도
			const float distance = 100.0f; // 돌이 떨어지는 거리


			for (int i = 0; i < numRings; ++i)
			{
				float angle = Random_big_rock(minAngle, maxAngle); // 떨어지는 각도를 랜덤하게 결정							
				Vector2 dropDirection = math::Rotate(Vector2{ 0.f,-1.f }, angle); // 떨어지는 방향 벡터를 구함

				Rock_Pice* Rock_pice = new Rock_Pice();
				//Rock_pice->Initialize();
				curScene->AddGameobeject(Rock_pice, jk_LayerType::BG_props);

				if (check)// 돌이 땅에 닿을때 의 상황
				{
					Image* groundImage = check->GetGroundImage();
					Rock_pice->SetGroundImage(groundImage);
				}
				Vector2 dropPos = tr->GetPos() + (dropDirection * distance); // 떨어지는 위치 계산
				Rock_pice->GetComponent<Transform>()->SetPos(dropPos); // 돌의 위치 설정
			}
			mState = eState::Death;
		}
	}

	void Rock_big::OnCollisionStay(Collider* other)
	{
	}

	void Rock_big::OnCollisionExit(Collider* other)
	{
	}

	void Rock_big::idle()
	{
	}

	void Rock_big::up()
	{
	}

	void Rock_big::death()
	{
		object::Destory(this);
	}
}