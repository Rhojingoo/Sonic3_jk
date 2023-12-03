#include "Boss_Run.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"



namespace jk
{
	Boss_Run::Boss_Run(Gameobject* owner)
		: mDir(0)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"L_Boss_run", mImage, Vector2{ 690,208 }, Vector2{ 70,64 }, Vector2{ 6,0 }, 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->Play(L"L_Boss_run", true);
	}
	Boss_Run::~Boss_Run()
	{
	}
	void Boss_Run::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss_Run::Update()
	{
		if (mDir == 0)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPos(pos);
		}
		else if (mDir == 1)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			pos.y -= 300.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPos(pos);
		}
		Gameobject::Update();
	}
	void Boss_Run::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss_Run::Release()
	{
		Gameobject::Release();
	}
}
