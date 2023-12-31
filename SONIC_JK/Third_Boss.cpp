#include "Third_Boss.h"
#include "Boss_act1_boomb.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "Rigidbody.h"
#include "jk_Pixel_Ground.h"
#include "jk_Object.h"
#include "jk_Time.h"


#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Sound.h"

namespace jk
{
	Third_Boss::Third_Boss()
		: mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mBoss_Hit(nullptr)
		, mBoss_Bomb(nullptr)
		, mSonicState()
		, mState()
		, mPos(0.f, 0.f)
		, mTime(0.f)
		, mSpeed(250.f)
		, mDir(1)
		, mBoss_cross_change(0)
		, mDamege_check(0)
		, mBoomb_point(0)
		, mGrap_pattern(0)
		, mHurt_check(0)
		, mEnding_point(0)
	{
		mBoss_Hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		mBoss_Bomb = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"third_boss_R", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_R.bmp");
		mImage1 = Resources::Load<Image>(L"third_boss_L", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_L.bmp");

		mAnimator->CreateAnimation(L"R_Boss_Third", mImage, Vector2{ 600,0 }, Vector2{ 96,80 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"R_Boss_third_Hurt", mImage, Vector2{ 700,0 }, Vector2{ 100,80 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_Third", mImage1, Vector2{ 600,0 }, Vector2{ 96,80 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"L_Boss_third_Hurt", mImage1, Vector2{ 700,0 }, Vector2{ 100,80 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"R_Boss_third_Hurt") = std::bind(&Third_Boss::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss_third_Hurt") = std::bind(&Third_Boss::Hurt, this);
		mAnimator->Play(L"R_Boss_Third", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(270.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.5f) * size.y });
	}

	Third_Boss::~Third_Boss()
	{
	}

	void Third_Boss::Initialize()
	{
		Gameobject::Initialize();
	}

	void Third_Boss::Update()
	{
		Transform* tr = GetComponent<Transform>();


		mPos = tr->GetPos();


		switch (mState)
		{
		case Third_Boss::eBossState::Start:
			start();
			break;

		case Third_Boss::eBossState::Left_Cross:
			L_cross();
			break;

		case Third_Boss::eBossState::Right_Cross:
			R_cross();
			break;

		case Third_Boss::eBossState::Left:
			left();
			break;

		case Third_Boss::eBossState::Right:
			right();
			break;

		case Third_Boss::eBossState::Grap_R:
			grap_R();
			break;

		case Third_Boss::eBossState::Grap_L:
			grap_L();
			break;

		case Third_Boss::eBossState::Death:
			death();
			break;

		case Third_Boss::eBossState::Ending:
			ending();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}


	void Third_Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Third_Boss::Release()
	{
		Gameobject::Release();
	}

	void Third_Boss::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mSonicState = sonic->Getsonicstate();

			if (mSonicState == Sonic::eSonicState::Dash || mSonicState == jk::Sonic::eSonicState::Jump || mSonicState == jk::Sonic::eSonicState::Spin)
			{
				mDamege_check += 1;
				mHurt_check = 1;
				mBoss_Hit->Play(false);

				Transform* sonicTr = sonic->GetComponent<Transform>();
				Vector2 sonic_Pos = sonicTr->GetPos();
				Rigidbody* sonicrb = sonic->GetComponent<Rigidbody>();
				sonicrb->SetVelocity(Vector2(0.f, -550.f));


				if (mDamege_check < 6)
				{
					if (mDir == 1)
					{
						mAnimator->Play(L"R_Boss_third_Hurt", false);
					}
					else
					{
						mAnimator->Play(L"L_Boss_third_Hurt", false);
					}
				}

				else if (mDamege_check == 6)
				{
					mState = eBossState::Death;
					if (mDir == 1)
					{
						mAnimator->Play(L"R_Boss_third_Hurt", false);
					}
					else
					{
						mAnimator->Play(L"L_Boss_third_Hurt", false);
					}
				}
			}
		}

	}

	void Third_Boss::OnCollisionStay(Collider* other)
	{
	}
	void Third_Boss::OnCollisionExit(Collider* other)
	{
	}

	void Third_Boss::start()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if (mPos.x >= 15150.0f)
		{
			mState = eBossState::Left_Cross;
			mAnimator->Play(L"L_Boss_Third", true);
			mPos = Vector2{ 15150.f,5400.f };
			mDir = -1;
			mBoss_cross_change = 1;
		}
		tr->SetPos(mPos);
	}

	void Third_Boss::L_cross()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.x -= mSpeed * static_cast<float>(Time::DeltaTime());

		if ((mPos.x > 13550.0f) && (mPos.x <= 14350.f))
		{
			mPos.x -= mSpeed * static_cast<float>(Time::DeltaTime());
			mPos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		}
		else if (mPos.x <= 13550.0f)
		{
			 if (mGrap_pattern == 1)
			{
				 mState = eBossState::Grap_R;
				 mAnimator->Play(L"L_Boss_Third", true);
				 mPos = Vector2{ 14350.0f,4500.f };
				 mBoss_cross_change = 0;
				 mDir = 1;
			 }
			 else
			 {
				 if (mBoss_cross_change == 0)
				 {
					 mState = eBossState::Right_Cross;
					 mAnimator->Play(L"R_Boss_Third", true);
					 mPos = Vector2{ 13550.0f,5300.f };
					 mDir = 1;
					 mBoss_cross_change = 1;
				 }
				 else if (mBoss_cross_change == 1)
				 {
					 mState = eBossState::Right;
					 mAnimator->Play(L"R_Boss_Third", true);
					 mPos = Vector2{ 13550.0f,5300.f };
					 mDir = 1;
					 mBoss_cross_change = 2;
				 }
			 }
		}

