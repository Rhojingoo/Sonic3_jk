#include "act1_waterfall1.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"


namespace jk
{
	act1_waterfall1::act1_waterfall1()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act1_waterfall1::~act1_waterfall1()
	{
	}
	void act1_waterfall1::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"act1_waterfall_1", L"..\\Resources\\act1_waterfall_1.bmp");
		mAnimator->CreateAnimation(L"act1_waterfall_1", mImage, Vector2(0, 0), Vector2(713, 1072), Vector2(8, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"act1_waterfall_1", true);
		Gameobject::Initialize();

	}
	void act1_waterfall1::Update()
	{
		Gameobject::Update();
	}
	void act1_waterfall1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act1_waterfall1::Release()
	{
		Gameobject::Release();
	}
	void act1_waterfall1::OnCollisionEnter(Collider* other)
	{
	}
	void act1_waterfall1::OnCollisionStay(Collider* other)
	{
	}
	void act1_waterfall1::OnCollisionExit(Collider* other)
	{
	}
}