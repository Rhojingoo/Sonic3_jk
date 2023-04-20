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
#include "jk_Object.h"

namespace jk
{
	Boss::Boss(Gameobject* owner)
		: //mCenterpos(Vector2(500.0f, 151.0f))
		 mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(200.0f)
		, mMonmaxdistance(300.0f)
		, mDir(-1)
		, time(0)
		, starscene(0)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();

		////////왼쪽 애니메이션//////////
		//왼쪽 상태변환
		mAnimator->CreateAnimation(L"L_Boss_Idle", mImage, Vector2{ 22,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->CreateAnimation(L"L_Boss_side_dianogol", mImage, Vector2{22,13}, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_down", mImage, Vector2{ 254,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_down_dianogol", mImage, Vector2{ 624,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_down_dianogol", mImage, Vector2{ 1004,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_down", mImage, Vector2{ 22,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		
		//왼쪽 타격			
		mAnimator->CreateAnimation(L"L_Boss_down_hurt", mImage, Vector2{ 624,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_hurt", mImage, Vector2{ 981,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_hurt", mImage, Vector2{ 1337,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);

		//왼쪽 공격	
		mAnimator->CreateAnimation(L"L_Boss_down_Attack", mImage, Vector2{ 625,835 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_Attack1", mImage, Vector2{ 625,930 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_Attack2", mImage, Vector2{ 1205,930 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_Attack1", mImage, Vector2{ 625,1023 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_Attack2", mImage, Vector2{ 1205,1023 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);


		
		////////오른쪽 애니메이션//////////
		//오른쪽 상태변환
		mAnimator->CreateAnimation(L"R_Boss_side_dianogol", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_down", mImage, Vector2{ 254,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_down_dianogol", mImage, Vector2{ 624,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_down_dianogol", mImage, Vector2{ 1004,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_side_down", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.5f);

		//오른쪽 타격			
		mAnimator->CreateAnimation(L"R_Boss_down_hurt", mImage, Vector2{ 624,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_hurt", mImage, Vector2{ 981,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_hurt", mImage, Vector2{ 1337,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);

		//오른쪽 공격	
		mAnimator->CreateAnimation(L"R_Boss_down_Attack", mImage, Vector2{ 625,529 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_Attack1", mImage, Vector2{ 625,624 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_Attack2", mImage, Vector2{ 1205,624 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_Attack1", mImage, Vector2{ 625,717 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_Attack2", mImage, Vector2{ 1205,717 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
				
		
		mAnimator->Play(L"L_Boss_Idle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(261.0f, 250.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.05f) * size.x, (-0.3f) * size.y });
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{		
		Gameobject::Initialize();
	}
	void Boss::Update()
	{			
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::Boss::eBossState::Idle:idle();
			break;

		case jk::Boss::eBossState::Move:move();
			break;

		case jk::Boss::eBossState::Side_Dianogol:side_dianogol();
			break;

		case jk::Boss::eBossState::Dianogol_Down:dianogol_down();
			break;

		case jk::Boss::eBossState::Down_Dianogol:down_dianogol();
			break;

		case jk::Boss::eBossState::Side_Down:side_down();
			break;

		case jk::Boss::eBossState::Attack_Side:attack_side();
			break;

		case jk::Boss::eBossState::Attack_Dianogol:attack_dianogol();
			break;

		case jk::Boss::eBossState::Attack_Down:attack_down();
			break;

		case jk::Boss::eBossState::Hurt_Down:hurt_down();
			break;

		case jk::Boss::eBossState::Hurt_Side:hurt_side();
			break;

		case jk::Boss::eBossState::Hurt_Dianogol:hurt_dianogol();
			break;

		case jk::Boss::eBossState::Death:death();
			break;

		default:
			break;
		}			

		Gameobject::Update();
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

	void Boss::idle()
	{
		mState = eBossState::Side_Down;
		mAnimator->Play(L"L_Boss_side_down", false);
		//mAnimator->GetCompleteEvent(L"L_Boss_side_down") = std::bind(&Boss::side_down, this);
	}

	void Boss::move()
	{
		Transform* tr = GetComponent<Transform>();
	
		fDist = mCenterpos.x - pos.x - mMonmaxdistance;
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -100.0f)
		{
			//mState = eState::Down;
			//mAnimator->Play(L"L_mBoss", true);
			mDir = -1;
		}
		tr->SetPos(pos);
	}

	void Boss::side_dianogol()
	{
	}

	void Boss::dianogol_down()
	{
	}

	void Boss::down_dianogol()
	{
	}

	void Boss::side_down()
	{	
		if (mDir == -1)
		{
			mAnimator->Play(L"L_Boss_down_Attack", false);
			mAnimator->GetCompleteEvent(L"L_Boss_down_Attack") = std::bind(&Boss::attack_down, this);
		}
		if (mDir == 1)
		{
			mAnimator->Play(L"R_Boss_down_Attack", false);
			mAnimator->GetCompleteEvent(L"R_Boss_down_Attack") = std::bind(&Boss::attack_down, this);
		}
	}

	void Boss::attack_side()
	{
	}

	void Boss::attack_dianogol()
	{
	}

	void Boss::attack_down()
	{
		if (mDir == -1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 3)
			{
				mState = eBossState::Move;
				mAnimator->Play(L"L_Boss_side_down", false);
				time = 0;
			}
		}
		else if (mDir == 1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 3)
			{
				mState = eBossState::Side_Down;
				mAnimator->Play(L"L_Boss_side_down", false);
				time = 0;
			}
		}		
		else if (starscene == 0)
		{
			mState = eBossState::Move;
			starscene = 1;
		}
	}

	void Boss::hurt_down()
	{
	}

	void Boss::hurt_side()
	{
	}

	void Boss::hurt_dianogol()
	{
	}
	void Boss::death()
	{
	}

}	


//Transform* tr = GetComponent<Transform>();
		//if (mDir == 1 || mDir == -1)//Input::GetKey(eKeyCode::Z)
		//{
		//	Scene* curScene = SceneManager::GetActiveScene();
		//	BaseBullet* bullet = new BaseBullet(this);
		//	bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		//	curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
		//	mState = eBossState::Move;
		//}'







	//예전에 업데이트 단에 있던것.
		//현재의 위치좌표 정보얻을 필요있음.(20,20  67,51) 750.0f, 320.0f


		//////배회거리 기준량을 넘어섰는지 확인		
		//float fDist = abs(mCenterpos.x - pos.x) - mMonmaxdistance;
		//if (fDist > 0.0f)
		//{
		//	//방향변경
		//	mDir *= -1;
		//	pos.x += fDist * mDir;
		//	mState = eBossState::Attack;

		//}
		//else////진행방향으로 시간당 mMonspeed 만큼이동
		//{
		//	pos.x += mMonspeed * static_cast<float>(Time::DeltaTime()) * mDir;
		//}
		//if (mDir == 1)
		//	mAnimator->Play(L"LROBOT", true);
		//else
		//	mAnimator->Play(L"RROBOT", true);


		////실험용 컨트롤
		//if (Input::GetKey(eKeyCode::Q))
		//{
		//	pos.x -= 100.0f * static_cast<float>(Time::DeltaTime());
		//}
		//if (Input::GetKey(eKeyCode::E))
		//{
		//	pos.x += 100.0f * static_cast<float>(Time::DeltaTime());
		//}

		//tr->SetPos(pos);
