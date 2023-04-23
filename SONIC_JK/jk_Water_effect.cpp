#include "jk_Water_effect.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_SONIC.h"


namespace jk
{
	Water_effect::Water_effect()
	{
		mImage = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Water_Effect_act1", mImage, Vector2(24, 370), Vector2(40, 32), Vector2(8, 0), 7, 1,7, Vector2::Zero, 0.1);
		mAnimator->Play(L"Water_Effect_act1", false);

		//Collider* collider = AddComponent<Collider>();
		//collider->SetSize(Vector2(90.0f, 85.0f));
		//Vector2 size = collider->GetSize();
		//collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
	}
	Water_effect::~Water_effect()
	{
	}
	void Water_effect::Initialize()
	{
		Gameobject::Initialize();
	}

	void Water_effect::Update()
	{

		Gameobject::Update();
	}

	void Water_effect::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Water_effect::Release()
	{
		Gameobject::Release();
	}

}