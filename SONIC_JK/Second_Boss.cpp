#include "Second_Boss.h"
#include "Second_boss_bullet.h"
#include "Boss_act1_boomb.h"
#include "Boss_Run.h"
#include "Third_Boss.h"
#include "Boss_Arm.h"



#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "Rigidbody.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Ground.h"


namespace jk
{
	Second_Boss::Second_Boss()
		: mCenterpos(14350.f, 6670.f)
		, pos(0.f,0.f)
		, mSpeed(250)
		, mDir(1)
		, Up_Down(-1)
		, Boss_change_point(3)
		, time(0)
		, Boomb_point(0)
		, secondtime(0)

	{
		mImage = Resources::Load<Image>(L"Second_boss_R", L"..\\Resources\\ActBG_6\\BOSS\\Second_boss_R.bmp");
		mImage1 = Resources::Load<Image>(L"Second_boss_L", L"..\\Resources\\ActBG_6\\BOSS\\Second_boss_L.bmp");


		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"L_Boss_3th", mImage, Vector2{ 580,3 }, Vector2{ 100,208 }, Vector2{ 4.f,0.f }, 9, 1, 9, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"L_Boss3_Hurt", mImage, Vector2{ 1480,3 }, Vector2{ 100,208 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_2th", mImage, Vector2{ 580,218 }, Vector2{ 100,168 }, Vector2{ 4.f,0.f }, 9, 1, 9, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"L_Boss_2th_Hurt", mImage, Vector2{ 1480,218 }, Vector2{ 100,168 }, Vector2{ 4.f,0.f },  3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_1th", mImage, Vector2{ 580,396 }, Vector2{ 84,128 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_1th_Hurt", mImage, Vector2{ 832,396 }, Vector2{ 84,128 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"L_Boss_Death", mImage, Vector2{ 832,396 }, Vector2{ 80,56 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);


		mAnimator->CreateAnimation(L"R_Boss_3th", mImage1, Vector2{ 580,3 }, Vector2{ 100,208 }, Vector2{ 4.f,0.f }, 9, 1, 9, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"R_Boss3_Hurt", mImage1, Vector2{ 1480,3 }, Vector2{ 100,208 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_2th", mImage1, Vector2{ 580,218 }, Vector2{ 100,168 }, Vector2{ 4.f,0.f }, 9, 1, 9, Vector2::Zero, 0.2f);
		mAnimator->CreateAnimation(L"R_Boss_2th_Hurt", mImage1, Vector2{ 1480,218 }, Vector2{ 100,168 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_1th", mImage1, Vector2{ 580,396 }, Vector2{ 84,128 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_1th_Hurt", mImage1, Vector2{ 832,396 }, Vector2{ 84,128 }, Vector2{ 4.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"R_Boss_Death", mImage1, Vector2{ 832,396 }, Vector2{ 80,56 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);


		mAnimator->Play(L"R_Boss_3th", true);


		mAnimator->GetCompleteEvent(L"R_Boss_3th") = std::bind(&Second_Boss::R_Attack, this);
		mAnimator->GetCompleteEvent(L"L_Boss_3th") = std::bind(&Second_Boss::L_Attack, this);


		mAnimator->GetCompleteEvent(L"R_Boss_2th") = std::bind(&Second_Boss::R_Attack, this);
		mAnimator->GetCompleteEvent(L"L_Boss_2th") = std::bind(&Second_Boss::L_Attack, this);


		mAnimator->GetCompleteEvent(L"R_Boss3_Hurt") = std::bind(&Second_Boss::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss3_Hurt") = std::bind(&Second_Boss::Hurt, this);

		mAnimator->GetCompleteEvent(L"R_Boss_2th_Hurt") = std::bind(&Second_Boss::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss_2th_Hurt") = std::bind(&Second_Boss::Hurt, this);

		mAnimator->GetCompleteEvent(L"R_Boss_1th_Hurt") = std::bind(&Second_Boss::Hurt, this);
		mAnimator->GetCompleteEvent(L"L_Boss_1th_Hurt") = std::bind(&Second_Boss::Hurt, this);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(245.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.5f) * size.y });

		Boomb_point = 0;
	}

	Second_Boss::~Second_Boss()
	{

	}


	void Second_Boss::Initialize()
	{
		Gameobject::Initialize();
	}
	void Second_Boss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		if (Boomb_point == 2)
		{
			secondtime += Time::DeltaTime();
			if (secondtime > 2)
			{
				Create_RunBoss();
				Boomb_point = 3;
				time = 0;
			}
		}
		if (Boomb_point == 3)
		{
			time += Time::DeltaTime();
			if (time > 5)
			{
				Create_Boss3();
				secondtime = 0;
				Boomb_point = 4;
				arm_lotaion = 1;
			}
		}
		if (arm_lotaion == 1)
		{
			boss_arm->Set_mDir(last_boss->Get_mDir());
			boss_arm->Set_Hurt(last_boss->Get_Hurt());
			last_boss->Set_Grap(boss_arm->Get_grap());
		}


		switch (mState)
		{
		case jk::Second_Boss::eBossState::R_up:R_up();
			break;

		case jk::Second_Boss::eBossState::R_down:R_down();
			break;

		case jk::Second_Boss::eBossState::L_up:L_up();
			break;

		case jk::Second_Boss::eBossState::L_down:L_down();
			break;

		//case jk::Second_Boss::eBossState::Attack_L:wating_L();
		//	break;

		//case jk::Second_Boss::eBossState::Attack_R:wating_R();
		//	break;

		case jk::Second_Boss::eBossState::Death:death();
			break;		

		default:
			break;
		}
		Gameobject::Update();
	}


	void Second_Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void Second_Boss::Release()
	{
		Gameobject::Release();
	}


	void Second_Boss::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				Damege_check += 1;

				//if (Damege_check < 3)
				//{		
				//	if (mDir == 1)
				//	{
				//		mAnimator->Play(L"R_Boss3_Hurt", true); 
				//	}
				//	else
				//	{
				//		mAnimator->Play(L"L_Boss3_Hurt", false);						
				//	}					
				//}

	
				//else if((Damege_check >= 3)&&(Damege_check < 6))
				//{

				//	if (mDir == 1)
				//	{
				//		mAnimator->Play(L"R_Boss_2th_Hurt", true);
				//		if (Damege_check == 3)
				//		{
				//			Boss_change_point = 2;
				//			//何加前冻绢飘府扁 棺 气惯
				//		}
				//	}
				//	else 
				//	{
				//		mAnimator->Play(L"L_Boss_2th_Hurt", true);
				//		if (Damege_check == 3)
				//		{
				//			Boss_change_point = 2;
				//			//何加前冻绢飘府扁 棺 气惯
				//		}
				//	}

				//}

				//else if ((Damege_check >= 6) && (Damege_check < 9))			
				//{
				//	if (mDir == 1)
				//	{
				//		mAnimator->Play(L"R_Boss_1th_Hurt", true);
				//		if (Damege_check == 6)
				//		{
				//			Boss_change_point = 1;
				//			//何加前冻绢飘府扁 棺 气惯
				//		}
				//	}
				//	else
				//	{
				//		mAnimator->Play(L"L_Boss_1th_Hurt", true);
				//		if (Damege_check == 6)
				//		{
				//			Boss_change_point = 1;
				//			//何加前冻绢飘府扁 棺 气惯
				//		}
				//	}
				//}

				/*else*/ if (Damege_check == 1)
				{
					mState = eBossState::Death;

					if (mDir == 1)
					{
						mAnimator->Play(L"R_Boss_Death", true);
						if (Damege_check == 3)
						{
							Boss_change_point = 0;
							//何加前冻绢飘府扁 棺 气惯
						}
					}
					else
					{
						mAnimator->Play(L"L_Boss_Death", true);
						if (Damege_check == 3)
						{
							Boss_change_point = 0;
							//何加前冻绢飘府扁 棺 气惯
						}
					}
				}
			}
		}

	}


	void Second_Boss::OnCollisionStay(Collider* other)
	{
	}


	void Second_Boss::OnCollisionExit(Collider* other)
	{
	}



	void Second_Boss::Create_RunBoss()
	{
		Scene* curScene = SceneManager::GetActiveScene();
		boss_run2 = new Boss_Run(this);		
		boss_run2->SetName(L"boss_run2");
		pos = Vector2{ 13850.f, 6000.f };
		boss_run2->GetComponent<Transform>()->SetPos(pos);
		boss_run2->Set_Dir(1);
		curScene->AddGameobeject(boss_run2, jk_LayerType::MiniBoss);
	}


	void Second_Boss::Create_Boss3()
	{
		Scene* curScene1 = SceneManager::GetActiveScene();
		last_boss = new Third_Boss();
		last_boss->SetName(L"last_boss");
		last_boss->GetComponent<Transform>()->SetPos(Vector2{ 13550.0f,5400.f });
		curScene1->AddGameobeject(last_boss, jk_LayerType::BOSS);


		Scene* curScene2 = SceneManager::GetActiveScene();
		boss_arm = new Boss_Arm(last_boss);
		boss_arm->SetName(L"boss_arm");
		boss_arm->GetComponent<Transform>()->SetPos(Vector2{ 13520.0f,5487.f });
		curScene2->AddGameobeject(boss_arm, jk_LayerType::BOSS);
	}


	void Second_Boss::R_up()
	{
		Transform* tr = GetComponent<Transform>();		
		pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y <= 4500.0f)
		{
			mState = eBossState::R_down;
			Up_Down = 1;
		}
		tr->SetPos(pos);
		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
	}


	void Second_Boss::R_down()
	{
		Transform* tr = GetComponent<Transform>();			
		pos.y += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y >=6000.0f)
		{
			mState = eBossState::L_up;		
			pos = Vector2{ 13850.f, 6000.f };
			tr->SetPos(pos);

			if (Damege_check < 3)
			{
				mAnimator->Play(L"L_Boss_3th", true);
			}
			else if (Damege_check >= 3 && Damege_check < 6)
			{
				mAnimator->Play(L"L_Boss_2th", true);
			}
			else if (Damege_check >= 6 )
			{
				mAnimator->Play(L"L_Boss_1th", true);
			}
			
			mDir = -1;
			Up_Down = -1;
		}
		tr->SetPos(pos);
		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
	}

	void Second_Boss::L_up()
	{
		Transform* tr = GetComponent<Transform>();
		pos.y -= mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y <= 4500.0f)
		{
			mState = eBossState::L_down;
			Up_Down = 1;
		}
		tr->SetPos(pos);
		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;
	}



