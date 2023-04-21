#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"

#include "jk_BaseBullet.h"
#include "Bullet_Act1_R_Side.h"
#include "Bullet_Act1_R_DIA.h"
#include "Bullet_Act1_L_Side.h"
#include "Bullet_Act1_L_DIA.h"


namespace jk
{
	Boss::Boss(Gameobject* owner)
		: mCenterpos(Vector2(19860.f, 3480.f))		
		, mMonspeed(200.0f)
		, mMonmaxdistance(100.0f)
		, mDir(-1)
		, time(0)
		, starscene(0)
		, attack_motion(0)
		, Dir_change(0)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();

		////////왼쪽 애니메이션//////////
		//왼쪽 상태변환//1.5f 듀레이션이 천천히 됨 
		mAnimator->CreateAnimation(L"L_Boss_side", mImage, Vector2{ 22,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1,1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_Down", mImage, Vector2{ 624,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol", mImage, Vector2{ 1004,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.1f);


		mAnimator->CreateAnimation(L"L_Boss_side_dianogol", mImage, Vector2{22,13}, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_down", mImage, Vector2{ 254,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_down_dianogol", mImage, Vector2{ 624,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_side", mImage, Vector2{ 1004,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
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
		mAnimator->CreateAnimation(L"R_Boss_side", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol", mImage, Vector2{ 1004,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_Down", mImage, Vector2{ 624,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_Boss_side_dianogol", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_down", mImage, Vector2{ 254,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_down_dianogol", mImage, Vector2{ 624,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_side", mImage, Vector2{ 1004,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
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
				
		
		mAnimator->Play(L"L_Boss_side", true);

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



		case jk::Boss::eBossState::Right:right();
			break;

		case jk::Boss::eBossState::Left:left();
			break;

		case jk::Boss::eBossState::Up:up();
			break;

		case jk::Boss::eBossState::Down:down();
			break;




		case jk::Boss::eBossState::Side_Dianogol:side_dianogol();
			break;

		case jk::Boss::eBossState::Dianogol_Down:dianogol_down();
			break;

		case jk::Boss::eBossState::Down_Dianogol:down_dianogol();
			break;

		case jk::Boss::eBossState::Dianogol_Side:dianogol_side();
			break;

		case jk::Boss::eBossState::Side_Down:side_down();
			break;



		case jk::Boss::eBossState::Attack_Side_Waiting:attack_side_waiting();
			break; 

		case jk::Boss::eBossState::Attack_Dianogol_Waiting:attack_dianogol_waition();
			break;	

		case jk::Boss::eBossState::Attack_Down_Waiting:attack_down_waition();
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
		time += Time::DeltaTime();
		if (time >= 1)
		{
			mState = eBossState::Side_Down;
			mAnimator->Play(L"L_Boss_side_down", false);
			time = 0;
		}


		//mAnimator->GetCompleteEvent(L"L_Boss_side_down") = std::bind(&Boss::side_down, this);
	}

	void Boss::move()
	{
		Transform* tr = GetComponent<Transform>();
	
		fDist = mCenterpos.x - pos.x - mMonmaxdistance;
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= 550.0f)
		{
			mState = eBossState::Down_Dianogol;
			mAnimator->Play(L"L_Boss_down_dianogol", false);
			mDir = -1;
			Dir_change = 1;
		}
		tr->SetPos(pos);
	}




	void Boss::right()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.x - pos.x - mMonmaxdistance;
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -650.0f)
		{
			mState = eBossState::Down_Dianogol;
			mAnimator->Play(L"L_Boss_down_dianogol", false);
			mDir = 1;
			Dir_change = -1;
		}
		tr->SetPos(pos);
	}

	void Boss::left()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.x - pos.x - mMonmaxdistance;
		pos.x -= mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= 550.0f)
		{
			mState = eBossState::Side_Dianogol;
			mAnimator->Play(L"R_Boss_down_dianogol", false);
			mDir = -1;
			Dir_change = -1;
		}
		tr->SetPos(pos);
	}

	void Boss::up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= -100.0f)
		{
			if (mDir == -1)
			{
				mState = eBossState::Side_Dianogol;
				mAnimator->Play(L"R_Boss_dianogol_side", false);
			}
			if (mDir == 1)
			{
				mState = eBossState::Side_Dianogol;
				mAnimator->Play(L"R_Boss_dianogol_side", false);
			}
		}
		tr->SetPos(pos);
	}

