#include "jk_Canon_Bullet.h"
#include "jk_Cannon.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Ground.h"

#include "jk_Input.h"
#include "jk_Time.h"

#include "jk_SONIC.h"



namespace jk 
{
	Canon_Bullet::Canon_Bullet(Gameobject* owner)
		: mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, tr(nullptr)
		, mOwner(owner)
		, mDir(-1)
		, check_ground_Cb(0)

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

		tr = GetComponent<Transform>();

		Cannon* canon = dynamic_cast<Cannon*>(owner);
		mDir = canon->GetDir();	
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
		Vector2 pos = tr->GetPos();
		Setpos_bullet(pos);
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
