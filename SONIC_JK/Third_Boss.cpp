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


namespace jk
{
	Third_Boss::Third_Boss()
		: mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, Boss_Hit(nullptr)
		, Boss_Bomb(nullptr)
		, sonicState()
		, mState()
		, pos(0.f, 0.f)
		, time(0.f)
		, mSpeed(250.f)
		, mDir(1)
		, Boss_cross_change(0)
		, Damege_check(0)
		, Boomb_point(0)
		, Grap_pattern(0)
		, Hur_check(0)
		, Ending_point(0)
	{
		Boss_Hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		Boss_Bomb = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
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

		case jk::Third_Boss::eBossState::Ending:ending();
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
				Boss_Hit->Play(false);

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
		pos.x += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.x >= 15150.0f)
		{
			mState = eBossState::Left_Cross;
			mAnimator->Play(L"L_Boss_Third", true);
			pos = Vector2{ 15150.f,5400.f };
			mDir = -1;
			Boss_cross_change = 1;
		}
		tr->SetPos(pos);
	}

	void Third_Boss::L_cross()
	{
		Transform* tr = GetComponent<Transform>();
		pos.x -= mSpeed * static_cast<float>(Time::DeltaTime());

		if ((pos.x > 13550.0f) && (pos.x <= 14350.f))
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
				pos = Vector2{ 13550.0f,5400.f };
				mDir = 1;
				Boss_cross_change = 1;
			}
			else if (Boss_cross_change == 1)
			{
				mState = eBossState::Right;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,5400.f };
				mDir = 1;
				Boss_cross_change = 2;
			}
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

		if ((pos.x >= 14350.f) && (pos.x < 15510.f))
		{
			pos.x += mSpeed * static_cast<float>(Time::DeltaTime());
			pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());
		}
		else if (pos.x > 15150.f)
		{
			if (Boss_cross_change == 0)
			{
				mState = eBossState::Left_Cross;
				mAnimator->Play(L"L_Boss_Third", false);
				pos = Vector2{ 15150.f,5400.f };
				mDir = -1;
				Boss_cross_change = 1;
			}
			else if (Boss_cross_change == 1)
			{
				mState = eBossState::Left;
				mAnimator->Play(L"L_Boss_Third", false);
				pos = Vector2{ 15150.f,5400.f };
				mDir = -1;
				Boss_cross_change = 2;
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
				pos = Vector2{ 13550.0f,5400.f };
				mDir = 1;
				Boss_cross_change = 0;
			}
			else if (Grap_pattern == 1)
			{
				mState = eBossState::Grap_R;
				mAnimator->Play(L"R_Boss_Third", true);
				pos = Vector2{ 13550.0f,4500.f };
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
				pos = Vector2{ 15150.f,5400.f };
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
			Boss_Bomb->Play(true);

			Scene* curScene = SceneManager::GetActiveScene();
			Boss_act1_boomb* Boss2_boomb = new Boss_act1_boomb(this);
			Boss2_boomb->SetName(L"Boss2_boomb");
			Boss2_boomb->GetComponent<Transform>()->SetPos(pos);
			curScene->AddGameobeject(Boss2_boomb, jk_LayerType::Effect);
			Boomb_point = 1;
		}
		else if (Boomb_point == 1)
		{
			time += static_cast<float>(Time::DeltaTime());
			if (time >= 1)
			{
				mRigidbody = AddComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Boomb_point = 2;
			}
		}

		if ((Boomb_point == 2) && (pos.y > 6000))
		{
			Ending_point = 1;
			Boomb_point = 3;
		}
	}
	void Third_Boss::ending()
	{


	}
}