#include "Boss_Arm.h"
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
#include "jk_Input.h"
#include "jk_SONIC.h"

namespace jk
{
	Boss_Arm::Boss_Arm(Gameobject* owner)
		: mOwner(owner)
		, Boss_pos(0.f,0.f)
		, pos(0.f,0.f)
		, Damege_check(0)
		, moving_lotation(0)
		, grap(0)
		, mDir(0)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
	{
		mImage = Resources::Load<Image>(L"third_boss_R", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_R.bmp");
		mImage1 = Resources::Load<Image>(L"third_boss_L", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_L.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"R_Boss_arm", mImage, Vector2{ 308,296 }, Vector2{ 96,48 }, Vector2{ 0.f,8.f }, 1, 4, 4, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"R_Boss_arm_Hurt", mImage, Vector2{ 603,298 }, Vector2{ 96,40 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_GRAP", mImage, Vector2{ 308,440}, Vector2{ 96,40 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_arm", mImage1, Vector2{ 308,296 }, Vector2{ 96,48 }, Vector2{ 0.f,8.f }, 1, 4, 4, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"L_Boss_arm_Hurt", mImage1, Vector2{ 603,298 }, Vector2{ 96,40 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_GRAP", mImage1, Vector2{ 308,440 }, Vector2{ 96,40 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"R_Boss_arm_Hurt") = std::bind(&Boss_Arm::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss_arm_Hurt") = std::bind(&Boss_Arm::Hurt, this);
		mAnimator->Play(L"R_Boss_arm", true);
		

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(270.0f, 110.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.5f) * size.y });
	}
	Boss_Arm::~Boss_Arm()
	{
	}
	void Boss_Arm::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss_Arm::Update()
	{
		Boss_pos = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
		mDir;

		if (mDir == 1 && moving_lotation == 0)
		{
			mAnimator->Play(L"R_Boss_arm", true);
			Boss_pos = mOwner->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			pos = tr->GetPos();
			pos.x = (Boss_pos.x + 85.f);
			pos.y = (Boss_pos.y + 165.f);

			tr->SetPos(pos);
		}
		if (mDir == -1 && moving_lotation == 0)
		{
			mAnimator->Play(L"L_Boss_arm", true);
			Boss_pos = mOwner->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			pos = tr->GetPos();
			pos.x = (Boss_pos.x - 75.f); 
			pos.y = (Boss_pos.y + 165.f);
			
			tr->SetPos(pos);
		}
		if (Damege_check == 1)
		{
			if (Damege_check != 1)
				return;

			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_arm_Hurt", false);				
			}
			else if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_arm_Hurt", false);				
			}
		}
		else
		{
			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_arm", true);
			}
			else if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_arm", true);
			}
		}
		Gameobject::Update();		
	}


	void Boss_Arm::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Boss_Arm::Release()
	{
		Gameobject::Release();
	}

	void Boss_Arm::OnCollisionEnter(Collider* other)
	{
	}

	void Boss_Arm::OnCollisionStay(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			grap = 1;
			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_GRAP", true);
			}
			else if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_GRAP", true);
			}

			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_Pos = mSonic_Col->Getpos();
			Collider* Boss_Col = this->GetComponent<Collider>();
			Vector2 Boss_ColPos = Boss_Col->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			if (!(mSonic->Getsonicstate() == Sonic::eSonicState::Hurt))
			{
				sonic_Pos = pos;
				sonicTr->SetPos(sonic_Pos);
			}
			else
			{
				rb->SetGround(false);
				Vector2 velocity = rb->GetVelocity();
				velocity.x += 20.f;
				velocity.y -= 30.f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
				sonic_Pos = sonicTr->GetPos();
				sonic_Pos = sonic_Pos + Vector2{ 10.f ,-15.f };
				sonicTr->SetPos(sonic_Pos);
			}
		}
	}

	void Boss_Arm::OnCollisionExit(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			grap = 0;
			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_arm", true);

			}
			else if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_arm", true);
			}
		}

	}

	void Boss_Arm::Hurt()
	{
	}
}