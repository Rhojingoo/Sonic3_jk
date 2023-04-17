#include "jk_Monket_Bullet.h"
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
#include "Rigidbody.h"
#include "jk_Scene.h"
#include "jk_Object.h"

int check_ground_Mb = 0;

namespace jk
{
	Monket_Bullet::Monket_Bullet(Gameobject* owner)
	{
		mImage = Resources::Load<Image>(L"Monket_Bullet", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RM_B", mImage, Vector2{ 542.f,204.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LM_B", mImage, Vector2{ 542.f,72.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mAnimator->Play(L"LM_B", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(30.0f, 35.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });
		mOwner = owner;
		check_ground_Mb = 0;
	}
	Monket_Bullet::~Monket_Bullet()
	{
	}
	void Monket_Bullet::Initialize()
	{
		Gameobject::Initialize();
	}
	void Monket_Bullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 Bullet_ps = tr->GetPos();
		Rigidbody* rb = GetComponent<Rigidbody>();

		if (tr && rb && mGroundImage)
		{			
			COLORREF RING_Color = mGroundImage->GetPixel(Bullet_ps.x, Bullet_ps.y + 16);
			if (RING_Color == RGB(0, 0, 0))
			{
				COLORREF RING_Color = mGroundImage->GetPixel(Bullet_ps.x, Bullet_ps.y + 16);

				while (RING_Color == RGB(0, 0, 0))
				{
					Bullet_ps.y -= 1;
					RING_Color = mGroundImage->GetPixel(Bullet_ps.x, Bullet_ps.y + 16);
					tr->SetPos(Bullet_ps);
					rb->SetGround(true);
					check_ground_Mb = 1;
				}
			}
		}
		if (check_ground_Mb > 0)
		{
			jk::object::Destory(this);
			return;
		}

		//	Sonic = mOwner->GetComponent<Transform>()->GetPos();		
		//		if (Sonic.x > pos.x)
		//{
		//	pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
		//	pos.y += 150.0f * static_cast<float>(Time::DeltaTime());
		//	mAnimator->Play(L"RM_B", true);
		//}
		//if (Sonic.x < pos.x)
		//{
		//	pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
		//	pos.y += 150.0f * static_cast<float>(Time::DeltaTime());
		//	mAnimator->Play(L"LM_B", true);
		//}
		//

		tr->SetPos(Bullet_ps);

		Gameobject::Update();
	}
	void Monket_Bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Monket_Bullet::Release()
	{
		Gameobject::Release();
	}
	void Monket_Bullet::OnCollisionEnter(Collider* other)
	{
	}
	void Monket_Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Monket_Bullet::OnCollisionExit(Collider* other)
	{
	}
}                          