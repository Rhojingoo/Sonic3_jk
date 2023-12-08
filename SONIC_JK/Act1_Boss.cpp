#include "Act1_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"


#include "jk_BaseBullet.h"
#include "Bullet_Act1_R_Side.h"
#include "Bullet_Act1_R_DIA.h"
#include "Bullet_Act1_L_Side.h"
#include "Bullet_Act1_L_DIA.h"
#include "Boss_Run.h"
#include "Boss_act1_boomb.h"


namespace jk
{
	Act1_Boss::Act1_Boss(Gameobject* owner)
		: mCenterpos(Vector2(19860.f, 3480.f))	
		, pos(0.f,0.f)
		, mMonspeed(200.0f)
		, mMonmaxdistance(100.0f)
		, fDist(0.f)
		, mDir(-1)
		, time(0)
		, attack_check(0)
		, starscene(0)
		, attack_motion(0)
		, Dir_change(0)
		, hurt_state(0)
		, Damege_sheck(0)
		, Death_check(0)
		, sonicState()
		, mOwner(owner)
		, mState()
		, boss_run(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, Boss_Hit(nullptr)
		, Boss_Bomb(nullptr)
		, Boss_Start(nullptr)
		, Act2_music(nullptr)
		, mRigidbody(nullptr)

	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();

		Boss_Hit = Resources::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\Boss_hit.wav");
		Boss_Bomb = Resources::Load<Sound>(L"Boss_death", L"..\\Resources\\Sound\\Boss_death.wav");
		Boss_Start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		Act2_music = Resources::Load<Sound>(L"Act2_bg", L"..\\Resources\\Sound\\Act2_bg.wav");




		////////���� �ִϸ��̼�//////////
		mAnimator->CreateAnimation(L"L_Boss_side", mImage, Vector2{ 22,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1,1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_Down", mImage, Vector2{ 624,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol", mImage, Vector2{ 1004,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->CreateAnimation(L"L_Boss_side_dianogol", mImage, Vector2{22,13}, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_down", mImage, Vector2{ 254,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_down_dianogol", mImage, Vector2{ 624,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_side", mImage, Vector2{ 1004,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_down", mImage, Vector2{ 22,13 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		
		//���� Ÿ��		
		mAnimator->CreateAnimation(L"L_Boss_down_hurt", mImage, Vector2{ 624,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_hurt", mImage, Vector2{ 981,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_hurt", mImage, Vector2{ 1337,396 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);

		//���� ����	
		mAnimator->CreateAnimation(L"L_Boss_down_Attack", mImage, Vector2{ 625,835 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_Attack1", mImage, Vector2{ 625,930 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_dianogol_Attack2", mImage, Vector2{ 1205,930 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_Attack1", mImage, Vector2{ 625,1023 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_side_Attack2", mImage, Vector2{ 1205,1023 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);


		
		////////������ �ִϸ��̼�//////////
		//������ ���º�ȯ
		mAnimator->CreateAnimation(L"R_Boss_side", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol", mImage, Vector2{ 1004,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_Down", mImage, Vector2{ 624,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_Boss_side_dianogol", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_down", mImage, Vector2{ 254,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_down_dianogol", mImage, Vector2{ 624,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_side", mImage, Vector2{ 1004,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"R_Boss_side_down", mImage, Vector2{ 22,113 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.5f);

		//������ Ÿ��			
		mAnimator->CreateAnimation(L"R_Boss_down_hurt", mImage, Vector2{ 624,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_hurt", mImage, Vector2{ 981,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_hurt", mImage, Vector2{ 1337,288 }, Vector2{ 120,88 }, Vector2{ 8,0 }, 3, 1, 3, Vector2::Zero, 0.1f);

		//������ ����	
		mAnimator->CreateAnimation(L"R_Boss_down_Attack", mImage, Vector2{ 625,529 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_Attack1", mImage, Vector2{ 625,624 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_dianogol_Attack2", mImage, Vector2{ 1205,624 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_Attack1", mImage, Vector2{ 625,717 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_side_Attack2", mImage, Vector2{ 1205,717 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 5, 1, 5, Vector2::Zero, 0.1f);
				
		//������ ��ü ����
		mAnimator->CreateAnimation(L"Body_pice", mImage, Vector2{ 388,323 }, Vector2{ 104,80 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"L_Boss_side", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(261.0f, 250.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.05f) * size.x, (-0.3f) * size.y });
	}

	Act1_Boss::~Act1_Boss()
	{
	}

	void Act1_Boss::Initialize()
	{		
		Gameobject::Initialize();
	}

	void Act1_Boss::Update()
	{			
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::Act1_Boss::eBossState::Idle:idle();
			break;

		case jk::Act1_Boss::eBossState::Move:move();
			break;

		case jk::Act1_Boss::eBossState::Right:right();
			break;

		case jk::Act1_Boss::eBossState::Left:left();
			break;

		case jk::Act1_Boss::eBossState::Up:up();
			break;

		case jk::Act1_Boss::eBossState::Down:down();
			break;

		case jk::Act1_Boss::eBossState::Side_Dianogol:side_dianogol();
			break;

		case jk::Act1_Boss::eBossState::Dianogol_Down:dianogol_down();
			break;

		case jk::Act1_Boss::eBossState::Down_Dianogol:down_dianogol();
			break;

		case jk::Act1_Boss::eBossState::Dianogol_Side:dianogol_side();
			break;

		case jk::Act1_Boss::eBossState::Side_Down:side_down();
			break;

		case jk::Act1_Boss::eBossState::Attack_Side_Waiting:attack_side_waiting();
			break; 

		case jk::Act1_Boss::eBossState::Attack_Dianogol_Waiting:attack_dianogol_waition();
			break;	

		case jk::Act1_Boss::eBossState::Attack_Down_Waiting:attack_down_waition();
			break;	

		case jk::Act1_Boss::eBossState::Death:death();
			break;

		case jk::Act1_Boss::eBossState::Death_throw:death_throw();
			break;

		default:
			break;
		}					
		Gameobject::Update();
	}

	void Act1_Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Act1_Boss::Release()
	{
		Gameobject::Release();
	}

	void Act1_Boss::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();
				
			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{

				Damege_sheck += 1;
				Boss_Hit->Play(false);

				if ((Damege_sheck >= 7) && (mDir == -1))//���� 6�븦 �⺻���� ��
				{
					mAnimator->Play(L"L_Boss_side", true);
					mState = eBossState::Death;
					Death_check = 1;
				}
				else if ((Damege_sheck >= 7) && (mDir == 1))//������
				{
					mAnimator->Play(L"R_Boss_side", true);
					mState = eBossState::Death;		
					Death_check = 1;
				}


				switch (mState)
				{
				case jk::Act1_Boss::eBossState::Down_Dianogol:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 1;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					} 
					if (mDir == 1)
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 1;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}						
					break;
				}
				case jk::Act1_Boss::eBossState::Attack_Dianogol_Waiting:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 2;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 2;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					break;
				}
				case jk::Act1_Boss::eBossState::Side_Dianogol:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 3;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 3;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					break;
				}
				case jk::Act1_Boss::eBossState::Left:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 4;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 4;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					break;
				}
				case jk::Act1_Boss::eBossState::Right:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 5;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 5;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					break;
				}

				case jk::Act1_Boss::eBossState::Down:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 6;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 6;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_dianogol, this);
					}
					break;
				}

				case jk::Act1_Boss::eBossState::Dianogol_Side:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_dianogol_hurt", false);
						hurt_state = 7;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_dianogol_hurt", false);
						hurt_state = 7;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					break;
				}

				case jk::Act1_Boss::eBossState::Side_Down:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_side_hurt", false);
						hurt_state = 8;
						mAnimator->GetCompleteEvent(L"L_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_side_hurt", false);
						hurt_state = 8;
						mAnimator->GetCompleteEvent(L"R_Boss_dianogol_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					break;
				}

				case jk::Act1_Boss::eBossState::Attack_Side_Waiting:
				{
					if (mDir == -1)
					{
						mAnimator->Play(L"L_Boss_side_hurt", false);
						hurt_state = 9;
						mAnimator->GetCompleteEvent(L"L_Boss_side_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					else
					{
						mAnimator->Play(L"R_Boss_side_hurt", false);
						hurt_state = 9;
						mAnimator->GetCompleteEvent(L"R_Boss_side_hurt") = std::bind(&Act1_Boss::hurt_side, this);
					}
					break;
				}

				default:
					break;
				}		
			}
		}
	}

	void Act1_Boss::OnCollisionStay(Collider* other)
	{
	}

	void Act1_Boss::OnCollisionExit(Collider* other)
	{
	}


	void Act1_Boss::idle()
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

	void Act1_Boss::move()
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


	void Act1_Boss::right()
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

	void Act1_Boss::left()
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

	void Act1_Boss::up()
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

	void Act1_Boss::down()
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

	void Act1_Boss::side_dianogol()
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

	void Act1_Boss::dianogol_side()
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

	void Act1_Boss::dianogol_down()
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

	void Act1_Boss::down_dianogol()
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

	void Act1_Boss::side_down()
	{	
		if (mDir == -1)
		{
			mState = eBossState::Attack_Down_Waiting;			
			mAnimator->Play(L"L_Boss_down_Attack", false);
		}
	}

	void Act1_Boss::attack_side()
	{
		if (mDir == -1)
		{
			if (attack_check == 0)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_L_Side* bullet = new Bullet_Act1_L_Side(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 200, tr->GetPos().y + 50 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 1;
			}
			else if (attack_check == 2)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_L_Side* bullet = new Bullet_Act1_L_Side(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 90, tr->GetPos().y + 50 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 3;
			}
		
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Side_Waiting;
					mAnimator->Play(L"L_Boss_side_Attack2", false);
					time = 0;
					attack_motion = 1;
					attack_check = 2;
				}
				else
				{
					mState = eBossState::Up;
					mAnimator->Play(L"L_Boss_side", false);
					time = 0;
					Dir_change = 1;	
					attack_motion = 0;
					attack_check = 0;
				}
			}
		}
		else if (mDir == 1)
		{
			if (attack_check == 0)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_R_Side* bullet = new Bullet_Act1_R_Side(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x - 100, tr->GetPos().y + 50 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 1;
			}
			else if (attack_check == 2)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_R_Side* bullet = new Bullet_Act1_R_Side(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 30, tr->GetPos().y + 50 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 3;
			}
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Side_Waiting;
					mAnimator->Play(L"R_Boss_side_Attack2", false);
					time = 0;
					attack_motion = 1;
					attack_check = 2;
				}
				else
				{						
					mState = eBossState::Up;
					mAnimator->Play(L"R_Boss_side", false);
					time = 0;	
					Dir_change = 1;
					attack_motion = 0;
					attack_check = 0;
				}
			}
		}
	}

	void Act1_Boss::attack_side_waiting()
	{
 		mAnimator->GetCompleteEvent(L"L_Boss_side_Attack1") = std::bind(&Act1_Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"L_Boss_side_Attack2") = std::bind(&Act1_Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"R_Boss_side_Attack1") = std::bind(&Act1_Boss::attack_side, this);
		mAnimator->GetCompleteEvent(L"R_Boss_side_Attack2") = std::bind(&Act1_Boss::attack_side, this);
	}

	void Act1_Boss::attack_dianogol()
	{
		if(mDir == -1)
		{
			if (attack_check == 0)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_L_DIA* bullet = new Bullet_Act1_L_DIA(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 200, tr->GetPos().y + 90 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 1;
			}
			else if (attack_check == 2)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_L_DIA* bullet = new Bullet_Act1_L_DIA(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 90, tr->GetPos().y + 90 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 3;
			}
			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Dianogol_Waiting;
					mAnimator->Play(L"L_Boss_dianogol_Attack2", false);
					time = 0;
					attack_motion = -1;		
					attack_check = 2;
				}
				else
				{
					//�̻���2 �ֱ� location change
					if (Dir_change == 1)
					{
						mState = eBossState::Right;
						mAnimator->Play(L"L_Boss_dianogol", false);
						time = 0;
						Dir_change = -1;	
						attack_check = 0;
					}
					else if (Dir_change == -1)
					{
						mState = eBossState::Down;
						mAnimator->Play(L"L_Boss_dianogol", false);
						time = 0;
						attack_motion = 0;
						attack_check = 0;
					}						
				}
			}	
		}
		else if(mDir == 1)
		{
			if (attack_check == 0)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_R_DIA* bullet = new Bullet_Act1_R_DIA(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x -80, tr->GetPos().y + 90 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 1;
			}
			if (attack_check == 2)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				Bullet_Act1_R_DIA* bullet = new Bullet_Act1_R_DIA(this);
				bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x +70, tr->GetPos().y + 90 });
				curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
				attack_check = 3;
			}

