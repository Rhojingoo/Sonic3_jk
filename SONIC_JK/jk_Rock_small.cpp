#include "jk_Rock_small.h"
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



float Random_rock(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}


namespace jk
{
	Rock_small::Rock_small()
		: Crash(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mState(eState::Idle)
		, check(nullptr)
		, sonicState()
		, timer_RS(0.f)// Ÿ�̸� ����
		, RS_DisappearTime(20.f)// ���� ������� �ð� (��)
		, bounceForce_RS(500.f)
		, check_ground_SR(0)
	{
		Crash = Resources::Load<Sound>(L"Crash", L"..\\Resources\\Sound\\Sonic\\Crash.wav");

		mImage = Resources::Load<Image>(L"Rock_Platform", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"small_Rock", mImage, Vector2(164, 578), Vector2(48, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"small_Rock", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(144.0f, 96.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
	}
	Rock_small::~Rock_small()
	{
	}

	void Rock_small::Initialize()
	{
		Gameobject::Initialize();
	}

	void Rock_small::Update()
	{
		switch (mState)
		{
		case Rock_small::eState::Idle:
			idle();
			break;

		case Rock_small::eState::Up:
			up();
			break;

		case Rock_small::eState::Death:
			death();
			break;

		default:
			break;
		}

		Transform* ROCK_TR = GetComponent<Transform>();
		Rigidbody* ROCK_rb = GetComponent<Rigidbody>();
		mGroundImage = check->GetGroundImage();
				
		//if (ROCK_TR && ROCK_rb && mGroundImage)
		//{
		//	Vector2 ROCK_ps = ROCK_TR->GetPos();
		//	COLORREF RING_Color = mGroundImage->GetPixel(static_cast<int>(ROCK_ps.x), static_cast<int>(ROCK_ps.y)+55);
		//	if (RING_Color == RGB(0, 0, 0))
		//	{
		//		ROCK_rb->SetGround(true);
		//		while (RING_Color == RGB(0, 0, 0))
		//		{
		//			ROCK_ps.y -= 1;
		//			//RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y+55);
		//			ROCK_TR->SetPos(ROCK_ps);
		//			check_ground_SR = 1;
		//		}
		//	}		
		//}

		if (ROCK_TR && ROCK_rb && mGroundImage)
		{
			Vector2 ROCK_ps = ROCK_TR->GetPos();
			COLORREF RING_Color = mGroundImage->GetPixel(static_cast<int>(ROCK_ps.x), static_cast<int>(ROCK_ps.y) + 55);
			if (RING_Color == RGB(0, 0, 0))
			{
				ROCK_rb->SetGround(true);
				do
				{
					ROCK_ps.y -= 1;
					//COLORREF RING_Color = mGroundImage->GetPixel(static_cast<int>(ROCK_ps.x), static_cast<int>(ROCK_ps.y) + 55);
					ROCK_TR->SetPos(ROCK_ps);
					check_ground_SR = 1;
				} while (RING_Color == RGB(0, 0, 0) && ROCK_ps.y <0);
			}
		}

		Gameobject::Update();
	}

	void Rock_small::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Rock_small::Release()
	{
		Gameobject::Release();
	}

	void Rock_small::OnCollisionEnter(Collider* other)
	{
		
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				Crash->Play(false);

				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();

				const int numRings = 4; // ������ ���� ����
				const float minAngle = -45.0f; // ���� �������� �ּ� ����
				const float maxAngle = 45.0f; // ���� �������� �ִ� ����
				const float distance = 150.0f; // ���� �������� �Ÿ�


				for (int i = 0; i < numRings; ++i)
				{
					float angle = Random_rock(minAngle, maxAngle); // �������� ������ �����ϰ� ����							
					Vector2 dropDirection = math::Rotate(Vector2{ 0.f,-1.f }, angle); // �������� ���� ���͸� ����

					Rock_Pice* Rock_pice = new Rock_Pice();
					Rock_pice->Initialize();
					curScene->AddGameobeject(Rock_pice, jk_LayerType::BG_props);

					if (check)// ���� ���� ������ �� ��Ȳ
					{
						Image* groundImage = check->GetGroundImage();
						Rock_pice->SetGroundImage(groundImage);
					}
					Vector2 dropPos = tr->GetPos() + (dropDirection * distance); // �������� ��ġ ���
					Rock_pice->GetComponent<Transform>()->SetPos(dropPos); // ���� ��ġ ����
				}
				mState = eState::Death;
			}
		}
		
		
	}

	void Rock_small::OnCollisionStay(Collider* other)
	{
	}

	void Rock_small::OnCollisionExit(Collider* other)
	{
	}

	void Rock_small::idle()
	{
	}
	void Rock_small::up()
	{
	}
	void Rock_small::death()
	{
		object::Destory(this);
	}

}