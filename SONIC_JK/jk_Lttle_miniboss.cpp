#include "jk_Lttle_miniboss.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Input.h"

namespace jk
{
	Lttle_miniboss::Lttle_miniboss( )
		: mMonspeed(10.0f)
		, pos(0.f,0.f)
		, mCenterpos(0.f, 0.f)
		, mMonmaxdistance(500.0f)
		, fDist(0.f)
		, mDir(1)
		, mState()
		, mAnimator(nullptr)
		, mImage(nullptr)
	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"little_bos_show_idle", mImage, Vector2{ 320.f,457.f }, Vector2{ 24.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->Play(L"little_bos_show_idle", true);
	}
	Lttle_miniboss::~Lttle_miniboss()
	{

	}
	void Lttle_miniboss::Initialize()
	{

		Gameobject::Initialize();
	}


	void Lttle_miniboss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::Lttle_miniboss::eState::Move:move();
			break;

		case jk::Lttle_miniboss::eState::Death:death();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Lttle_miniboss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Lttle_miniboss::Release()
	{
		Gameobject::Release();
	}


	void Lttle_miniboss::OnCollisionEnter(Collider* other)
	{
	}
	void Lttle_miniboss::OnCollisionStay(Collider* other)
	{
	}
	void Lttle_miniboss::OnCollisionExit(Collider* other)
	{

	}

	void Lttle_miniboss::move()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.x - pos.x - mMonmaxdistance;
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime())* mDir;

		if (fDist <= -1000.0f)
		{
			mState = eState::Death;	
		}
		tr->SetPos(pos);

	}

	void Lttle_miniboss::death()
	{

	}
}