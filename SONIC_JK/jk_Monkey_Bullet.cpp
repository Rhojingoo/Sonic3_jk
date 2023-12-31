#include "jk_Monkey_Bullet.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Object.h"


namespace jk
{
	Monkey_Bullet::Monkey_Bullet(Gameobject* owner)
		: mCurpos(0.f,0.f)
		, mOwner(owner)
		, mRigidbody(nullptr)
		, mTr(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mCheck_Ground(0)
	{
		mImage = Resources::Load<Image>(L"Monket_Bullet", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RM_B", mImage, Vector2{ 542.f,204.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LM_B", mImage, Vector2{ 542.f,72.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mAnimator->Play(L"LM_B", true);

		mTr = GetComponent<Transform>();

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(30.0f, 35.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });
	
		mCheck_Ground = 0;
	}
	Monkey_Bullet::~Monkey_Bullet()
	{
	}
	void Monkey_Bullet::Initialize()
	{
		Gameobject::Initialize();
	}
	void Monkey_Bullet::Update()
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
	void Monkey_Bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Monkey_Bullet::Release()
	{
		Gameobject::Release();
	}
	void Monkey_Bullet::OnCollisionEnter(Collider* other)
	{
	}
	void Monkey_Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Monkey_Bullet::OnCollisionExit(Collider* other)
	{
	}
}                          