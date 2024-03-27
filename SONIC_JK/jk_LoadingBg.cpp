#include "jk_LoadingBg.h"
#include "jk_Time.h"
#include "jk_Input.h"


#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Image.h"
#include "jk_Animation.h"
#include "jk_Animator.h"

namespace jk
{
	LoadingBg::LoadingBg()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
	}
	LoadingBg::~LoadingBg()
	{
	}
	void LoadingBg::Initialize()
	{		
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 0.0f, 0.0f });
		tr->SetScale(Vector2{ 1.0f, 1.f });
		mImage = Resources::Load<Image>(L"LoadingSC", L"..\\Resources\\SonicLoading.bmp");	

		Gameobject::Initialize();
	}
	void LoadingBg::Update()
	{
		Gameobject::Update();
	}
	void LoadingBg::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), 0, 0, 960, 720, RGB(1, 1, 1));
	}
	void LoadingBg::Release()
	{
		Gameobject::Release();
	}
}