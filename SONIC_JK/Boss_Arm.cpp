#include "Boss_Arm.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Pixel_Ground.h"
#include "jk_Image.h"


#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_SONIC.h"

namespace jk
{
	Boss_Arm::Boss_Arm(Gameobject* owner)
		: mOwner(owner)
		, mBoss_pos(0.f,0.f)
		, mPos(0.f,0.f)
		, mDamege_check(0)
		, mMoving_lotation(0)
		, mGrap(0)
		, mDir(0)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mSonic_Tr(nullptr)
		, mSonic_RG(nullptr)
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
		mBoss_pos = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		mDir;

		if (mDir == 1 && mMoving_lotation == 0)
		{
			mAnimator->Play(L"R_Boss_arm", true);
			mBoss_pos = mOwner->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			mPos = tr->GetPos();
			mPos.x = (mBoss_pos.x + 85.f);
			mPos.y = (mBoss_pos.y + 165.f);

			tr->SetPos(mPos);
		}
		if (mDir == -1 && mMoving_lotation == 0)
		{
			mAnimator->Play(L"L_Boss_arm", true);
			mBoss_pos = mOwner->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			mPos = tr->GetPos();
			mPos.x = (mBoss_pos.x - 75.f); 
			mPos.y = (mBoss_pos.y + 165.f);
			
			tr->SetPos(mPos);
		}


		if (mGrap == 1)
		{
			Vector2 sonic_Pos = mSonic_Tr->GetPos();
			sonic_Pos = mPos;
			mSonic_Tr->SetPos(Vector2(sonic_Pos.x, sonic_Pos.y-50.f));
		}




		if (mDamege_check == 1)
		{
			if (mDamege_check != 1)
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
			mGrap = 1;
			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_GRAP", true);
			}
			else if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_GRAP", true);
			}

			mSonic_Tr = mSonic->GetComponent<Transform>();
			mSonic_RG = mSonic->GetComponent<Rigidbody>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = mSonic_Tr->GetPos();


			if ((mSonic->Getsonicstate() == Sonic::eSonicState::Hurt) ||
				(mSonic->Getsonicstate() == Sonic::eSonicState::Death))
			{
				mGrap = 0;
				mSonic_RG->SetGravity(Vector2{ 0.f,1000.f });
				mSonic_Tr->SetPos(Vector2(sonic_Pos.x, sonic_Pos.y - 150));
				mSonic_RG->SetGround(false);
				Vector2 velocity = mSonic_RG->GetVelocity();
				velocity = Vector2(0.0f, -500.0f);
				mSonic_RG->SetVelocity(velocity);
				mSonic_RG->SetGround(false);
				return;
			}

			else if ((mSonic->Getsonicstate() != Sonic::eSonicState::Hurt)  ||
				(mSonic->Getsonicstate() != Sonic::eSonicState::Death) )
			{
			
				mSonic_RG->SetGround(true);
				mSonic_RG->SetGravity(Vector2{ 0.f,100.f });

				Vector2 pos = tr->GetPos();
				Collider* mSonic_Col = mSonic->GetComponent<Collider>();
				Vector2 mSonic_Pos = mSonic_Col->Getpos();
				Collider* Boss_Col = this->GetComponent<Collider>();
				Vector2 Boss_ColPos = Boss_Col->Getpos();		
				mSonic_Pos.y = Boss_ColPos.y - 100;
				mSonic_Col->SetPos(mSonic_Pos);

				sonic_Pos =	Vector2 (pos.x, pos.y-100);
				mSonic_Tr->SetPos(sonic_Pos);
			}

		}
	}

	void Boss_Arm::OnCollisionExit(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mGrap = 0;
			mSonic_Tr = mSonic->GetComponent<Transform>();
			mSonic_RG = mSonic->GetComponent<Rigidbody>();
			mSonic_RG->SetGround(false);
			mSonic_RG->SetGravity(Vector2{ 0.f,1000.f });
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