		tr->SetPos(mPos);
	}

	void Third_Boss::R_cross()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if ((mPos.x >= 14350.f) && (mPos.x < 15510.f))
		{
			mPos.x += mSpeed * static_cast<float>(Time::DeltaTime());
			mPos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		}
		else if (mPos.x > 15150.f)
		{			
			 if (mGrap_pattern == 1)
			{
				mState = eBossState::Grap_L;
				mAnimator->Play(L"L_Boss_Third", true);
				mPos = Vector2{ 14350.0f,4500.f };
				mBoss_cross_change = 0;
				mDir = -1;
			}
			 else
			 {
				 if (mBoss_cross_change == 0)
				 {
					 mState = eBossState::Left_Cross;
					 mAnimator->Play(L"L_Boss_Third", false);
					 mPos = Vector2{ 15150.f,5300.f };
					 mDir = -1;
					 mBoss_cross_change = 1;
				 }
				 else if (mBoss_cross_change == 1)
				 {
					 mState = eBossState::Left;
					 mAnimator->Play(L"L_Boss_Third", false);
					 mPos = Vector2{ 15150.f,5300.f };
					 mDir = -1;
					 mBoss_cross_change = 2;
				 }
			 }

		}
		tr->SetPos(mPos);
	}

	void Third_Boss::left()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.x -= mSpeed * static_cast<float>(Time::DeltaTime());

		if (mPos.x <= 13550.0f)
		{
			if (mGrap_pattern == 1)
			{
				mState = eBossState::Grap_R;
				mAnimator->Play(L"R_Boss_Third", true);
				mPos = Vector2{ 14350.0f,4500.f };
				mBoss_cross_change = 0;
				mDir = 1;
			}
			else
			{
				if (mBoss_cross_change == 2)
				{
					mState = eBossState::Right_Cross;
					mAnimator->Play(L"R_Boss_Third", true);
					mPos = Vector2{ 13550.0f,5300.f };
					mDir = 1;
					mBoss_cross_change = 0;
				}
			}
		}
		tr->SetPos(mPos);
	}

	void Third_Boss::right()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if (mPos.x >= 15150.0f)
		{
			if (mGrap_pattern == 1)
			{
				mState = eBossState::Grap_L;
				mAnimator->Play(L"L_Boss_Third", true);
				mPos = Vector2{ 14350.0f,4500.f };
				mBoss_cross_change = 0;
				mDir = -1;
			}
			else 
			{

				if (mBoss_cross_change == 2)
				{
					mState = eBossState::Left_Cross;
					mAnimator->Play(L"L_Boss_Third", true);
					mPos = Vector2{ 15150.f,5300.f };
					mDir = -1;
					mBoss_cross_change = 0;
				}

			}
		}
		tr->SetPos(mPos);
	}


	void Third_Boss::grap_R()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.y += 3*mSpeed * static_cast<float>(Time::DeltaTime());

		if (mPos.y >= 6000.0f)
		{
			mState = eBossState::Right;
			mAnimator->Play(L"R_Boss_Third", true);
			mPos = Vector2{ 13550.0f,5300.f };
			mDir = 1;
			mBoss_cross_change = 2;
		}
		tr->SetPos(mPos);
	}

	void Third_Boss::grap_L()
	{
		Transform* tr = GetComponent<Transform>();
		mPos.y +=3* mSpeed * static_cast<float>(Time::DeltaTime());

		if (mPos.y >= 6000.0f)
		{
			mState = eBossState::Left;
			mAnimator->Play(L"L_Boss_Third", true);
			mPos = Vector2{ 15150.f,5300.f };
			mDir = -1;
			mBoss_cross_change = 2;
		}
		tr->SetPos(mPos);
	}

	void Third_Boss::Hurt()
	{
		if (mDir == 1)
		{
			mAnimator->Play(L"R_Boss_Third", true);
			mHurt_check = 0;

		}
		else
		{
			mAnimator->Play(L"L_Boss_Third", true);
			mHurt_check = 0;
		}

		return;
	}

	void Third_Boss::death()
	{
		if (mBoomb_point == 0)
		{
			mBoss_Bomb->Play(true);

			Scene* curScene = SceneManager::GetActiveScene();
			Boss_act1_boomb* Boss2_boomb = new Boss_act1_boomb(this);
			Boss2_boomb->SetName(L"Boss2_boomb");
			Boss2_boomb->GetComponent<Transform>()->SetPos(mPos);
			curScene->AddGameobeject(Boss2_boomb, jk_LayerType::Effect);
			mBoomb_point = 1;
		}
		else if (mBoomb_point == 1)
		{
			mTime += static_cast<float>(Time::DeltaTime());
			if (mTime >= 1)
			{
				mRigidbody = AddComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				mBoomb_point = 2;
			}
		}

		if ((mBoomb_point == 2) && (mPos.y > 6000))
		{
			mEnding_point = 1;
			mBoomb_point = 3;
		}
	}
	void Third_Boss::ending()
	{


	}
}