#include "jk_Canon_Bullet.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "SonicState.h"
#include "jk_BaseBullet.h"
#include "jk_Ground.h"
#include "Rigidbody.h"
#include "jk_Cannon.h"
#include "jk_Object.h"

int check_ground_Cb = 0;

namespace jk 
{
	Canon_Bullet::Canon_Bullet(Gameobject* owner)
		:mDir(-1)
	{
		mImage = Resources::Load<Image>(L"Canon_B", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Canon_B", mImage, Vector2{ 319.f,336.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(30.0f, 35.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
	
		mOwner = owner;
		Cannon* canon = new Cannon(this);
		mDir = canon->GetDir();
		check_ground_Cb = 0;
	}
	Canon_Bullet::~Canon_Bullet()
	{
	}
	void Canon_Bullet::Initialize()
	{

		Gameobject::Initialize();
		
	}
	void Canon_Bullet::Update()
	{		


		Transform* rock_TR = GetComponent<Transform>();
		Rigidbody* rock_rb = GetComponent<Rigidbody>();
		

		if (rock_TR && rock_rb && mGroundImage)
		{
			Vector2 Ring_ps = rock_TR->GetPos();
			COLORREF RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y + 30);
			if (RING_Color == RGB(0, 0, 0))
			{
				COLORREF RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y+30);

				while (RING_Color == RGB(0, 0, 0))
				{
					Ring_ps.y -= 1;
					RING_Color = mGroundImage->GetPixel(Ring_ps.x, Ring_ps.y +30);
					rock_TR->SetPos(Ring_ps);
					rock_rb->SetGround(true);
					check_ground_Cb = 1;
				}
			}	
		}

		if (check_ground_Cb > 0)
		{
			jk::object::Destory(this);
			return;
		}


		mAnimator->Play(L"Canon_B", true);			

		Gameobject::Update();
	}
	void Canon_Bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Canon_Bullet::Release()
	{
		Gameobject::Release();
	}
}