	void Second_Boss::L_down()
	{

		Transform* tr = GetComponent<Transform>();		
		
		pos.y += mSpeed * static_cast<float>(Time::DeltaTime());

		if (pos.y >= 6000.0f)
		{
			mState = eBossState::R_up;
			pos = Vector2{ 14750.f, 6000.f };
			tr->SetPos(pos);

			if (Damege_check < 3)
			{
				mAnimator->Play(L"R_Boss_3th", true);
			}
			else if (Damege_check >= 3 && Damege_check < 6)
			{
				mAnimator->Play(L"R_Boss_2th", true);
			}
			else if (Damege_check >= 6)
			{
				mAnimator->Play(L"R_Boss_1th", true);
			}

			Up_Down = -1;
			mDir = 1;
		}
		tr->SetPos(pos);
		//fDist = mCenterpos.y - pos.y - mMonmaxdistance;		
	}


	void Second_Boss::wating_L()
	{

	}


	void Second_Boss::wating_R()
	{

	}


	void Second_Boss::death()
	{
		if(Boomb_point==0)
		{
		Scene* curScene = SceneManager::GetActiveScene();
		Boss_act1_boomb* Boss2_boomb = new Boss_act1_boomb(this);		
		Boss2_boomb->SetName(L"Boss2_boomb");
		Boss2_boomb->GetComponent<Transform>()->SetPos(pos);
		curScene->AddGameobeject(Boss2_boomb, jk_LayerType::Effect);
	 	Boomb_point =  1;		
		}
		else if(Boomb_point == 1 )
	 	 {
			time += Time::DeltaTime();
			if (time >= 2)
			{
				mRigidbody = AddComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Boomb_point = 2;				
			}
		}
	}


