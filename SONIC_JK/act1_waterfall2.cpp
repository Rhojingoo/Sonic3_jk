#include "act1_waterfall2.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"

namespace jk
{
	act1_waterfall2::act1_waterfall2()
	{
	}
	act1_waterfall2::~act1_waterfall2()
	{
	}
	void act1_waterfall2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();

		mImage = Resources::Load<Image>(L"act1_waterfall_2", L"..\\Resources\\act1_waterfall_2.bmp");
		mAnimator->CreateAnimation(L"act1_waterfall_2", mImage, Vector2(0, 1), Vector2(343, 1292), Vector2(9, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"act1_waterfall_2", true);

		Gameobject::Initialize();
	}
	void act1_waterfall2::Update()
	{
		Gameobject::Update();
	}
	void act1_waterfall2::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act1_waterfall2::Release()
	{
		Gameobject::Release();
	}
	void act1_waterfall2::OnCollisionEnter(Collider* other)
	{
	}
	void act1_waterfall2::OnCollisionStay(Collider* other)
	{
	}
	void act1_waterfall2::OnCollisionExit(Collider* other)
	{
	}
}
