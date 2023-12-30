#include "jk_Callapses.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "Rigidbody.h"
#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_SONIC.h"

namespace jk
{
	Callapses::Callapses()
		: mImage(nullptr)
		, mRigidbody(nullptr)
		, mAnimator(nullptr)
	{
		mImage = Resources::Load<Image>(L"Rock_Platform2", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Gr_collapses", mImage, Vector2(499, 634), Vector2(136, 88), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Gr_collapses", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}

	Callapses::~Callapses()
	{
	}

	void Callapses::Initialize()
	{
		Gameobject::Initialize();
	}
	void Callapses::Update()
	{
		Gameobject::Update();
	}
	void Callapses::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Callapses::Release()
	{
		Gameobject::Release();
	}

	void Callapses::idle()
	{
	}
	void Callapses::death()
	{
	}
}
