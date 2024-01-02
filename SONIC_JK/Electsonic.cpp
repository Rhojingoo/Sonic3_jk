#include "Electsonic.h"
#include "Elec_effect.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Object.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	Electsonic::Electsonic(Gameobject* owner)
		: mOwner(owner)
		, mSonic(nullptr)
		, mElect1(nullptr)
		, mElect2(nullptr)
		, mAnimator(nullptr)
		, mState(State::Idle)

		, mSonic_pos(0.0f,0.0f)
		, mEffect_check(0)
		, mEffect_call(0)
		, mTime(0.f)

	{		 
		mSonic = dynamic_cast<Sonic*>(owner);
		Image* mImage = Resources::Load<Image>(L"shield", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Elect", mImage, Vector2(372, 472), Vector2(56, 56), Vector2(8, 8), 3, 4, 12, Vector2::Zero, 0.05f);
		mAnimator->Play(L"Elect", true);


		mSonic_pos = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = mSonic_pos;
		
	}
	Electsonic::~Electsonic()
	{
	}
	void Electsonic::Initialize()
	{
		Gameobject::Initialize();
	}
	void Electsonic::Update()
	{
		mSonic_pos = mOwner->GetComponent<Transform>()->GetPos();
		mEffect_check =mSonic->Elect_Shield();

		switch (mState)
		{
		case jk::Electsonic::State::Idle:idle();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Electsonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Electsonic::Release()
	{
		Gameobject::Release();
	}
	void Electsonic::idle()
	{
		mSonic_pos = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(mSonic_pos);

		if (mEffect_check == 1)
		{          
  			if (mEffect_check != 1)
				return;
			if (mEffect_call == 0)
			{
				effect();
				mEffect_call = 1;
				mTime = 0;
			}
		}

		if (mEffect_call == 1)
		{		
			object::Destory(mElect1);
			object::Destory(mElect2);
			mEffect_call = 0;			
		}

	}
	void Electsonic::elect_effect()
	{	
		mState = State::Idle;
	}

	void Electsonic::effect()
	{
		mSonic_pos = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Scene* curScene = SceneManager::GetActiveScene();
		mElect1 = new Elec_effect(this);
		mElect1->SetName(L"elect_effect1");
		curScene->AddGameobeject(mElect1, jk_LayerType::Effect);
		mElect1->GetComponent<Transform>()->SetPos(Vector2{ pos.x , pos.y });


		mElect2 = new Elec_effect(this);
		mElect2->SetName(L"mboss");
		curScene->AddGameobeject(mElect2, jk_LayerType::Effect);
		mElect2->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 45, pos.y });
	}
}