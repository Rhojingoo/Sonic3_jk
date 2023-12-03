#include "Elec_effect.h"
#include "Electsonic.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"




namespace jk
{
	Elec_effect::Elec_effect(Gameobject* owner)
		: mOwner(owner)
		, mAnimator(nullptr)
	{		
		Image* mImage = Resources::Load<Image>(L"shield", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Elect_effect", mImage, Vector2(556, 472), Vector2(16, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.05f);
		mAnimator->Play(L"Elect_effect", true);

	}
	Elec_effect::~Elec_effect()
	{
	}
	void Elec_effect::Initialize()
	{
		Gameobject::Initialize();
	}
	void Elec_effect::Update()
	{
		Gameobject::Update();
	}
	void Elec_effect::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Elec_effect::Release()
	{
		Gameobject::Release();
	}
}