	void Boss::down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -350.0f)
		{
			if (mDir == -1)
			{
				mState = eBossState::Dianogol_Side;
				mAnimator->Play(L"R_Boss_dianogol_side", false);
			}
			if (mDir == 1)
			{
				mState = eBossState::Dianogol_Side;
				mAnimator->Play(L"R_Boss_dianogol_side", false);
			}
		}
		tr->SetPos(pos);
	}





	void Boss::side_dianogol()
	{
		if (mDir == -1)
		{
			mState = eBossState::Attack_Dianogol_Waiting;
			mAnimator->Play(L"L_Boss_dianogol_Attack1", false);
		}
		if (mDir == 1)
		{
			mState = eBossState::Attack_Dianogol_Waiting;
			mAnimator->Play(L"R_Boss_dianogol_Attack1", false);
		}
	}

	void Boss::dianogol_side()
	{	
		if (mDir == -1)
		{
			mState = eBossState::Attack_Side_Waiting;
			mAnimator->Play(L"L_Boss_side_Attack1", false);
		}
		if (mDir == 1)
		{
			mState = eBossState::Attack_Side_Waiting;
			mAnimator->Play(L"R_Boss_side_Attack1", false);
		}
	}

	void Boss::dianogol_down()
	{
		if (mDir == -1)
		{
			mState = eBossState::Attack_Dianogol_Waiting;
			mAnimator->Play(L"L_Boss_dianogol_Attack1", false);
		}
		if (mDir == 1)
		{
			mAnimator->Play(L"R_Boss_down_Attack", false);
			//mAnimator->GetCompleteEvent(L"R_Boss_down_Attack") = std::bind(&Boss::attack_down, this);
		}
	}

	void Boss::down_dianogol()
	{
		if (mDir == -1)
		{
			mState = eBossState::Attack_Dianogol_Waiting;
			mAnimator->Play(L"L_Boss_dianogol_Attack1", false);
		}
		if (mDir == 1)
		{
			mState = eBossState::Attack_Dianogol_Waiting;
			mAnimator->Play(L"R_Boss_dianogol_Attack1", false);
		}
	}

	void Boss::side_down()
	{	
		if (mDir == -1)
		{
			mState = eBossState::Attack_Down_Waiting;			
			mAnimator->Play(L"L_Boss_down_Attack", false);
		}
	}





	void Boss::attack_side()
	{
		if (mDir == -1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Side_Waiting;
					mAnimator->Play(L"L_Boss_side_Attack2", false);
					time = 0;
					attack_motion = 1;
				}
				else
				{
					//미사일2 넣기 location change				
					mState = eBossState::Up;
					mAnimator->Play(L"L_Boss_side", false);
					time = 0;
					Dir_change = 1;	
					attack_motion = 0;
				}
			}
		}
		else if (mDir == 1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Side_Waiting;
					mAnimator->Play(L"R_Boss_side_Attack2", false);
					time = 0;
					attack_motion = 1;
				}
				else
				{
					//미사일2 넣기 location change
				
					mState = eBossState::Up;
					mAnimator->Play(L"R_Boss_side", false);
					time = 0;	
					Dir_change = 1;
					attack_motion = 0;
				}
			}
		}
	}

	void Boss::attack_side_waiting()
	{
		mAnimator->GetCompleteEvent(L"L_Boss_side_Attack1") = std::bind(&Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"L_Boss_side_Attack2") = std::bind(&Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"R_Boss_side_Attack1") = std::bind(&Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"R_Boss_side_Attack2") = std::bind(&Boss::attack_side, this);
	}


	void Boss::attack_dianogol()
	{
		if(mDir == -1)
		{	
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Dianogol_Waiting;
					mAnimator->Play(L"L_Boss_dianogol_Attack2", false);
					time = 0;
					attack_motion = -1;
				}
				else
				{
					//미사일2 넣기 location change
					if (Dir_change == 1)
					{
						mState = eBossState::Right;
						mAnimator->Play(L"L_Boss_dianogol", false);
						time = 0;
						Dir_change = -1;						
					}
					else if (Dir_change == -1)
					{
						mState = eBossState::Down;
						mAnimator->Play(L"L_Boss_dianogol", false);
						time = 0;
						attack_motion = 0;
					}						
				}
			}	
		}
		else if(mDir == 1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Dianogol_Waiting;
					mAnimator->Play(L"R_Boss_dianogol_Attack2", false);
					time = 0;
					attack_motion = 1;
				}
				else
				{
					//미사일2 넣기 location change
					if (Dir_change == 1)
					{
						mState = eBossState::Left;
						mAnimator->Play(L"R_Boss_dianogol", false);
						time = 0;
						Dir_change = -1;
					}
					else if (Dir_change == -1)
					{
						mState = eBossState::Down;
						mAnimator->Play(L"R_Boss_dianogol", false);
						time = 0;	
						attack_motion = 0;
					}					
				}
			}
		}
	}

	void Boss::attack_dianogol_waition()
	{		
		mAnimator->GetCompleteEvent(L"L_Boss_dianogol_Attack1") = std::bind(&Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"L_Boss_dianogol_Attack2") = std::bind(&Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"R_Boss_dianogol_Attack1") = std::bind(&Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"R_Boss_dianogol_Attack2") = std::bind(&Boss::attack_dianogol, this);
	}


	void Boss::attack_down()
	{
		if (mDir == -1)
		{
			//미사일 넣기
			time += Time::DeltaTime();
			if (time >= 2)
			{
				mState = eBossState::Move;
				mAnimator->Play(L"L_Boss_Down", false);
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

	void Boss::attack_down_waition()
	{
		mAnimator->GetCompleteEvent(L"L_Boss_down_Attack") = std::bind(&Boss::attack_down, this);
		mAnimator->GetCompleteEvent(L"R_Boss_down_Attack") = std::bind(&Boss::attack_down, this);
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

