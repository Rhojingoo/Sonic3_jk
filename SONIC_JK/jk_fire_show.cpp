#include "jk_fire_show.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Collider.h"
#include "jk_Object.h"

#include "jk_Time.h"
#include "jk_Input.h"


namespace jk
{
	fire_show::fire_show()
		: mCenterpos(30792.f, 2407.f)
		, pos(0.f,0.f)
		, mMonspeed(350.0f)
		, mMonmaxdistance(1000000.0f)
		, fDist(0.f)
		, mState()
	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"fire_show_ending", mImage, Vector2{ 24.f,610.f }, Vector2{ 512.f,768.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"fire_show_ending", true);
	}
	fire_show::~fire_show()
	{
	}
	void fire_show::Initialize()
	{
		Gameobject::Initialize();
	}
	void fire_show::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::fire_show::eState::Move:move();
			break;

		case jk::fire_show::eState::Attack:attack();
			break;

		case jk::fire_show::eState::Death:death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
		
	
	void fire_show::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void fire_show::Release()
	{
		Gameobject::Release();
	}
	void fire_show::OnCollisionEnter(Collider* other)
	{
	}
	void fire_show::OnCollisionStay(Collider* other)
	{
	}
	void fire_show::OnCollisionExit(Collider* other)
	{
	}
	void fire_show::move()
	{
		Transform* tr = GetComponent<Transform>();
		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());				
		tr->SetPos(pos);

	}
	void fire_show::attack()
	{
	}
	void fire_show::death()
	{
	}
}