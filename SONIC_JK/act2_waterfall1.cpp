#include "act2_waterfall1.h"
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
	act2_waterfall1::act2_waterfall1()
	{
	}
	act2_waterfall1::~act2_waterfall1()
	{
	}
	void act2_waterfall1::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();

		mImage = Resources::Load<Image>(L"act2_waterfall_1", L"..\\Resources\\ActBG_1_2\\act2_waterfall_1.bmp");
		mAnimator->CreateAnimation(L"act2_waterfall_1", mImage, Vector2(0, 0), Vector2(280, 80), Vector2(8, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"act2_waterfall_1", true);

		Gameobject::Initialize();
	}
	void act2_waterfall1::Update()
	{
		Gameobject::Update();
	}
	void act2_waterfall1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act2_waterfall1::Release()
	{
		Gameobject::Release();
	}
	void act2_waterfall1::OnCollisionEnter(Collider* other)
	{
	}
	void act2_waterfall1::OnCollisionStay(Collider* other)
	{
	}
	void act2_waterfall1::OnCollisionExit(Collider* other)
	{
	}
}
