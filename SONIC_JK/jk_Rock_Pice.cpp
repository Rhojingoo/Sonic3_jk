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
#include "jk_SONIC.h"


namespace jk
{
	Rock_Pice::Rock_Pice()
		: mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, check(nullptr)
		, timer_rock(0.f)
		, bounce_Force(300.f)
		, check_gr(0)
	{
		mImage = Resources::Load<Image>(L"Rock_Pice", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Rock_Pice1", mImage, Vector2(211, 634), Vector2(24, 24), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Rock_Pice2", mImage, Vector2(244, 634), Vector2(24, 24), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Rock_Pice1", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		timer_rock = 0;
	}

	Rock_Pice::~Rock_Pice()
	{
	}

	void Rock_Pice::Initialize()
	{
		Gameobject::Initialize();
	}
	void Rock_Pice::Update()
	{
		Transform* rock_TR = GetComponent<Transform>();
		Rigidbody* rock_rb = GetComponent<Rigidbody>();

		if (rock_TR && rock_rb && mGroundImage)
		{
			Vector2 Ring_ps = rock_TR->GetPos();
			COLORREF RING_Color = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Ring_ps.x), static_cast<int>(Ring_ps.y + 24)));
			if (RING_Color == RGB(0, 0, 0))
			{
				RING_Color = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Ring_ps.x), static_cast<int>(Ring_ps.y + 24)));

				while (RING_Color == RGB(0, 0, 0))
				{
					Ring_ps.y -= 1;
					RING_Color = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Ring_ps.x), static_cast<int>(Ring_ps.y + 24)));
					rock_TR->SetPos(Ring_ps);
					rock_rb->SetGround(true);
					check_gr = 1;

					if (rock_rb->GetGround() == true)
					{
						Vector2 bounceForceVec(0.0f, -bounce_Force);
						rock_rb->SetVelocity(bounceForceVec);
						rock_rb->SetGround(false);
					}
				}
			}

			if (check_gr > 0)
			{
				timer_rock += static_cast<float>(Time::DeltaTime());
				if (timer_rock >= 15)
				{
					jk::object::Destory(this);
					return;
				}
			}
		}
		Gameobject::Update();
	}
	void Rock_Pice::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Rock_Pice::Release()
	{
		Gameobject::Release();
	}
}
