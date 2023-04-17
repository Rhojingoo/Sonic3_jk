#include "jk_Airplanetails.h"
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

	Airplanetails::Airplanetails()
		: mDir(1)
		, mState(eState::Move)	
		, mCenterpos(Vector2(600.0f, 232.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mspeed(300.0f)
		, maxdistance(700.0f)
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
		//tr->SetScale(Vector2{ 1.3f, 1.2f });
		mImage = Resources::Load<Image>(L"plane_BG", L"..\\Resources\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"Titleplane", mImage, Vector2(340, 787), Vector2(48, 30), Vector2(2, 0), 2, 1, 2, Vector2::Zero, 0.1);
		mImage = Resources::Load<Image>(L"plane_BG", L"..\\Resources\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"LTitleplane", mImage, Vector2(448, 787), Vector2(48, 30), Vector2(2, 0), 2, 1, 2, Vector2::Zero, 0.1);
	}

	void Airplanetails::Update()
	{
		Gameobject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//현재의 위치좌표 정보얻을 필요있음.(20,20  67,51) 750.0f, 320.0f


		////배회거리 기준량을 넘어섰는지 확인		
		float fDist = abs(mCenterpos.x - pos.x) - maxdistance;
		if (fDist > 0.0f)
		{
			mDir *= -1;
			pos.x += fDist * mDir;
		}
		else
		{
			pos.x += mspeed * (float)Time::DeltaTime() * mDir;
		}
		if (mDir == 1)
			mAnimator->Play(L"Titleplane", true);
		else
			mAnimator->Play(L"LTitleplane", true);


		//실험용 컨트롤
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 100.0f * (float)Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 100.0f * (float)Time::DeltaTime();
		}

		tr->SetPos(pos);
	

		//switch (mState)
		//{
		//case Airplanetails::eState::Move:
		//	move();
		//	break;

		//default:
		//	break;
		//}
	}

	void Airplanetails::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Airplanetails::Release()
	{
		Gameobject::Release();
	}


	void Airplanetails::move()
	{
	}

}