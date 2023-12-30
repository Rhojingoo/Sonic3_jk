#include "jk_Miniboss.h"
#include "mB_Rdeath.h"
#include "mBoss_Bl_L.h"
#include "mBoss_BL_R.h"
#include "mB_Ldeath.h"
#include "Boss_act1_boomb.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Time.h"
#include "jk_Input.h"

#include "jk_Sonic.h"
#include "jk_Image.h"
#include "jk_Sound.h"


namespace jk
{
	Minibos::Minibos(Gameobject* owner)
		: mOwner(owner)
		, mCenterpos(13545.f, 2880.f)
		, mPos(0.f, 0.f)
		, mMonspeed(100.0f)
		, mMonmaxdistance(100.0f)
		, fDist(0.f)
		, mTime_Check(0.f)
		, mTime(0.f)
		, mDir(-1)
		, mAttack(0)
		, mAttack_check(0)
		, mDeath(0)
		, mMap_check(0)
		, sonicState()
		, mState()
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mMiniboss2(nullptr)
		, mBoss_hit(nullptr)
		, mMinboss_death(nullptr)
		, mAct2_music(nullptr)
	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"R_mBoss", mImage, Vector2{ 4.f,285.f }, Vector2{ 96.f,72.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_mBoss", mImage, Vector2{ 4.f,206.f }, Vector2{ 96.f,72.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"middle_bos_cover_open", mImage, Vector2{ 4.f,25.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_mBoss_idle", mImage, Vector2{ 4.f,285.f }, Vector2{ 96.f,72.f }, Vector2{ 8.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_mBoss_idle", mImage, Vector2{ 4.f,206.f }, Vector2{ 96.f,72.f }, Vector2{ 8.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_mBDeath", mImage, Vector2{ 452.f,418.f }, Vector2{ 80.f,64.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_mBDeath", mImage, Vector2{ 451.f,331.f }, Vector2{ 80.f,64.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"L_mBoss", true);

		mMinboss_death = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
		mMiniboss2 = Resources::Load<Sound>(L"Miniboss2", L"..\\Resources\\Sound\\Miniboss2.wav");
		mBoss_hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		mAct2_music = Resources::Load<Sound>(L"Act2_bg", L"..\\Resources\\Sound\\Act2_bg.wav");


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(245.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.25f) * size.y });
	}
	Minibos::~Minibos()
	{
	}
	void Minibos::Initialize()
	{
		Gameobject::Initialize();
	}

	void Minibos::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		switch (mState)
		{
		case jk::Minibos::eState::Down:
			down();
			break;

		case jk::Minibos::eState::Up:
			up();
			break;

		case jk::Minibos::eState::Right:
			right();
			break;

		case jk::Minibos::eState::Left:
			left();
			break;

		case jk::Minibos::eState::Waiting:
			waiting();
			break;

		case jk::Minibos::eState::Atack:
			atack();
			break;

		case jk::Minibos::eState::Hurt:
			hurt();
			break;

		case jk::Minibos::eState::Death:
			death();
			break;

		default:
			break;
		}

		if (mDeath == 1)
		{
			mTime += static_cast<float>(Time::DeltaTime());
			if (mTime >= 5)
			{
				mAct2_music->Play(true);
				SceneManager::LoadScene(jk_SceneType::GamePlay3);
				mMap_check = 2;
				object::Destory(this);
			}
		}

