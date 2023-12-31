#include "jk_Cannon_Bullet.h"
#include "jk_Cannon.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Pixel_Ground.h"
#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_Input.h"
#include "jk_Time.h"

#include "jk_SONIC.h"



namespace jk 
{
	Cannon_Bullet::Cannon_Bullet(Gameobject* owner)
		: mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTr(nullptr)
		, mOwner(owner)
		, mDir(-1)
		, mCheck_Ground(0)

	{
		mImage = Resources::Load<Image>(L"Canon_B", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Canon_B", mImage, Vector2{ 319.f,336.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->Play(L"Canon_B", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(30.0f, 35.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mTr = GetComponent<Transform>();

		Cannon* canon = dynamic_cast<Cannon*>(owner);
		mDir = canon->GetDir();	
	}

	Cannon_Bullet::~Cannon_Bullet()
	{
	}

	void Cannon_Bullet::Initialize()
	{
		Gameobject::Initialize();		
	}

	void Cannon_Bullet::Update()
	{	
		Vector2 pos = mTr->GetPos();
		Setpos_bullet(pos);


		if (mGroundImage)
		{
			Vector2 Bullet_ps = mTr->GetPos();
			COLORREF FootColor = mGroundImage->GetPixel(static_cast<int>(Bullet_ps.x), static_cast<int>(Bullet_ps.y) + 20);
			if (FootColor == GROUNDCOLOR)
			{
				Bullet_ps.y += 100;
				mTr->SetPos(Bullet_ps);
				this->SetState(eState::Pause);
			}
		}

		Gameobject::Update();
	}

	void Cannon_Bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Cannon_Bullet::Release()
	{
		Gameobject::Release();
	}
}
