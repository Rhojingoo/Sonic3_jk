#include "jk_minibos_show.h"
#include "jk_fire_show.h"
#include "jk_midlle_boss_shoot.h"
#include "jk_Lttle_miniboss.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"

#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Object.h"

namespace jk
{
	minibos_show::minibos_show()
		: mCenterpos(30792.f, 2407.f)
		, mPos(0.f, 0.f)
		, fDist(0.f)
		, mMonspeed(20.f)
		, mMonmaxdistance(100.f)
		, time(0.f)
		, mDir(1)
		, mState()
		, mShoot(0)
		, mMap_check(0)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mAct1_music(nullptr)
		, mMiniboss1(nullptr)
		, mFire_show(nullptr)
		, mAct2_music(nullptr)

	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"middle_bos_show_idle", mImage, Vector2{ 388.f,116.f }, Vector2{ 96.f,78.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"middle_bos_cover_open", mImage, Vector2{ 4.f,25.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"middle_bos_cover_close", mImage, Vector2{ 4.f,115.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->Play(L"middle_bos_show_idle", true);

		mAct1_music = Resources::Load<Sound>(L"Act1_bg", L"..\\Resources\\Sound\\Act1_bg.wav");
		mMiniboss1 = Resources::Load<Sound>(L"Miniboss1", L"..\\Resources\\Sound\\Miniboss1.wav");
		mFire_show = Resources::Load<Sound>(L"Fire_show", L"..\\Resources\\Sound\\Fire_show.wav");
		mAct2_music = Resources::Load<Sound>(L"Act2_bg", L"..\\Resources\\Sound\\Act2_bg.wav");
	}
	minibos_show::~minibos_show()
	{
	}
	void minibos_show::Initialize()
	{
		Gameobject::Initialize();
	}


	void minibos_show::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		switch (mState)
		{
		case jk::minibos_show::eState::Move:
			move();
			break;

		case jk::minibos_show::eState::Attack:
			attack();
			break;

		case jk::minibos_show::eState::Death:
			death();
			break;

		default:
			break;
		}

		if (mShoot == 3)
		{
			time += static_cast<float>(Time::DeltaTime());
			if (time >= 5)
			{
				mFire_show->Stop(true);
				mAct2_music->Play(true);
				SceneManager::LoadScene(jk_SceneType::GamePlay2);
				mMap_check = 1;
			}
		}
		Gameobject::Update();
	}

	void minibos_show::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void minibos_show::Release()
	{
		Gameobject::Release();
	}


	void minibos_show::OnCollisionEnter(Collider* other)
	{
	}

	void minibos_show::OnCollisionStay(Collider* other)
	{
	}

	void minibos_show::OnCollisionExit(Collider* other)
	{
	}

	void minibos_show::move()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
		mPos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -300.0f)
		{
			mState = eState::Attack;
			mAnimator->Play(L"middle_bos_cover_open", false);
		}
		tr->SetPos(mPos);
	}

	void minibos_show::attack()
	{
		Transform* tr = GetComponent<Transform>();
		if (mShoot == 0)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			midlle_boss_shoot* mboss_show_shot[3];
			mboss_show_shot[0] = new midlle_boss_shoot();
			mboss_show_shot[0]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 50.f, mPos.y - 50 });
			curScene->AddGameobeject(mboss_show_shot[0], jk_LayerType::Bullet);

			mboss_show_shot[1] = new midlle_boss_shoot();
			mboss_show_shot[1]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 100.f, mPos.y - 50 });
			curScene->AddGameobeject(mboss_show_shot[1], jk_LayerType::Bullet);

			mboss_show_shot[2] = new midlle_boss_shoot();
			mboss_show_shot[2]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x + 150.f, mPos.y - 50 });
			curScene->AddGameobeject(mboss_show_shot[2], jk_LayerType::Bullet);

			mShoot = 1;
			float distance = 0;
			distance = abs(mboss_show_shot[0]->GetComponent<Transform>()->GetPos().y - mPos.y);
		}
		if (mShoot == 1)
		{
			time += static_cast<float>(Time::DeltaTime());
			if (time >= 5)
			{
				mShoot = 2;
				mState = eState::Death;
				mAnimator->Play(L"middle_bos_cover_close", false);
			}
		}

		tr->SetPos(mPos);
	}

	void minibos_show::death()
	{
		if (mShoot == 2)
		{
			mMiniboss1->Stop(true);
			mFire_show->Play(true);
			Scene* curScene = SceneManager::GetActiveScene();
			fire_show* fire = new fire_show();
			fire->GetComponent<Transform>()->SetPos(Vector2{ mPos.x - 1000.f, mPos.y + 500 });
			curScene->AddGameobeject(fire, jk_LayerType::UI);
			fire->SetCenterpos((Vector2{ mPos.x - 1000.f, mPos.y + 500 }));
			mShoot = 3;
			time = 0;
		}
	}
}