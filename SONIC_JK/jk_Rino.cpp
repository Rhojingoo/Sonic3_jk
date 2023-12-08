#include "jk_Rino.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Animator.h"

#include "jk_Object.h"
#include "jk_Ground.h"
#include "jk_Animal.h"



namespace jk
{
	Rino::Rino()
		: mCenterpos(Vector2(0.0f, 0.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(350.0f)
		, mMonmaxdistance(300.0f)
		, mDir(1)
		, check(nullptr)
		, check_map(0)
		, Death_Point(0)
		, sonicState()
		, tailsState()
		, mState(eMonsterState::Move)
		, Death(nullptr)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mGroundImage(nullptr)
		, mGroundImage2(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)

	{

	}

	Rino::~Rino()
	{
	}

	void Rino::Initialize()
	{
		Death =  Resources::Load<Sound>(L"Monster_Death", L"..\\Resources\\Sound\\Sonic\\Monster_Death.wav");
			
		mImage = Resources::Load<Image>(L"RINO", L"..\\Resources\\Monster.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RMonster", mImage, Vector2::RmonsterLTC, Vector2::Rmonstersize, Vector2::RmonsterSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LMonster", mImage, Vector2::LmonsterLTC, Vector2::Lmonstersize, Vector2::LmonsterSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RMonster_turn", mImage, Vector2::RmonsterLTC, Vector2::Rmonstersize, Vector2::RmonsterSpace, 9, 1, 9, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"LMonster_turn", mImage, Vector2::LmonsterLTC, Vector2::Lmonstersize, Vector2::LmonsterSpace, 9, 1, 9, Vector2::Zero, 0.05f);
				

		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"rino_death", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"rino_deth2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->GetCompleteEvent(L"rino_death") = std::bind(&Rino::release_animal, this);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(133.0f, 90.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Monster::Initialize();
		//Gameobject::Initialize();
	}

	void Rino::Update()
	{		
		if (Death_Point == 1)
		{
			mState = eMonsterState::Death;
			mAnimator->Play(L"rino_death", false);
		}


		switch (mState)
		{
		case jk::Rino::eMonsterState::Move:move();
			break;

		case jk::Rino::eMonsterState::Turn:turn();
			break;
	
		case jk::Rino::eMonsterState::Death:death();
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
				COLORREF FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));
				if (FootColor == RGB(0, 0, 0))
				{
					FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));

					while (FootColor == RGB(0, 0, 0))
					{
						Rino_ps.y -= 1;
						FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));
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
				COLORREF FootColor = static_cast<int>(mGroundImage2->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));
				if (FootColor == RGB(0, 0, 0))
				{
					FootColor = static_cast<int>(mGroundImage2->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));

					while (FootColor == RGB(0, 0, 0))
					{
						Rino_ps.y -= 1;
						FootColor = static_cast<int>(mGroundImage2->GetPixel(static_cast<int>(Rino_ps.x), static_cast<int>(Rino_ps.y) + 75));
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

		Monster::Update();
		//Gameobject::Update();
	}	

	void Rino::Render(HDC hdc)
	{
		//Gameobject::Render(hdc);
		Monster::Render(hdc);
	}

	void Rino::Release()
	{
		Monster::Release();
		//Gameobject::Release();
	}

	void Rino::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();
		
			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{				
				Death->Play(false);
       			mAnimator->Play(L"rino_death", false);		
				Death_Point = 1;
			}
		}
		else if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			tailsState = tails->GetTails_state();

			if (tailsState == Tails::eTailsState::Dash || tailsState == Tails::eTailsState::Jump || tailsState == Tails::eTailsState::Spin || tailsState == Tails::eTailsState::Movejump)
			{				
				Death->Play(false);
				mAnimator->Play(L"rino_death", false);
				Death_Point = 1;
			}
		}
	}

	void Rino::OnCollisionStay(Collider* other)
	{
	}

	void Rino::OnCollisionExit(Collider* other)
	{
	}


	void Rino::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mCurpos = pos;

	
		float fDist = abs(mCenterpos.x - pos.x) - mMonmaxdistance;
		if (fDist > 0.0f)
		{
			
			mDir *= -1;
			pos.x += fDist * mDir;
			mState = eMonsterState::Turn;			
			if (mDir == 1)
				mAnimator->Play(L"RMonster_turn", false);
			else
				mAnimator->Play(L"LMonster_turn", false);
		}
		else
		{
			pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir;
		}

		tr->SetPos(pos);
	}

	void Rino::turn()
	{	
		mAnimator->GetCompleteEvent(L"LMonster_turn");
		mAnimator->GetCompleteEvent(L"RMonster_turn");

		mState = eMonsterState::Move;
	}

	void Rino::death()
	{
		Death_Point = 2;
	}
	
	void Rino::release_animal()
	{ 
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(this);
		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);

		jk::object::Destory(this);
	}

}