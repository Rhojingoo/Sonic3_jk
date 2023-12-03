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


namespace jk
{
	Electsonic::Electsonic(Gameobject* owner)
		: mOwner(owner)
		, sonic(nullptr)
		, elect1(nullptr)
		, elect2(nullptr)
		, mAnimator(nullptr)
		, mState(State::Idle)

		, mSonic(0.0f,0.0f)
		, effect_check(0)
		, effect_call(0)
		, time(0.f)

	{		 
		sonic = dynamic_cast<Sonic*>(owner);
		Image* mImage = Resources::Load<Image>(L"shield", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Elect", mImage, Vector2(372, 472), Vector2(56, 56), Vector2(8, 8), 3, 4, 12, Vector2::Zero, 0.05f);
		mAnimator->Play(L"Elect", true);


		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = mSonic;
		
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
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		effect_check =sonic->Elect_Shield();

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
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(mSonic);

		if (effect_check == 1)
		{          
  			if (effect_check != 1)
				return;
			if (effect_call == 0)
			{
				effect();
				effect_call = 1;
				time = 0;
			}
		}

		if (effect_call == 1)
		{		
			object::Destory(elect1);
			object::Destory(elect2);
			effect_call = 0;			
		}

	}
	void Electsonic::elect_effect()
	{	
		mState = State::Idle;
	}

	void Electsonic::effect()
	{
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Scene* curScene = SceneManager::GetActiveScene();
		elect1 = new Elec_effect(this);
		elect1->SetName(L"elect_effect1");
		curScene->AddGameobeject(elect1, jk_LayerType::Effect);
		elect1->GetComponent<Transform>()->SetPos(Vector2{ pos.x , pos.y });


		elect2 = new Elec_effect(this);
		elect2->SetName(L"mboss");
		curScene->AddGameobeject(elect2, jk_LayerType::Effect);
		elect2->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 45, pos.y });
	}
}