#include "WaterSonic.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"



namespace jk
{
	WaterSonic::WaterSonic(Gameobject* owner)
		: mOwner(nullptr)
		, sonic(nullptr)
		, mAnimator(nullptr)
		, mSonic(0.f,0.f)
		, mState(State::Idle)
		, shield_bounce(0)
		, mDir(0)
	{
		sonic = dynamic_cast<Sonic*>(owner);
		Image* mImage = Resources::Load<Image>(L"shield", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Water", mImage, Vector2(372, 343), Vector2(56, 56), Vector2(8, 8), 5, 2, 10, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"Water_collision", mImage, Vector2(24, 287), Vector2(80, 48), Vector2(8, 0), 3, 1, 3, Vector2::Zero, 0.05f);
		mAnimator->GetCompleteEvent(L"Water_collision") = std::bind(&WaterSonic::water_effect,this);
		mAnimator->Play(L"Water", true);
		
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = mSonic;
				
	}
	WaterSonic::~WaterSonic()
	{
	}
	void WaterSonic::Initialize()
	{
		Gameobject::Initialize();
	}
	void WaterSonic::Update()
	{
		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		shield_bounce = sonic->Water_Shield();
	
		switch (mState)
		{
		case jk::WaterSonic::State::Idle:idle();
			break;

		case jk::WaterSonic::State::Collision_Ground:collsion_ground();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void WaterSonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void WaterSonic::Release()
	{
		Gameobject::Release();
	}
	void WaterSonic::OnCollisionEnter(Collider* other)
	{
	}
	void WaterSonic::OnCollisionStay(Collider* other)
	{
	}
	void WaterSonic::OnCollisionExit(Collider* other)
	{
	}
	void WaterSonic::idle()
	{
		if (shield_bounce == 0)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(mSonic);
		}
		if (shield_bounce == 1)
		{
			mState = State::Collision_Ground;
			mAnimator->Play(L"Water_collision", false);
		}
	}
	void WaterSonic::collsion_ground()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();	
		tr->SetPos(Vector2{ mSonic.x - 24,mSonic.y });		
	}
	void WaterSonic::water_effect()
	{
		mState = State::Idle;
		mAnimator->Play(L"Water", true);
	}
}