		Gameobject::Update();
	}

	void Minibos::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Minibos::Release()
	{
		Gameobject::Release();
	}

	void Minibos::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();
			mBoss_hit->Play(false);

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAttack_check += 1;

				Transform* tr = GetComponent<Transform>();
				if ((mAttack_check >= 6) && (mDir == -1))//哭率
				{


					mAnimator->Play(L"L_mBoss_idle", true);
					mState = eState::Death;
					mAttack_check = 0;
					mTime = 0;

					Collider* collider = GetComponent<Collider>();
					collider->SetSize(Vector2(.0f, 0.0f));
				}
				if ((mAttack_check >= 6) && (mDir == 1))//坷弗率
				{

					mAnimator->Play(L"R_mBoss_idle", true);
					mState = eState::Death;
					mAttack_check = 0;
					mTime = 0;
					Collider* collider = GetComponent<Collider>();
					collider->SetSize(Vector2(.0f, 0.0f));
				}
				tr->SetPos(mPos);
			}
		}
	}

	void Minibos::OnCollisionStay(Collider* other)
	{
	}

	void Minibos::OnCollisionExit(Collider* other)
	{
	}

	void Minibos::down()
	{
		Transform* tr = GetComponent<Transform>();
		mTime_Check = 0;
		fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
		mPos.y += mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist <= -485.0f)
		{
			mState = eState::Atack;
		}
		tr->SetPos(mPos);
	}

	void Minibos::up()
	{
		Transform* tr = GetComponent<Transform>();
		mTime_Check = 0;
		fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
		mPos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist >= -35.0f)
		{
			if (mDir == -1)//哭率
			{
				mState = eState::Left;
				int a = 0;
			}
			if (mDir == 1)//坷弗率
			{
				int a = 0;
				mState = eState::Right;
			}
		}
		tr->SetPos(mPos);
	}

	void Minibos::right()
	{
		Transform* tr = GetComponent<Transform>();
		mTime_Check = 0;
		fDist = mCenterpos.x - mPos.x - mMonmaxdistance;
		mPos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -335.0f)
		{
			mState = eState::Down;
			mAnimator->Play(L"L_mBoss", true);
			mDir = -1;
		}
		tr->SetPos(mPos);
	}

	void Minibos::left()
	{
		Transform* tr = GetComponent<Transform>();
		mTime_Check = 0;
		fDist = mCenterpos.x - mPos.x - mMonmaxdistance;
		mPos.x -= mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist >= 590.0f)
		{
			mState = eState::Down;
			mAnimator->Play(L"R_mBoss", true);
			mDir = 1;
		}
		tr->SetPos(mPos);
	}

	void Minibos::waiting()
	{
		mTime_Check += static_cast<float>(Time::DeltaTime());
		if (mTime_Check > 3)//促款
		{
			if (mAttack == 0)
			{
				//mAnimator->Play(L"middle_bos_cover_open", false);
				mState = eState::Atack;
				mTime_Check = 0;
				mAttack = 1;
			}
			if (mAttack == 1)
			{
				mState = eState::Up;
				mTime_Check = 0;
				mAttack = 0;
			}
		}
	}

	void Minibos::atack()
	{
		mTime_Check += static_cast<float>(Time::DeltaTime());
		Transform* tr = GetComponent<Transform>();

		if (mDir == -1)//哭率
		{
			Scene* curScene = SceneManager::GetActiveScene();
			mBoss_Bl_L* bullet = new mBoss_Bl_L(this);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x - 400, tr->GetPos().y + 25 });
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
			if (mTime_Check >= 3)
			{
				object::Destory(bullet);
				mState = eState::Waiting;
				mTime_Check = 0;
			}
		}
		if (mDir == 1)//坷弗率
		{
			Scene* curScene = SceneManager::GetActiveScene();
			mBoss_BL_R* bullet = new mBoss_BL_R(this);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 245, tr->GetPos().y + 25 });
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);

			if (mTime_Check >= 3)
			{
				object::Destory(bullet);
				mState = eState::Waiting;
				mTime_Check = 0;
			}
		}
		tr->SetPos(mPos);
	}

	void Minibos::hurt()
	{
	}

	void Minibos::death()
	{

		if (mAttack_check == 0)
		{
			mMiniboss2->Stop(true);
			mMinboss_death->Play(false);

			Transform* tr = GetComponent<Transform>();
			Boss_act1_boomb* boss_boomb = new Boss_act1_boomb(this);
			Scene* curScene = SceneManager::GetActiveScene();
			boss_boomb->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x , tr->GetPos().y });
			curScene->AddGameobeject(boss_boomb, jk_LayerType::MiniBoss);
			mAttack_check = 1;
			mTime = 0;
		}
		mTime += static_cast<float>(Time::DeltaTime());
		if ((mTime >= 2) && (mAttack_check >= 1))
		{
			mDeath = 1;
			mTime_Check = 0;
		}
	}


}