	void Second_Boss::Hurt()
	{
		if (mDir == 1)
		{
			if (Up_Down == -1)
			{
				if (Boss_change_point == 3)
				{
					mAnimator->Play(L"R_Boss_3th", true);
					mState = eBossState::R_up;
				}
				else if(Boss_change_point == 2)
				{
					mAnimator->Play(L"R_Boss_2th", true);
					mState = eBossState::R_up;
				}
				else if(Boss_change_point == 1)
				{
					mAnimator->Play(L"R_Boss_1th", true);
					mState = eBossState::R_up;
				}

			}
			else
			{
				if (Boss_change_point == 3)
				{
					mAnimator->Play(L"R_Boss_3th", true);
					mState = eBossState::R_down;
				}
				else if (Boss_change_point == 2)
				{
					mAnimator->Play(L"R_Boss_2th", true);
					mState = eBossState::R_down;
				}
				else if (Boss_change_point == 1)
				{
					mAnimator->Play(L"R_Boss_1th", true);
					mState = eBossState::R_down;
				}
			}

		}
		else
		{
			if (Up_Down == -1)
			{
				if (Boss_change_point == 3)
				{
					mAnimator->Play(L"L_Boss_3th", true);
					mState = eBossState::L_up;
				}
				else if (Boss_change_point == 2)
				{
					mAnimator->Play(L"L_Boss_2th", true);
					mState = eBossState::L_up;
				}
				else if (Boss_change_point == 1)
				{
					mAnimator->Play(L"L_Boss_1th", true);
					mState = eBossState::L_up;
				}

			}
			else
			{
				if (Boss_change_point == 3)
				{
					mAnimator->Play(L"L_Boss_3th", true);
					mState = eBossState::L_down;
				}
				else if (Boss_change_point == 2)
				{
					mAnimator->Play(L"L_Boss_2th", true);
					mState = eBossState::L_down;
				}
				else if (Boss_change_point == 1)
				{
					mAnimator->Play(L"L_Boss_1th", true);
					mState = eBossState::L_down;
				}
			}
		}
	}


