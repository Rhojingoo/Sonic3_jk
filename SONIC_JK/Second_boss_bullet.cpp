#include "Second_boss_bullet.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_Input.h"
#include "jk_Time.h"

namespace jk
{
	Second_boss_bullet::Second_boss_bullet()
		: mDir(1)
		, mSpeed(150.f)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{
		mImage = Resources::Load<Image>(L"Second_boss_R", L"..\\Resources\\ActBG_6\\BOSS\\Second_boss_R.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"boss2_bullet", mImage, Vector2{ 232,435 }, Vector2{ 48,16 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"boss2_bullet", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(96.0f, 32.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (-0.11f) * size.y });
	}
	Second_boss_bullet::~Second_boss_bullet()
	{
	}


	void Second_boss_bullet::Initialize()
	{
		Gameobject::Initialize();
	}


	void Second_boss_bullet::Update()
	{		
		
		if (mDir == 1)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += mSpeed * static_cast<float>(Time::DeltaTime());
			tr->SetPos(pos);
			
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x -= mSpeed * static_cast<float>(Time::DeltaTime());
			tr->SetPos(pos);			
		}

		Gameobject::Update();
	}


	void Second_boss_bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void Second_boss_bullet::Release()
	{
		Gameobject::Release();
	}


	void Second_boss_bullet::OnCollisionEnter(Collider* other)
	{
	}


	void Second_boss_bullet::OnCollisionStay(Collider* other)
	{
	}


	void Second_boss_bullet::OnCollisionExit(Collider* other)
	{
	}
}