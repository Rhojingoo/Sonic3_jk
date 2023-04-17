#include "jk_BaseBullet.h"
#include "jk_Transform.h"
#include "jk_Time.h"
#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"

namespace jk
{
	BaseBullet::BaseBullet(Gameobject* owner)
		: mCenterpos(Vector2(750.0f, 151.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(50.0f)
		, mMonmaxdistance(800.0f)
		, mDir(-1)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Rbullet", mImage, Vector2(307, 93), Vector2(36, 37), Vector2(8, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Lbullet", mImage, Vector2(263, 93), Vector2(36, 37), Vector2(8, 0), 1, 1, 1, Vector2::Zero, 0.1f);

		Collider* collider = AddComponent<Collider>();		
		collider->SetSize(Vector2(90.0f, 95.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });
		mOwner = owner;
	}

	BaseBullet::~BaseBullet()
	{
	}
	void BaseBullet::Initialize()
	{

	}
	void BaseBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Sonic = mOwner->GetComponent<Transform>()->GetPos();
		
		if (Sonic.x > pos.x)
		{
			pos.x += 100.0f * static_cast<float>(Time::DeltaTime());
			pos.y += 100.0f * static_cast<float>(Time::DeltaTime());
			mAnimator->Play(L"Rbullet", true);
		}
		if (Sonic.x < pos.x)
		{
			pos.x -= 100.0f * static_cast<float>(Time::DeltaTime());
			pos.y += 100.0f * static_cast<float>(Time::DeltaTime());
			mAnimator->Play(L"Lbullet", true);
		}
		tr->SetPos(pos);	
	
		Gameobject::Update();
	}
	void BaseBullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void BaseBullet::Release()
	{
		Gameobject::Release();
	}
}