			time += Time::DeltaTime();
			if (time >= 2)
			{
				if (attack_motion == 0)
				{
					mState = eBossState::Attack_Dianogol_Waiting;
					mAnimator->Play(L"R_Boss_dianogol_Attack2", false);
					time = 0;
					attack_motion = 1;	
					attack_check = 2;
				}
				else
				{
					//�̻���2 �ֱ� location change
					if (Dir_change == 1)
					{
						mState = eBossState::Left;
						mAnimator->Play(L"R_Boss_dianogol", false);
						time = 0;
						Dir_change = -1;
						attack_check = 0;
					}
					else if (Dir_change == -1)
					{
						mState = eBossState::Down;
						mAnimator->Play(L"R_Boss_dianogol", false);
						time = 0;	
						attack_motion = 0;
						attack_check = 0;
					}					
				}
			}
		}
	}

	void Act1_Boss::attack_dianogol_waition()
	{		
		mAnimator->GetCompleteEvent(L"L_Boss_dianogol_Attack1") = std::bind(&Act1_Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"L_Boss_dianogol_Attack2") = std::bind(&Act1_Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"R_Boss_dianogol_Attack1") = std::bind(&Act1_Boss::attack_dianogol, this);
		mAnimator->GetCompleteEvent(L"R_Boss_dianogol_Attack2") = std::bind(&Act1_Boss::attack_dianogol, this);
	}

	void Act1_Boss::attack_down()
	{
		if (mDir == -1)
		{
			//�̻��� �ֱ�
			if(attack_check == 0)
			{
				Transform* tr = GetComponent<Transform>();
				Scene* curScene = SceneManager::GetActiveScene();
				BaseBullet* bullet[2];
				bullet[0] = new BaseBullet(this);
				bullet[0]->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 60, tr->GetPos().y + 110 });
				curScene->AddGameobeject(bullet[0], jk_LayerType::Bullet);

				bullet[1] = new BaseBullet(this);
				bullet[1]->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x + 200, tr->GetPos().y + 110 });
				curScene->AddGameobeject(bullet[1], jk_LayerType::Bullet);
				attack_check = 1;
			}			
			time += Time::DeltaTime();
			if (time >= 2)
			{
				mState = eBossState::Move;
				mAnimator->Play(L"L_Boss_Down", false);
				time = 0;
				attack_check = 0;
			}
		}
		else if (mDir == 1)
		{
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

	void Act1_Boss::attack_down_waition()
	{
		mAnimator->GetCompleteEvent(L"L_Boss_down_Attack") = std::bind(&Act1_Boss::attack_down, this);
		mAnimator->GetCompleteEvent(L"R_Boss_down_Attack") = std::bind(&Act1_Boss::attack_down, this);
	}

	void Act1_Boss::hurt_down()
	{
		if (hurt_state == 1)
		{
		}
		else if (hurt_state == 2)
		{
		}
		else if (hurt_state == 3)
		{
		}
	}

	void Act1_Boss::hurt_side()
	{
		if (hurt_state == 7)
		{
			mState = eBossState::Dianogol_Side;
			if (mDir == -1)
			{				
				mAnimator->Play(L"L_Boss_dianogol_side", false);
			}
			else if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_dianogol_side", false);
			}
		}
		else if (hurt_state == 8)
		{
			mState = eBossState::Side_Down;
			if (mDir == -1)
			{				
				mAnimator->Play(L"L_Boss_side_down", false);
			}
			else if (mDir == 1)
			{				
				mAnimator->Play(L"R_Boss_side_down", false);
			}
		}
		else if (hurt_state == 9)
		{
			mState = eBossState::Attack_Side_Waiting;
			if (mDir == -1)
			{				
				mAnimator->Play(L"L_Boss_side_Attack1", false);
			}
			else if (mDir == 1)
			{				
				mAnimator->Play(L"R_Boss_side_Attack1", false);
			}
		}
		hurt_state = 0;
	}

	void Act1_Boss::hurt_dianogol()
	{
		if (hurt_state == 1)
		{
			if (mDir == -1)
			{
				mState = eBossState::Down_Dianogol;
				mAnimator->Play(L"L_Boss_down_dianogol", false);
			}
			else if (mDir == 1)
			{
				mState = eBossState::Down_Dianogol;
				mAnimator->Play(L"R_Boss_down_dianogol", false);
			}			
		}
		else if (hurt_state == 2)
		{
			if (mDir == -1)
			{
				mState = eBossState::Attack_Dianogol_Waiting;
				mAnimator->Play(L"L_Boss_dianogol_Attack1", false);
			}
			else if (mDir == 1)
			{
				mState = eBossState::Attack_Dianogol_Waiting;
				mAnimator->Play(L"R_Boss_dianogol_Attack1", false);
			}
			
		}
		else if (hurt_state == 3)
		{
			if (mDir == -1)
			{
				mState = eBossState::Side_Dianogol;
				mAnimator->Play(L"L_Boss_side_dianogol", false);
			}
			else if (mDir == 1)
			{
				mState = eBossState::Side_Dianogol;
				mAnimator->Play(L"R_Boss_side_dianogol", false);
			}		
		}
		else if (hurt_state == 4)
		{		
			mState = eBossState::Left;
			mAnimator->Play(L"R_Boss_dianogol", false);			
		}

		else if (hurt_state == 5)
		{	
			mState = eBossState::Right;
			mAnimator->Play(L"L_Boss_dianogol", false);			
		}

		else if (hurt_state == 6)
		{
			mState = eBossState::Down;
			if (mDir == -1)
			{
				mAnimator->Play(L"L_Boss_dianogol", false);
			}
			if (mDir == 1)
			{
				mAnimator->Play(L"R_Boss_dianogol", false);
			}
		}
		hurt_state = 0;
	}

	void Act1_Boss::death()
	{	
		Boss_Bomb->Play(false);
		Boss_Start->Stop(true);
		Act2_music->Play(true);

		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector2(0.0f, 0.0f));


		if (Death_check == 1)
		{
			Transform* tr = GetComponent<Transform>();
			Scene* curScene = SceneManager::GetActiveScene();
			Boss_act1_boomb* boss_boomb = new Boss_act1_boomb(this);
			boss_boomb->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x , tr->GetPos().y });
			curScene->AddGameobeject(boss_boomb, jk_LayerType::Effect);
			time += Time::DeltaTime();
			Death_check = 2;
		}


		time += Time::DeltaTime();
		if ((Death_check ==2)&&(time >= 3))
		{
			Transform* tr = GetComponent<Transform>();
			Scene* curScene = SceneManager::GetActiveScene();
			boss_run = new Boss_Run(this);
			boss_run->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x , tr->GetPos().y });
			curScene->AddGameobeject(boss_run, jk_LayerType::BOSS);
			time = 0;
			//object::Destory(this);

			mState = eBossState::Death_throw;
			mAnimator->Play(L"Body_pice",false);
		}
	}

	void Act1_Boss::death_throw()
	{
		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.f);
		mRigidbody->SetVelocity(Vector2{ 0.f,500.f });


		if (Death_check == 2)
		{
			if (Death_check != 2)
				return;

			Vector2 boss_pos = boss_run->GetComponent<Transform>()->GetPos();

			if (boss_pos.x > 21845)
			{
				Death_check = 3;
			}
		}


	}
}	
