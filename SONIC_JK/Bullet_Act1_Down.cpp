#include "Bullet_Act1_Down.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Time.h"

#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_Last_Bridge.h"
#include "jk_Object.h"

namespace jk
{
	BaseBullet::BaseBullet(Gameobject* owner)
		: mOwner(owner)
		, mAnimator(nullptr)
		, mImage(nullptr)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Rbullet_Down", mImage, Vector2(1367, 18), Vector2(32, 48), Vector2(8, 0), 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Rbullet_Down", true);


		Collider* collider = AddComponent<Collider>();		
		collider->SetSize(Vector2(72.0f, 120.0f));
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
		pos.y += 150.0f * static_cast<float>(Time::DeltaTime());
		tr->SetPos(pos);	
		Setpos_bullet(pos);
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

	void BaseBullet::OnCollisionEnter(Collider* other)
	{
		if (Last_Bridge* last_bridge = dynamic_cast<Last_Bridge*>(other->GetOwner()))
		{
		 object::Destory(this);
		}
	}
	
	void BaseBullet::OnCollisionStay(Collider* other)
	{
	}
	void BaseBullet::OnCollisionExit(Collider* other)
	{
	}
}