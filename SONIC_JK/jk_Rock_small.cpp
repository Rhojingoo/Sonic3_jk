#include "jk_Rock_small.h"
#include "jk_Item.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_SONIC.h"
#include "jk_Rock_Pice.h"
#include "Rigidbody.h"
#include "jk_Ground.h"

float Random_rock(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}
float timer_RS = 0.0f; // Ÿ�̸� ����
float RS_DisappearTime = 20.0f; // ���� ������� �ð� (��)
float bounceForce_RS = 500.0f;
int check_ground_SR = 0;

namespace jk
{
	Rock_small::Rock_small()
	{
	}
	Rock_small::~Rock_small()
	{
	}

	void Rock_small::Initialize()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"small_Rock", mImage, Vector2(164, 578), Vector2(48, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"small_Rock", true);
		
		
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(130.0f, 95.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

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

		if (ROCK_TR && ROCK_rb && mGroundImage)
		{
			Vector2 ROCK_ps = ROCK_TR->GetPos();
			COLORREF RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y+55);
			if (RING_Color == RGB(0, 0, 0))
			{
				COLORREF RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y+55);

				while (RING_Color == RGB(0, 0, 0))
				{
					ROCK_ps.y -= 1;
					RING_Color = mGroundImage->GetPixel(ROCK_ps.x, ROCK_ps.y+55);
					ROCK_TR->SetPos(ROCK_ps);
					ROCK_rb->SetGround(true);
					check_ground_SR = 1;
				}
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
		
			Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner());
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{

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