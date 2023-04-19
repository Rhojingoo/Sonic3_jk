#include "jk_minibos_show.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_fire_show.h"
#include "jk_midlle_boss_shoot.h"
#include "jk_Object.h"
#include "jk_Lttle_miniboss.h"

namespace jk
{
	minibos_show::minibos_show()
		:mCenterpos(30792.f, 2407.f)
		, mMonspeed(20.0f)
		, mMonmaxdistance(100.0f)
		, mDir(1)
		, shoot(0)
		, time(0.f)
		, map_check(0)
	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"middle_bos_show_idle", mImage, Vector2{ 388.f,116.f }, Vector2{ 96.f,78.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"middle_bos_cover_open", mImage, Vector2{ 4.f,25.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"middle_bos_cover_close", mImage, Vector2{ 4.f,115.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);


		mAnimator->Play(L"middle_bos_show_idle", true);		
	}
	minibos_show::~minibos_show()
	{
	}
	void minibos_show::Initialize()
	{

		//mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		//mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimation(L"middle_bos_show_idle", mImage, Vector2{ 388.f,117.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimation(L"middle_bos_cover_open", mImage, Vector2{ 4.f,25.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 8, 1, 8, Vector2::Zero, 0.1f);
		//mAnimator->CreateAnimation(L"middle_bos_cover_close", mImage, Vector2{ 4.f,115.f }, Vector2{ 96.f,79.f }, Vector2{ 8.f,0.f }, 8, 1, 8, Vector2::Zero, 0.1f);

		//mAnimator->Play(L"middle_bos_show_idle", true);
		//mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		//mAnimator->GetCompleteEvent(L"middle_bos_cover_open") = std::bind(&minibos_show::attack, this);


		Gameobject::Initialize();
	}


	void minibos_show::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::minibos_show::eState::Move:move();
			break;

		case jk::minibos_show::eState::Attack:attack();
			break;

		case jk::minibos_show::eState::Death:death();
			break;

		default:
			break;
		}

		if (shoot == 3)
		{
			time += Time::DeltaTime();
			if (time >= 5)
			{		
				SceneManager::LoadScene(jk_SceneType::GamePlay2);
				map_check = 1;
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

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist <= -300.0f)
		{
			mState = eState::Attack;
			mAnimator->Play(L"middle_bos_cover_open", false);	
		}
		tr->SetPos(pos);

	}

	void minibos_show::attack()
	{
		Transform* tr = GetComponent<Transform>();
		if(shoot==0)
		{
			Scene* curScene[3];
			curScene[0] = new Scene();
			curScene[0] = SceneManager::GetActiveScene();
			midlle_boss_shoot* mboss_show_shot[3];
			mboss_show_shot [0] = new midlle_boss_shoot();
			mboss_show_shot[0]->GetComponent<Transform>()->SetPos(Vector2{pos.x + 50.f, pos.y-50});
			curScene[0]->AddGameobeject(mboss_show_shot[0], jk_LayerType::Bullet);

			curScene[1] = new Scene();
			curScene[1] = SceneManager::GetActiveScene();
			mboss_show_shot[1] = new midlle_boss_shoot();
			mboss_show_shot[1]->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 100.f, pos.y-50 });
			curScene[1]->AddGameobeject(mboss_show_shot[1], jk_LayerType::Bullet);


			curScene[2] = new Scene();
			curScene[2] = SceneManager::GetActiveScene();
			mboss_show_shot[2] = new midlle_boss_shoot();
			mboss_show_shot[2]->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 150.f, pos.y-50 });
			curScene[2]->AddGameobeject(mboss_show_shot[2], jk_LayerType::Bullet);

			shoot = 1;
			float distance = 0;
			distance = abs(mboss_show_shot[0]->GetComponent<Transform>()->GetPos().y - pos.y);			
		}
		if (shoot == 1)
		{
			time += Time::DeltaTime();
			if (time >= 5)
			{
				shoot = 2;
				mState = eState::Death;
				mAnimator->Play(L"middle_bos_cover_close", false);
			}
		}

		tr->SetPos(pos);
	}

	void minibos_show::death()
	{
		if (shoot == 2)
		{
			Scene* curScene = new Scene();
			curScene = SceneManager::GetActiveScene();
			fire_show* fire = new fire_show();
			fire->GetComponent<Transform>()->SetPos(Vector2{ pos.x - 1000.f, pos.y + 500 });
			curScene->AddGameobeject(fire, jk_LayerType::UI);
			fire->SetCenterpos((Vector2{ pos.x - 1000.f, pos.y + 500 }));			
			shoot = 3;
			time = 0;
		}
	}
}