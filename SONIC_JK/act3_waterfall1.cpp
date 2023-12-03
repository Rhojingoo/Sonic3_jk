#include "act3_waterfall1.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Scene.h"



namespace jk
{
	act3_waterfall1::act3_waterfall1()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act3_waterfall1::~act3_waterfall1()
	{
	}
	void act3_waterfall1::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"act3_waterfall", L"..\\Resources\\ActBG_1_3\\act3_waterfall.bmp");
		mAnimator->CreateAnimation(L"act3_waterfall", mImage, Vector2(0, 0), Vector2(776, 1644), Vector2(8, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"act3_waterfall", true);

		Gameobject::Initialize();
	}
	void act3_waterfall1::Update()
	{
		Gameobject::Update();
	}
	void act3_waterfall1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act3_waterfall1::Release()
	{
		Gameobject::Release();
	}
	void act3_waterfall1::OnCollisionEnter(Collider* other)
	{
	}
	void act3_waterfall1::OnCollisionStay(Collider* other)
	{
	}
	void act3_waterfall1::OnCollisionExit(Collider* other)
	{
	}
}