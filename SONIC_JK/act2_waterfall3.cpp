#include "act2_waterfall3.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"


namespace jk
{
	act2_waterfall3::act2_waterfall3()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act2_waterfall3::~act2_waterfall3()
	{
	}
	void act2_waterfall3::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"act2_waterfall_3", L"..\\Resources\\ActBG_1_2\\act2_waterfall_3.bmp");
		mAnimator->CreateAnimation(L"act2_waterfall_3", mImage, Vector2(0, 0), Vector2(648, 752), Vector2(8, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"act2_waterfall_3", true);

		Gameobject::Initialize();
	}
	void act2_waterfall3::Update()
	{
		Gameobject::Update();
	}
	void act2_waterfall3::Render(HDC hdc)
	{
		Gameobject::Render(hdc);			
	}
	void act2_waterfall3::Release()
	{
		Gameobject::Release();
	}	
	void act2_waterfall3::OnCollisionEnter(Collider* other)
	{
	}
	void act2_waterfall3::OnCollisionStay(Collider* other)
	{
	}
	void act2_waterfall3::OnCollisionExit(Collider* other)
	{
	}
}