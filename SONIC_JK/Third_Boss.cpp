#include "Third_Boss.h"
#include "Boss_act1_boomb.h"

#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "Rigidbody.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Ground.h"


namespace jk
{
	Third_Boss::Third_Boss()
		:mDir(1)
		, Boss_cross_change(0)
		, Grap_pattern(0)
		, Hur_check(0)
		, mSpeed(250)
	{

		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"third_boss_R", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_R.bmp");
		mImage1 = Resources::Load<Image>(L"third_boss_L", L"..\\Resources\\ActBG_6\\BOSS\\Third_boss3_L.bmp");



		mAnimator->CreateAnimation(L"R_Boss_Third", mImage, Vector2{ 600,0 }, Vector2{ 96,80 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"R_Boss_third_Hurt", mImage, Vector2{ 700,0 }, Vector2{ 100,80 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);


		mAnimator->CreateAnimation(L"L_Boss_Third", mImage1, Vector2{ 600,0 }, Vector2{ 96,80 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"L_Boss_third_Hurt", mImage1, Vector2{ 700,0 }, Vector2{ 100,80 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);


		mAnimator->GetCompleteEvent(L"R_Boss_third_Hurt") = std::bind(&Third_Boss::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss_third_Hurt") = std::bind(&Third_Boss::Hurt, this);



		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(270.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.5f) * size.y });


		mAnimator->Play(L"R_Boss_Third", true);
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
		pos = tr->GetPos();
				

		switch (mState)
		{
		case jk::Third_Boss::eBossState::Start:start();
			break;

		case jk::Third_Boss::eBossState::Left_Cross:L_cross();
			break;

		case jk::Third_Boss::eBossState::Right_Cross:R_cross();
			break;

		case jk::Third_Boss::eBossState::Left:left();
			break;

		case jk::Third_Boss::eBossState::Right:right();
			break;

		case jk::Third_Boss::eBossState::Grap_R:grap_R();
			break;

		case jk::Third_Boss::eBossState::Grap_L:grap_L();
			break;

		//case jk::Third_Boss::eBossState::Hurt:Hurt();
		//	break;

		case jk::Third_Boss::eBossState::Death:death();
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
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				Damege_check += 1;
				Hur_check = 1;

				if (Damege_check < 6)
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

				else if (Damege_check == 6)
				{
					mState = eBossState::Death;
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
		pos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.x >= 15150.0f)
		{
			mState = eBossState::Left_Cross;
				mAnimator->Play(L"L_Boss_Third", true);
				pos = Vector2{ 15150.f,5200.f };
				mDir = -1;
				Boss_cross_change = 1;	
		}
		tr->SetPos(pos);
	}

	void Third_Boss::L_cross()
	{
		Transform* tr = GetComponent<Transform>();
		pos.x -= mSpeed * static_cast<float>(Time::DeltaTime());

		if((pos.x > 13550.0f)&& (pos.x <= 14350.f))
		{
			pos.x -= mSpeed * static_cast<float>(Time::DeltaTime());
			pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		}
		else if (pos.x <= 13550.0f)
		{

			if (Boss_cross_change == 0)
			{
				mState = eBossState::Right_Cross;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,5200.f };
				mDir = 1;
				Boss_cross_change = 1;
			}
			else if (Boss_cross_change == 1)
			{
				mState = eBossState::Right;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,5200.f };
				mDir = 1;
				Boss_cross_change = 2;
			}
			//else if (Boss_cross_change == 2)
			//{
			//	mState = eBossState::Right;
			//	mAnimator->Play(L"R_Boss_Third", true);
			//	pos = Vector2{ 13550.0f,5400.f };
			//	mDir = 1;		
			//}
			else if (Grap_pattern == 1)
			{
				mState = eBossState::Grap_R;
				mAnimator->Play(L"L_Boss_Third", true);
				pos = Vector2{ 14350.0f,4500.f };
				Boss_cross_change = 0;
				mDir = 1;
			}
		}

		tr->SetPos(pos);
	}

	void Third_Boss::R_cross()
	{
		Transform* tr = GetComponent<Transform>();
		pos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if((pos.x >= 14350.f) &&(pos.x < 15510.f))
		{
			pos.x += mSpeed * static_cast<float>(Time::DeltaTime());
			pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		}
		else if(pos.x > 15150.f)
		{
			if (Boss_cross_change == 0)
			{
				mState = eBossState::Left_Cross;
				mAnimator->Play(L"L_Boss_Third", false);
				pos = Vector2{ 15150.f,5200.f };
				mDir = -1;
				Boss_cross_change = 1;
			}
			else if (Boss_cross_change == 1)
			{
				mState = eBossState::Left;
				mAnimator->Play(L"L_Boss_Third", false);
				pos = Vector2{ 15150.f,5200.f };
				mDir = -1;
				Boss_cross_change = 2;
			}

			//else if (Boss_cross_change == 2)
			//{
			//	mState = eBossState::Left;
			//	mAnimator->Play(L"L_Boss_Third", true);
			//	pos = Vector2{ 15150.f,5400.f };
			//	mDir = -1;			
			//}
			else if (Grap_pattern == 1)
			{
				mState = eBossState::Grap_L;
				mAnimator->Play(L"L_Boss_Third", true);
				pos = Vector2{ 14350.0f,4500.f };
				Boss_cross_change = 0;
				mDir = -1;
			}

		}
		tr->SetPos(pos);
	}

	void Third_Boss::left()
	{
		Transform* tr = GetComponent<Transform>();
		pos.x -= mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.x <= 13550.0f)
		{
			if (Boss_cross_change == 2)
			{
				mState = eBossState::Right_Cross;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,5200.f };
				mDir = 1;
				Boss_cross_change = 0;
			}
			else if (Grap_pattern == 1)
			{
				mState = eBossState::Grap_R;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,5200.f };
				Boss_cross_change = 0;
				mDir = 1;
			}
		}
		tr->SetPos(pos);
	}

	void Third_Boss::right()
	{
		Transform* tr = GetComponent<Transform>();
		pos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.x >= 15150.0f)
		{
			if (Boss_cross_change == 2)
			{
				mState = eBossState::Left_Cross;
				mAnimator->Play(L"L_Boss_Third", true);
				pos = Vector2{ 15150.f,5200.f };
				mDir = -1;
				Boss_cross_change = 0;
			}
			else if (Grap_pattern == 1)
			{
				mState = eBossState::Grap_L;
				mAnimator->Play(L"L_Boss_Third", true);
				pos = Vector2{ 14350.0f,4500.f };
				Boss_cross_change = 0;
				mDir = -1;
			}

		}
		tr->SetPos(pos);
	}


	void Third_Boss::grap_R()
	{
		Transform* tr = GetComponent<Transform>();
		pos.y += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y >= 6000.0f)
		{
			mState = eBossState::Right;
			mAnimator->Play(L"R_Boss_Third", true);
			pos = Vector2{ 13550.0f,5200.f };
			mDir = 1;
			Boss_cross_change = 0;
		}
		tr->SetPos(pos);
	}

	void Third_Boss::grap_L()
	{
		Transform* tr = GetComponent<Transform>();
		pos.y += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y >= 6000.0f)
		{
			mState = eBossState::Left;
			mAnimator->Play(L"L_Boss_Third", true);
			pos = Vector2{ 15150.f,5200.f };
			mDir = 1;
			Boss_cross_change = 0;
		}
		tr->SetPos(pos);
	}

	void Third_Boss::Hurt()
	{
		if (mDir == 1)
		{
			mAnimator->Play(L"R_Boss_Third", true);
			Hur_check = 0;
			
		}
		else
		{
			mAnimator->Play(L"L_Boss_Third", true);
			Hur_check = 0;
			
		}

		return;
	}

	void Third_Boss::death()
	{
		if (Boomb_point == 0)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Boss_act1_boomb* Boss2_boomb = new Boss_act1_boomb(this);
			Boss2_boomb->SetName(L"Boss2_boomb");
			Boss2_boomb->GetComponent<Transform>()->SetPos(pos);
			curScene->AddGameobeject(Boss2_boomb, jk_LayerType::Effect);
			Boomb_point = 1;
		}
		else if (Boomb_point == 1)
		{
			time += Time::DeltaTime();
			if (time >= 1)
			{
				mRigidbody = AddComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Boomb_point = 2;
			}
		}
	}
}