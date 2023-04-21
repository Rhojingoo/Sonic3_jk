#include "Boss_act1_boomb.h"
#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"


namespace jk
{
	Boss_act1_boomb::Boss_act1_boomb(Gameobject* owner)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"L_Boss_run", mImage, Vector2{ 625,1118 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 9, 1, 9, Vector2::Zero, 0.1f);
		mAnimator->Play(L"L_Boss_run", true);
	}
	Boss_act1_boomb::~Boss_act1_boomb()
	{
	}
	void Boss_act1_boomb::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss_act1_boomb::Update()
	{
		Gameobject::Update();
	}
	void Boss_act1_boomb::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss_act1_boomb::Release()
	{
		Gameobject::Release();
	}
	void Boss_act1_boomb::move()
	{
	}
}
