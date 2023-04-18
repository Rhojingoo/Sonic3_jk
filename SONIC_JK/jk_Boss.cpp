#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_BaseBullet.h"


namespace jk
{
	Boss::Boss(Gameobject* owner)
		: mCenterpos(Vector2(500.0f, 151.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(200.0f)
		, mMonmaxdistance(300.0f)
		, mDir(-1)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(2790.0f, 3050.0f));
		//2790.0f * 3, 3200.f
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
	/*	Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(750.0f, 151.0f));*/
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RROBOT", mImage, Vector2::rRobotAtackLTC, Vector2::rRobotAtacksize, Vector2::rRobotAtackSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LROBOT", mImage, Vector2::lRobotAtackLTC, Vector2::lRobotAtacksize, Vector2::lRobotAtackSpace, 1, 1, 1, Vector2::Zero, 0.1f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(261.0f, 250.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.05f) * size.x, (-0.3f) * size.y });
		
		Gameobject::Initialize();
	}
	void Boss::Update()
	{	
		Gameobject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//현재의 위치좌표 정보얻을 필요있음.(20,20  67,51) 750.0f, 320.0f
	

		////배회거리 기준량을 넘어섰는지 확인		
		float fDist = abs(mCenterpos.x - pos.x) - mMonmaxdistance;
		if (fDist > 0.0f)
		{
			//방향변경
			mDir *= -1;
			pos.x += fDist * mDir;
			mState = eBossState::Attack;

		}
		else////진행방향으로 시간당 mMonspeed 만큼이동
		{
			pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir;
		}
		if (mDir == 1)
			mAnimator->Play(L"LROBOT", true);
		else
			mAnimator->Play(L"RROBOT", true);


		//실험용 컨트롤
		if (Input::GetKey(eKeyCode::Q))
		{
			pos.x -= 100.0f * static_cast<float>(Time::DeltaTime());
		}
		if (Input::GetKey(eKeyCode::E))
		{
			pos.x += 100.0f * static_cast<float>(Time::DeltaTime());
		}

		tr->SetPos(pos);


		switch (mState)
		{
		case jk::Boss::eBossState::Move:move();
			break;

		case jk::Boss::eBossState::Attack:attack();
			break;

		case jk::Boss::eBossState::Hit:hit();
			break;

		case jk::Boss::eBossState::Death:death();
			break;


		default:
			break;
		}			
	}

	void Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss::Release()
	{
		Gameobject::Release();
	}

	void Boss::OnCollisionEnter(Collider* other)
	{
	}

	void Boss::OnCollisionStay(Collider* other)
	{
	}

	void Boss::OnCollisionExit(Collider* other)
	{
	}

	void Boss::move()
	{
	}

	void Boss::attack()
	{
		Transform* tr = GetComponent<Transform>();
		if (mDir == 1 || mDir == -1)//Input::GetKey(eKeyCode::Z)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet(this);
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
			mState = eBossState::Move;
		}
	}

	void Boss::hit()
	{
	}

	void Boss::death()
	{
	}
}