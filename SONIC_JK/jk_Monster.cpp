#include "jk_Monster.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "SonicState.h"
#include "Rigidbody.h"
#include "jk_Object.h"
#include "jk_Animal.h"
#include "jk_Ground.h"


namespace jk
{
	Monster::Monster()
		: mCenterpos(Vector2(0.0f, 0.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(350.0f)
		, mMonmaxdistance(300.0f)
		, mDir(1)
		, check_map(0)
	{
		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(15224.0f, 2921.0f));
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{

		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(750.0f, 531.0f));		
		mImage = Resources::Load<Image>(L"RINO", L"..\\Resources\\Monster.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RMonster", mImage, Vector2::RmonsterLTC, Vector2::Rmonstersize, Vector2::RmonsterSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LMonster", mImage, Vector2::LmonsterLTC, Vector2::Lmonstersize, Vector2::LmonsterSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RMonster_turn", mImage, Vector2::RmonsterLTC, Vector2::Rmonstersize, Vector2::RmonsterSpace, 9, 1, 9, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"LMonster_turn", mImage, Vector2::LmonsterLTC, Vector2::Lmonstersize, Vector2::LmonsterSpace, 9, 1, 9, Vector2::Zero, 0.05);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(133.0f, 90.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });
		

		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"rino_deth", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"rino_deth2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);

		mAnimator->GetCompleteEvent(L"rino_deth") = std::bind(&Monster::deth, this);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}

	void Monster::Update()
	{
		switch (mState)
		{
		case jk::Monster::eMonsterState::Move:move();
			break;

		case jk::Monster::eMonsterState::Turn:turn();
			break;
	

		default:
			break;
		}

		Transform* Rino_TR = GetComponent<Transform>();
		Rigidbody* Rino_rb = GetComponent<Rigidbody>();
		
		check_map = check->Get_map_check();

		mGroundImage = check->GetGroundImage();
		mGroundImage2 = check->GetGroundImage2();

		if (check_map == 0)
		{
			if (Rino_TR && Rino_rb && mGroundImage)
			{
				Vector2 Rino_ps = Rino_TR->GetPos();
				COLORREF FootColor = mGroundImage->GetPixel(Rino_ps.x, Rino_ps.y + 75);
				if (FootColor == RGB(0, 0, 0))
				{
					COLORREF FootColor = mGroundImage->GetPixel(Rino_ps.x, Rino_ps.y + 75);

					while (FootColor == RGB(0, 0, 0))
					{
						Rino_ps.y -= 1;
						FootColor = mGroundImage->GetPixel(Rino_ps.x, Rino_ps.y + 75);
						Rino_TR->SetPos(Rino_ps);
						Rino_rb->SetGround(true);
					}
				}
				else
				{
					Rino_rb->SetGround(false);
				}
			}

		}
		else if (check_map == 1)
		{
			if (Rino_TR && Rino_rb && mGroundImage2)
			{
				Vector2 Rino_ps = Rino_TR->GetPos();
				COLORREF FootColor = mGroundImage2->GetPixel(Rino_ps.x, Rino_ps.y + 75);
				if (FootColor == RGB(0, 0, 0))
				{
					COLORREF FootColor = mGroundImage2->GetPixel(Rino_ps.x, Rino_ps.y + 75);

					while (FootColor == RGB(0, 0, 0))
					{
						Rino_ps.y -= 1;
						FootColor = mGroundImage2->GetPixel(Rino_ps.x, Rino_ps.y + 75);
						Rino_TR->SetPos(Rino_ps);
						Rino_rb->SetGround(true);
					}
				}
				else
				{
					Rino_rb->SetGround(false);
				}

			}
		}



		Gameobject::Update();
	}	

	void Monster::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Monster::Release()
	{
		Gameobject::Release();
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();
		
			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
       			mAnimator->Play(L"rino_deth", false);					
			}
		}
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}


	void Monster::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//현재의 위치좌표 정보얻을 필요있음.(20,20  67,51) 750.0f, 320.0f
		mCurpos = pos;

		////배회거리 기준량을 넘어섰는지 확인		
		float fDist = abs(mCenterpos.x - pos.x) - mMonmaxdistance;
		if (fDist > 0.0f)
		{
			//방향변경
			mDir *= -1;
			pos.x += fDist * mDir;
			mState = eMonsterState::Turn;			
			if (mDir == 1)
				mAnimator->Play(L"RMonster_turn", false);
			else
				mAnimator->Play(L"LMonster_turn", false);
		}
		else////진행방향으로 시간당 mMonspeed 만큼이동
		{
			pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir;
		}
		if (mState == eMonsterState::Deth)
		{
			mState = eMonsterState::Deth;
		}

		tr->SetPos(pos);

	}

	void Monster::turn()
	{	
		//mState = eMonsterState::Move;
		mAnimator->GetCompleteEvent(L"LMonster_turn");
		mAnimator->GetCompleteEvent(L"RMonster_turn");
		//if (mAnimator->GetCompleteEvent(L"LMonster_turn"))/*||mAnimator->GetCompleteEvent(L"RMonster_turn")*/
		//{
		//	int a = 0;
		//}
		//if (mAnimator->GetCompleteEvent(L"RMonster_turn"))/*||mAnimator->GetCompleteEvent(L"RMonster_turn")*/
		//{
		//	int a = 0;
		//}
		mState = eMonsterState::Move;

		if (mState == eMonsterState::Deth)
		{
			mState = eMonsterState::Deth;
		}
	}

	void Monster::deth()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(mOwner);

		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);

		jk::object::Destory(this);

		//Monster::release_animal();
	}
	
	void Monster::release_animal()
	{ 
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(this);

		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);
	}

}