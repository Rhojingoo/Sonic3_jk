#include "act1_waterfall3.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"

namespace jk
{
	act1_waterfall3::act1_waterfall3()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act1_waterfall3::~act1_waterfall3()
	{
	}
	void act1_waterfall3::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		mImage = Resources::Load<Image>(L"act1_waterfall_3", L"..\\Resources\\act1_waterfall_3.bmp");
		mAnimator->CreateAnimation(L"act1_waterfall_3", mImage, Vector2(0, 0), Vector2(665, 912), Vector2(9, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->Play(L"act1_waterfall_3", true);

		Gameobject::Initialize();
	}
	void act1_waterfall3::Update()
	{
		Gameobject::Update();
	}
	void act1_waterfall3::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act1_waterfall3::Release()
	{
		Gameobject::Release();
	}
	void act1_waterfall3::OnCollisionEnter(Collider* other)
	{
	}
	void act1_waterfall3::OnCollisionStay(Collider* other)
	{
	}
	void act1_waterfall3::OnCollisionExit(Collider* other)
	{
	}
}