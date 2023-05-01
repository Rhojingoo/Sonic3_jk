#include "Boss_appear.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Ground.h"
#include "jk_Object.h"

namespace jk
{
	Boss_appear::Boss_appear(Gameobject* owner)
		: mMonspeed(1650.0f)
		, mDir(1)
		, pos(0.f, 0.f)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"Boss_apear", mImage, Vector2{ 388,232 }, Vector2{ 64,56 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);

	
		mAnimator->Play(L"Boss_apear", true);
	}
	Boss_appear::~Boss_appear()
	{
	}
	void Boss_appear::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss_appear::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		tr->SetPos(pos);
		Gameobject::Update();
	}
	void Boss_appear::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss_appear::Release()
	{
		Gameobject::Release();
	}
	void Boss_appear::move()
	{
	}
	void Boss_appear::death()
	{
	}
}