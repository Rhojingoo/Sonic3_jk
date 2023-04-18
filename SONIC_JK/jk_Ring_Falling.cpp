#include "jk_Ring_Falling.h"
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
#include "Rigidbody.h"

float timer = 0.0f; // Ÿ�̸� ����
float ringDisappearTime = 20.0f; // ���� ������� �ð� (��)
float bounceForce = 500.0f;
int check_ground = 0;


namespace jk
{
	Ring_Falling::Ring_Falling(Gameobject* owner)
	{
		mImage = Resources::Load<Image>(L"Ring_fall", L"..\\Resources\\Ring.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Ring_turn", mImage, Vector2(128, 303), Vector2(20, 16), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Ring_Eat", mImage, Vector2(128, 323), Vector2(20, 16), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"Ring_turn", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(65.0f, 60.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		timer = 0;
		
	}
	Ring_Falling::~Ring_Falling()
	{
		//if (groundImg)
		//	groundImg = nullptr;
	}
	void Ring_Falling::Initialize()
	{
		Gameobject::Initialize();
	}
	void Ring_Falling::Update()
	{
		Ringcheck;

		switch (Ring_State)
		{
		case Ring_Falling::eState::Idle:
			idle();
			break;

		case Ring_Falling::eState::Eat:
			eat();
			break;

		case Ring_Falling::eState::Death:
			death();
			break;

		default:
			break;
		}

		//��
		Transform* ring_TR = GetComponent<Transform>();
		Rigidbody* ring_rb = GetComponent<Rigidbody>();

		if (ring_TR && ring_rb && mGroundImage)
		{
			Vector2 Ring_ps = ring_TR->GetPos();
			COLORREF RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y);
			if (RING_Color == RGB(0, 0, 0))
			{
				COLORREF RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y);

				while (RING_Color == RGB(0, 0, 0))
				{
					Ring_ps.y -= 1;
					RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y);
					ring_TR->SetPos(Ring_ps);
					ring_rb->SetGround(true);
					check_ground = 1;

					if (ring_rb->GetGround()==true) // Ground ������ ��쿡�� ����
					{
						Vector2 bounceForceVec(0.0f, -bounceForce);
						ring_rb->SetVelocity(bounceForceVec);
						ring_rb->SetGround(false);										
					}	
				}
			}

		
			if (check_ground > 0)
			{
				timer += Time::DeltaTime();
				if (timer >= 30)
				{
					jk::object::Destory(this); // ���� �� ����
					return; // ���� �����Ǿ����Ƿ� �Ʒ��� �ڵ带 �������� �ʰ� �Լ� ����
				}
			}

		}	

		Gameobject::Update();
	}

	void Ring_Falling::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Ring_Falling::Release()
	{
		Gameobject::Release();
	}

	void Ring_Falling::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mAnimator->Play(L"Ring_Eat", false);

			Ring_State = eState::Eat;
		}
	}

	void Ring_Falling::OnCollisionStay(Collider* other)
	{
	}

	void Ring_Falling::OnCollisionExit(Collider* other)
	{
	}

	void Ring_Falling::CreateBlending()
	{
	}

	void Ring_Falling::idle()
	{
	}

	void Ring_Falling::eat()
	{
		mAnimator->GetCompleteEvent(L"Ring_Eat") = std::bind(&Ring_Falling::death, this);
		Ringcheck += 1;
	}

	void Ring_Falling::death()
	{
		object::Destory(this);
	}
}