	void Second_Boss::L_Attack()
	{
		if (Boss_change_point == 3)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2 = new Second_boss_bullet();
			bullet2->SetName(L"bullet_boss2");
			bullet2->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 50.f, pos.y + 45.f });
			curScene->AddGameobeject(bullet2, jk_LayerType::Bullet);
			bullet2->Set_mDir(1);

			Scene* curScene1 = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2_1 = new Second_boss_bullet();
			bullet2_1->SetName(L"bullet_boss2");
			bullet2_1->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 50.f, pos.y + 85.f });
			curScene1->AddGameobeject(bullet2_1, jk_LayerType::Bullet);
			bullet2_1->Set_mDir(1);
		}


		if (Boss_change_point == 2)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2 = new Second_boss_bullet();
			bullet2->SetName(L"bullet_boss2");
			bullet2->GetComponent<Transform>()->SetPos(Vector2{ pos.x +50, pos.y + 45.f });
			curScene->AddGameobeject(bullet2, jk_LayerType::Bullet);
			bullet2->Set_mDir(1);
		}
	}


	void Second_Boss::R_Attack()
	{
		if (Boss_change_point == 3)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2 = new Second_boss_bullet();
			bullet2->SetName(L"bullet_boss2");
			bullet2->GetComponent<Transform>()->SetPos(Vector2{ pos.x,pos.y + 45.f });
			curScene->AddGameobeject(bullet2, jk_LayerType::Bullet);
			bullet2->Set_mDir(-1);

			Scene* curScene1 = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2_1 = new Second_boss_bullet();
			bullet2_1->SetName(L"bullet_boss2");
			bullet2_1->GetComponent<Transform>()->SetPos(Vector2{ pos.x , pos.y + 85.f });
			curScene1->AddGameobeject(bullet2_1, jk_LayerType::Bullet);
			bullet2_1->Set_mDir(-1);
		}


		if (Boss_change_point == 2)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Second_boss_bullet* bullet2 = new Second_boss_bullet();
			bullet2->SetName(L"bullet_boss2");
			bullet2->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y + 45.f });
			curScene->AddGameobeject(bullet2, jk_LayerType::Bullet);
			bullet2->Set_mDir(-1);
		}
	}
}






