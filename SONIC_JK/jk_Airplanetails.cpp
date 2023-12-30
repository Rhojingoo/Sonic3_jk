#include "jk_Airplanetails.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Image.h"

#include "jk_Time.h"

namespace jk
{

	Airplanetails::Airplanetails()
		: mDir(1)
		, mCenterpos(Vector2(600.0f, 232.0f))
		, mSpeed(300.0f)
		, mMaxdistance(700.0f)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{



	}

	Airplanetails::~Airplanetails()
	{
	}

	void Airplanetails::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 600.0f, 232.0f });
		mImage = Resources::Load<Image>(L"plane_BG", L"..\\Resources\\Title\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"Titleplane", mImage, Vector2(340, 787), Vector2(48, 30), Vector2(2, 0), 2, 1, 2, Vector2::Zero, 0.1f);
		mImage = Resources::Load<Image>(L"plane_BG", L"..\\Resources\\Title\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"LTitleplane", mImage, Vector2(448, 787), Vector2(48, 30), Vector2(2, 0), 2, 1, 2, Vector2::Zero, 0.1f);
	}

	void Airplanetails::Update()
	{
		Gameobject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		float fDist = abs(mCenterpos.x - pos.x) - mMaxdistance;
		if (fDist > 0.0f)
		{
			mDir *= -1;
			pos.x += fDist * mDir;
		}
		else
		{
			pos.x += mSpeed * (float)Time::DeltaTime() * mDir;
		}
		if (mDir == 1)
			mAnimator->Play(L"Titleplane", true);
		else
			mAnimator->Play(L"LTitleplane", true);

		tr->SetPos(pos);
	}

	void Airplanetails::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Airplanetails::Release()
	{
		Gameobject::Release();
	}
}