#include "FireSonic.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"


namespace jk
{
	FireSonic::FireSonic(Gameobject* owner)
		: mOwner(owner)
		, sonic(nullptr)
		, mAnimator(nullptr)
		, mSonic(0.0f, 0.0f)
		, effect_check(0)
		, mDir(0)
		, mState(State::Idle)
	{		
		sonic = dynamic_cast<Sonic*>(owner);
		Image* mImage = Resources::Load<Image>(L"shield", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Fire", mImage, Vector2(372, 769), Vector2(56, 56), Vector2(8, 8), 6, 3, 18, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"Fire_effect", mImage, Vector2(24, 175), Vector2(72, 48), Vector2(8,0), 9, 1, 9, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"LFire_effect", mImage, Vector2(24, 225), Vector2(72, 48), Vector2(8, 0), 9, 1, 9, Vector2::Zero, 0.05f);
		mAnimator->GetCompleteEvent(L"Fire_effect") = std::bind(&FireSonic::fire_effect, this);
		mAnimator->GetCompleteEvent(L"LFire_effect") = std::bind(&FireSonic::fire_effect, this);
		mAnimator->Play(L"Fire", true);
	}
	FireSonic::~FireSonic()
	{
	}
	void FireSonic::Initialize()
	{
		Gameobject::Initialize();
	}
	void FireSonic::Update()
	{
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(mSonic);

		mDir = sonic->GetSonicDir();
		effect_check= sonic->Fire_Shield();

		switch (mState)
		{
		case jk::FireSonic::State::Idle:idle();
			break;

		case jk::FireSonic::State::Fire_Attack:fire_attack();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void FireSonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void FireSonic::Release()
	{
		Gameobject::Release();
	}
	void FireSonic::idle()
	{
		if (effect_check == 0)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(mSonic);
		}
		if (effect_check == 1)
		{
			mState = State::Fire_Attack;
			if (mDir == 1)
			{
				mAnimator->Play(L"Fire_effect", false);
			}
			else
			{
				mAnimator->Play(L"LFire_effect", false);
			}
		}

	}
	void FireSonic::fire_attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if (mDir == 1)
		{
			tr->SetPos(Vector2{ mSonic.x - 16,mSonic.y+15 });
		}
		else
		{
			tr->SetPos(Vector2{ mSonic.x,mSonic.y+15 });
		}
	}
	void FireSonic::fire_effect()
	{
		mState = State::Idle;
		mAnimator->Play(L"Fire", true);
	}
}