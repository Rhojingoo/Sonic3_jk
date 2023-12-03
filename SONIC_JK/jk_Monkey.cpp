#include "jk_Monkey.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Animator.h"

#include "jk_Object.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Ground.h"
#include "jk_Monket_Bullet.h"
#include "jk_Animal.h"


namespace jk
{
	Monkey::Monkey(Gameobject* owner)
		: mState()
		, mCenterpos(Vector2(12280.0f, 3111.0f))
		, pos(0.f,0.f)
		, mSonic(0.f,0.f)
		, mMonspeed(50.0f)
		, mMonmaxdistance(70.0f)
		, fDist(0.f)
		, mDir(1)
		, death_point(0)
		, animal_point(0)
		, sonicpattern(-1)
		, sonicState()
		, tailsState()
		, mOwner(owner)
		, check(nullptr)
		, Death(nullptr)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		
	{


	}
	Monkey::~Monkey()
	{
	}
	void Monkey::Initialize()
	{
		Death = Resources::Load<Sound>(L"Monster_Death", L"..\\Resources\\Sound\\Sonic\\Monster_Death.wav");
	

		mImage = Resources::Load<Image>(L"MONKEY", L"..\\Resources\\Monster2.bmp");
		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RMonkey", mImage, Vector2{ 20.f,150.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LMonkey", mImage, Vector2{ 20.f,18.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RMonkey_throw", mImage, Vector2{ 20.f,213.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"LMonkey_throw", mImage, Vector2{ 20.f,81.f }, Vector2{ 86.f,58.f }, Vector2{ 5.f,0.f }, 6, 1, 6, Vector2::Zero, 0.05);
		
		mAnimator->CreateAnimation(L"death", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"deth2", mImage1   , Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		
		mAnimator->GetCompleteEvent(L"LMonkey_throw") = std::bind(&Monkey::throw_CompleteEvent, this);
		mAnimator->GetCompleteEvent(L"death") = std::bind(&Monkey::release_animal, this);
		
		mAnimator->Play(L"LMonkey", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(153.0f, 130.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });


		Gameobject::Initialize();
	}

	void Monkey::Update()
	{
		mGroundImage = check->GetGroundImage();
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
		
		if (death_point == 1)
		{
			mState = eMonkey::Death;
			mAnimator->Play(L"death", false);
		}
		

 		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		if (mSonic.x <= pos.x)
		{
			sonicpattern = -1;
		}
		else if (mSonic.x > pos.x)
		{
			sonicpattern = 1;
		}

 		switch (mState)
 		{
		case jk::Monkey::eMonkey::L_Move_UP:Lmove_up();
			break;

		case jk::Monkey::eMonkey::L_Move_DOWN:Lmove_down();
			break;

		case jk::Monkey::eMonkey::R_Move_UP:Rmove_up();
			break;

		case jk::Monkey::eMonkey::R_Move_DOWN:Rmove_down();
			break;

		case jk::Monkey::eMonkey::L_Throw:Lthrows();
			break;

		case jk::Monkey::eMonkey::R_Throw:Rthrows();
			break;

		case jk::Monkey::eMonkey::Turn:turn();
			break;

		case jk::Monkey::eMonkey::Death:death();
		break;	

		default:
			break;
		}
		Gameobject::Update();
	}

	void Monkey::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Monkey::Release()
	{
		Gameobject::Release();
	}

	void Monkey::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"death", false);		
				sonicpattern;
				death_point = 1;				
				Death->Play(false);
			}	
		}

		else if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			tailsState = tails->GetTails_state();

			if (tailsState == Tails::eTailsState::Dash || tailsState == Tails::eTailsState::Jump || tailsState == Tails::eTailsState::Spin|| tailsState == Tails::eTailsState::Movejump)
			{				
				Death->Play(false);
				mAnimator->Play(L"death", false);				
				death_point = 1;
			}
		}


	}
	void Monkey::OnCollisionStay(Collider* other)
	{
	}
	void Monkey::OnCollisionExit(Collider* other)
	{
	}

	
	void Monkey::Lmove_up()
	{
		Transform* tr = GetComponent<Transform>();
	
		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());


		if (fDist >= 30.0f)
		{
			mState = eMonkey::L_Throw;
			mAnimator->Play(L"LMonkey_throw", false);
			mDir *= -1;
		}
		//if (sonicpattern == 1)
		//{
		//	pos.x = pos.x + 170;
		//	mAnimator->Play(L"RMonkey", true);
		//	mState = eMonkey::R_Move_UP;
		//}

		tr->SetPos(pos);
	}

	void Monkey::Lmove_down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -100.0f)
		{
			mState = eMonkey::L_Throw;
				mAnimator->Play(L"LMonkey_throw", false);
			mDir *= -1;
		}
		//if (sonicpattern == 1)
		//{
		//	pos.x = pos.x + 170;
		//	mAnimator->Play(L"RMonkey", true);
		//	mState = eMonkey::R_Move_DOWN;
		//}

		tr->SetPos(pos);
	}

	void Monkey::Rmove_up()
	{
		//Transform* tr = GetComponent<Transform>();

		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		//pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());


		//if (fDist >= 30.0f)
		//{
		//	mState = eMonkey::R_Throw;
		//		mAnimator->Play(L"RMonkey_throw", false);
		//	mDir *= -1;
		//}

		//if (mState == eMonkey::Deth)
		//{
		//	mAnimator->Play(L"deth", false);
		//	mAnimator->GetCompleteEvent(L"deth") = std::bind(&Monkey::deth, this);
		//}

		//if (sonicpattern == -1)
		//{
		//	pos.x = pos.x - 170;
		//	mAnimator->Play(L"RMonkey", true);
		//	mState = eMonkey::L_Move_UP;
		//}

		//tr->SetPos(pos);
	}

	void Monkey::Rmove_down()
	{
		//Transform* tr = GetComponent<Transform>();

		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		//pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		//if (fDist <= -100.0f)
		//{
		//	mState = eMonkey::R_Throw;
		//	mAnimator->Play(L"RMonkey_throw", false);
		//	mDir *= -1;
		//}
		//if (mState == eMonkey::Deth)
		//{
		//	mAnimator->Play(L"deth", false);
		//	mAnimator->GetCompleteEvent(L"deth") = std::bind(&Monkey::deth, this);
		//}
		//if (sonicpattern == -1)
		//{
		//	pos.x = pos.x - 170;
		//	mAnimator->Play(L"LMonkey", true);
		//	mState = eMonkey::L_Move_UP;
		//}

		//tr->SetPos(pos);
	}


	void Monkey::Lthrows()
	{
		//mAnimator->GetCompleteEvent(L"LMonkey_throw") = std::bind(&Monkey::throw_CompleteEvent, this);
	}

	void Monkey::Rthrows()
	{
		//mAnimator->GetCompleteEvent(L"RMonkey_throw") = std::bind(&Monkey::throw_CompleteEvent, this);

		//if (mState == eMonkey::Deth)
		//{
		//	mAnimator->Play(L"deth", false);
		//	mAnimator->GetCompleteEvent(L"deth") = std::bind(&Monkey::deth, this);
		//}
	}

	void Monkey::turn()
	{
	/*	if (sonicpattern == -1)
		{*/
			if (mDir == -1)
			{
				mState = eMonkey::L_Move_UP;
				mAnimator->Play(L"LMonkey", true);
			}
			if (mDir == 1)
			{
				mState = eMonkey::L_Move_DOWN;
				mAnimator->Play(L"LMonkey", true);
			}
		//}
		//if (sonicpattern == 1)
		//{
		//	if (mDir == -1)
		//	{
		//		mState = eMonkey::R_Move_UP;
		//		mAnimator->Play(L"RMonkey", true);
		//	}
		//	if (mDir == 1)
		//	{
		//		mState = eMonkey::R_Move_DOWN;
		//		mAnimator->Play(L"RMonkey", true);
		//	}
		//}

	}



	void Monkey::death()
	{		
		if (animal_point == 0)
		{
			//release_animal();
			//animal_point = 1;
			//jk::object::Destory(this);
			death_point = 2;		
		}

	
	}

	void Monkey::throw_CompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();		
		
		if (sonicpattern == -1)
		{
			Monket_Bullet* bullet = new Monket_Bullet(mOwner);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos()});
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -300.0f, -300.0f });
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
			bullet->SetGroundImage(mGroundImage);
		}
		else if(sonicpattern ==1)
		{
			Monket_Bullet* bullet = new Monket_Bullet(mOwner);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos()});
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ 300.0f, -300.0f });
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
			bullet->SetGroundImage(mGroundImage);
		}
		
		mState = eMonkey::Turn;
	}

	void Monkey::release_animal()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(mOwner);
		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);

		object::Destory(this);
	}
}

         