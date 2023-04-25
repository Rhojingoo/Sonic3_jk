#include "act6_bullet1.h"
#include "jk_Transform.h"
#include "jk_Time.h"
#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Ground.h"
#include "Rigidbody.h"



namespace jk
{
	act6_bullet1::act6_bullet1()
		: mDir(-1)
	{
		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"boss1_bullet", mImage, Vector2{ 312,263}, Vector2{ 32,32 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->Play(L"boss1_bullet", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 90.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (-0.11f) * size.y });
		
	}

	act6_bullet1::~act6_bullet1()
	{
	}

	void act6_bullet1::Initialize()
	{
		Gameobject::Initialize();
	}


	void act6_bullet1::Update()
	{


		//switch (mState)
		//{
		//case jk::act6_bullet1::eBossState::Idle:idle();
		//	break;

		//case jk::act6_bullet1::eBossState::Up:up();
		//	break;

		//case jk::act6_bullet1::eBossState::Down:down();
		//	break;

		//default:
		//	break;
		//}

		Transform* Boss_TR = GetComponent<Transform>();
		Rigidbody* Boss_rb = GetComponent<Rigidbody>();
		pos = Boss_TR->GetPos();
		


		if (Boss_TR && Boss_rb && mGroundImage)
		{
			Vector2 Boss_ps = Boss_TR->GetPos();
			COLORREF FootColor = mGroundImage->GetPixel(Boss_ps.x-50, Boss_ps.y+70  );
			if (FootColor == RGB(0, 0, 0))
			{
				COLORREF FootColor = mGroundImage->GetPixel(Boss_ps.x-50, Boss_ps.y+70 );

				while (FootColor == RGB(0, 0, 0))
				{
					Boss_ps.y -= 1;
					FootColor = mGroundImage->GetPixel(Boss_ps.x-50, Boss_ps.y+70);
					Boss_TR->SetPos(Boss_ps);
					Boss_rb->SetGround(true);
				}
			}
			else
			{
				Boss_rb->SetGround(false);
			}
		}

		Gameobject::Update();
	}


	void act6_bullet1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void act6_bullet1::Release()
	{
		Gameobject::Release();
	}

	void act6_bullet1::idle()
	{
		//if (mDir == -1)
		//{
		//	mState = eBossState::Up;
		//}
		//else
		//{
		//	mState = eBossState::Down;
		//}
	}

	void act6_bullet1::up()
	{		
		//mRigidbody->SetVelocity(Vector2{ -200.f,-80.f });
		//mRigidbody->SetGround(false);
		//mDir = 1;
	}

	void act6_bullet1::down()
	{
		
		//mRigidbody->SetVelocity(Vector2{ -250.f,0.f });
		//mRigidbody->SetGround(false);
		//mDir = -1;
	}

	void act6_bullet1::OnCollisionEnter(Collider* other)
	{
	}
	void act6_bullet1::OnCollisionStay(Collider* other)
	{
	}
	void act6_bullet1::OnCollisionExit(Collider* other)
	{
	}

}