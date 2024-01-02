#include "jk_PlayScene4.h"
#include "jk_PlayScene3.h"
#include "jk_PlayScene2.h"
#include "jk_PlayScene.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_Camera.h"
#include "jk_CollisionManager.h"
#include "jk_Gameobject.h"
#include "jk_Object.h"
#include "jk_Transform.h"
#include "jk_Blending.h"
#include "Rigidbody.h"
#include "jk_Resources.h"
#include "jk_Sound.h"
#include "jk_Image.h"
#include "jk_Sonic.h"
#include "Electsonic.h"
#include "jk_Tails.h"

#include "UI_framework.h"
#include "UI_Time.h"
#include "UI_Time_seconds.h"
#include "UI_Time_minutes.h"
#include "Ring_Point_Manager.h"
#include "Ring_UnitsDigit.h"
#include "Ring_TensDigit.h"
#include "Ring_HundredsDgit.h"
#include "Life_Manager.h"
#include "Life_UnitsDigit.h"
#include "Life_TensDigit.h"


#include "jk_Pixel_Ground.h"
#include "jk_Act6_BG.h"
#include "act6_sky1.h"
#include "Deatht_line_act6.h"

#include "Robotnic_machine.h"
#include "First_Boss.h"
#include "boss_come.h"
#include "boss1_object.h"
#include "finall_stage.h"
#include "Third_Boss.h"
#include "Boss_Arm.h"
#include "Last_Boss_bomb.h"
#include "Boss_trash.h"


#include "Second_Boss.h"
#include "Third_Boss.h"
#include "Boss_Arm.h"
#include "Ending_boss.h"


#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Item_Elect.h"
#include "jk_StageSave.h"




namespace jk
{
	PlayScene4::PlayScene4()
		: playgr(nullptr)
		, mSonic(nullptr)
		, mTails(nullptr)
		, mFirst_Boss(nullptr)
		, mRobotnic_machine(nullptr)
		, mSecond_Boss(nullptr)
		, mFinall_stage(nullptr)
		, mBoss_Arm(nullptr)
		, mThird_Boss(nullptr)
		, mAct6_sky1(nullptr)
		, mBoss_trash(nullptr)
		, mEnding_boss(nullptr)
		, mDeatht_line_act6(nullptr)


		, mBoss_start(nullptr)
		, mAct6_music(nullptr)
		, mRocket_Start(nullptr)
		, mLast_Boss_f(nullptr)
		, mStage_bomb(nullptr)
		, mEnding(nullptr)


		, mCamera_Switch(0)
		, mCheck_boss(0)
		, mFrame_check(0)
		, mBoss_Death_point(0)
		, mMap_lotation(0)
		, mBOSS2_Start(0)
		, mBOSS3_Start(0)
		, mBoss_end(0)
		, mArm_lotaion(0)
		, mDir(0)
		, mCheck_map(0)
		, mTime(0.f)
	{
	}
	PlayScene4::~PlayScene4()
	{
	}
	void PlayScene4::Initialize()
	{
		mCheck_map = 3;

		mAct6_music = Resources::Load<Sound>(L"Act6_bg", L"..\\Resources\\Sound\\Act6_bg.wav");
		mBoss_start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		mRocket_Start = Resources::Load<Sound>(L"Rocket_Start", L"..\\Resources\\Sound\\Rocket_Start.wav");
		mLast_Boss_f = Resources::Load<Sound>(L"Last_Boss_f", L"..\\Resources\\Sound\\Last_Boss_f.wav");
		mStage_bomb = Resources::Load<Sound>(L"Stage_bomb", L"..\\Resources\\Sound\\Stage_bomb.wav");



		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);

		Sonic::eSonicState::Jeep_line;
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		//mSonic_Pos->GetComponent<Transform>()->SetPos(Vector2{ 6000.f, 5085.f });
		//mSonic_Pos->GetComponent<Transform>()->SetPos(Vector2{ 14350.f, 5550.f });
		mSonic->Set_Fly(1);

		mTails = new Tails(mSonic);
		mTails->SetName(L"Player2");
		AddGameobeject(mTails, jk_LayerType::Player2);
		Tails::eTailsState::Fly_Waiting;
		mTails->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		mTails->Set_Fly(1);


		playgr = new Pixel_Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, mTails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		mTails->SetCheckTargetGround(playgr);



		UI_framework* UI_frame = new UI_framework();
		UI_frame->SetName(L"UI_frame");
		AddGameobeject(UI_frame, jk_LayerType::UI);

		UI_Time* ui_time = new UI_Time();
		ui_time->SetName(L"ui_time");
		AddGameobeject(ui_time, jk_LayerType::UI);

		UI_Time_seconds* ui_seconds = new UI_Time_seconds(ui_time);
		ui_seconds->SetName(L"ui_seconds");
		AddGameobeject(ui_seconds, jk_LayerType::UI);

		UI_Time_minutes* ui_minutes = new UI_Time_minutes(ui_time);
		ui_minutes->SetName(L"ui_seconds");
		AddGameobeject(ui_minutes, jk_LayerType::UI);

		Ring_Point_Manager* Ring_Point = new Ring_Point_Manager(mSonic);
		Ring_Point->SetName(L"Ring_Point");
		AddGameobeject(Ring_Point, jk_LayerType::UI);

		Ring_UnitsDigit* Ring_Units = new Ring_UnitsDigit(Ring_Point);
		Ring_Units->SetName(L"Ring_Point");
		AddGameobeject(Ring_Units, jk_LayerType::UI);

		Ring_TensDigit* TensDigit = new Ring_TensDigit(Ring_Point);
		TensDigit->SetName(L"TensDigit");
		AddGameobeject(TensDigit, jk_LayerType::UI);

		Ring_HundredsDgit* HundredsDgit = new Ring_HundredsDgit(Ring_Point);
		HundredsDgit->SetName(L"HundredsDgit");
		AddGameobeject(HundredsDgit, jk_LayerType::UI);

		Life_Manager* Life_M = new Life_Manager(mSonic);
		Life_M->SetName(L"Life_M");
		AddGameobeject(Life_M, jk_LayerType::UI);

		Life_UnitsDigit* Life_u = new Life_UnitsDigit(Life_M);
		Life_u->SetName(L"Life_u");
		AddGameobeject(Life_u, jk_LayerType::UI);

		Life_TensDigit* Life_t = new Life_TensDigit(Life_M);
		Life_t->SetName(L"Life_t");
		AddGameobeject(Life_t, jk_LayerType::UI);

		mDeatht_line_act6 = new Deatht_line_act6();
		mDeatht_line_act6->SetName(L"death_line");
		AddGameobeject(mDeatht_line_act6, jk_LayerType::BOSS);
		mDeatht_line_act6->GetComponent<Transform>()->SetPos(Vector2{ 13500.f,  5900.f });


		mRobotnic_machine = new Robotnic_machine();
		mRobotnic_machine->SetName(L"boss_first");
		AddGameobeject(mRobotnic_machine, jk_LayerType::Player);
		mRobotnic_machine->GetComponent<Transform>()->SetPos(Vector2{ 6855.0f,5600.0f });


		//First mBoss
		mFirst_Boss = new First_Boss();
		mFirst_Boss->SetName(L"boss_first");
		AddGameobeject(mFirst_Boss, jk_LayerType::BOSS);
		mFirst_Boss->GetComponent<Transform>()->SetPos(Vector2{ 6185.0f,5215.0f });
		mFirst_Boss->SetCheckTargetGround(playgr);


		mFinall_stage = new finall_stage();
		mFinall_stage->SetName(L"stage");
		AddGameobeject(mFinall_stage, jk_LayerType::BG_props);
		mFinall_stage->GetComponent<Transform>()->SetPos(Vector2{ 10190.0f,5650.0f });


		//배경
		jk_Act6_BG* act6_BG = new jk_Act6_BG();
		act6_BG->SetName(L"act6_BG");
		AddGameobeject(act6_BG, jk_LayerType::BG);

		mAct6_sky1 = new act6_sky1();
		mAct6_sky1->SetName(L"act6_sky1");
		AddGameobeject(mAct6_sky1, jk_LayerType::foreground);
		mAct6_sky1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, -500.f });


		Scene::Initialize();

	}
	void PlayScene4::Update()
	{
		playgr->Set_map_check(mCheck_map);;


		mBoss_Death_point = mFirst_Boss->Get_BossDeath();


		if (mBoss_Death_point == 1)
		{
			mCamera_Switch = 0;
		}

		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();
		if ((mBoss_Death_point == 0) && (sonic_pos.x >= 6050.f)) //카메라 스위치 변경하면서 보스1 출현
		{
			mCamera_Switch = 1;
		}
		else if ((mBoss_Death_point == 1) && (sonic_pos.x >= 6150.f))
		{
			mCamera_Switch = 0;
			mFirst_Boss->Set__BossDeath(2);
			mAct6_music->Play(true);
		}

		if (mMap_lotation == 0)//LAST STAGE FIRE
		{
			if (sonic_pos.x >= 9500.f)
			{
				mMap_lotation = 1;
				mFinall_stage->Set_move_stage(mMap_lotation);
				Vector2 stagepos = mFinall_stage->GetComponent<Transform>()->GetPos();

			}
		}

		if (mCamera_Switch == 1)//보스1 출현
		{
			Camera::SetCamera(1);
			Camera::SetTarget(nullptr);
			if (mCheck_boss == 0)
			{
				if (mCheck_boss != 0)
					return;

				Create_Boss1();
				mCheck_boss = 1;
			}
		}

		if (mMap_lotation == 1)//SECOND BOSS START
		{
			if (sonic_pos.x >= 14350.f)
			{
				mCamera_Switch = 1;
				Create_Boss2();
				mMap_lotation = 2;
			}
		}

		else if (mCamera_Switch == 0)
		{
			Camera::SetTarget(mSonic);
			Camera::SetCamera(0);
		}
		//6840
		if ((mTails->GetComponent<Transform>()->GetPos().x > 6840) && (mTails->GetComponent<Transform>()->GetPos().x < 14100))
		{
			mTails->Set_Fly(3);
		}

		if (mTails->Get_Fly() == 3)
		{
			if (mTails->GetComponent<Transform>()->GetPos().x > 14100)
			{
				mTails->Set_Fly(4);
			}
		}
		if (mTails->Get_Fly() == 4)
		{
			Rigidbody* rb = mTails->GetComponent<Rigidbody>();
			rb->SetGround(true);
			if (rb->GetGround())
			{
				mTails->Set_Fly(5);
			}
		}

		if (mSonic->GetComponent<Transform>()->GetPos().x > 14000)
		{
			Vector2 Sky_Pos = mAct6_sky1->GetComponent<Transform>()->GetPos();

			Sky_Pos.x -= 50 * static_cast<float>(Time::DeltaTime());
			Sky_Pos.y += 20 * static_cast<float>(Time::DeltaTime());

			mAct6_sky1->GetComponent<Transform>()->SetPos(Sky_Pos);
		}

		if (mBOSS2_Start == 1)
		{
			mBOSS3_Start = mSecond_Boss->Get_last_BOSS();

			if (mBOSS3_Start == 3)
			{
				mTime += static_cast<float>(Time::DeltaTime());
				if (mTime > 5)
				{
					Create_Boss3();
					mBOSS3_Start = 4;
					mSecond_Boss->Set_last_BOSS(mBOSS3_Start);
					//mBoomb_point = 4;
					mArm_lotaion = 1;
				}
			}
		}
		if (mArm_lotaion == 1)
		{
			mBoss_Arm->Set_mDir(mThird_Boss->Get_mDir());
			mBoss_Arm->Set_Hurt(mThird_Boss->Get_Hurt());
			mThird_Boss->Set_Grap(mBoss_Arm->Get_grap());
		}
		if (mBOSS3_Start == 4)
		{

			if (mThird_Boss->GetEnding_point() == 1)
			{
				mTime = 0;
				Last_Stage_bomb(14300.f, 4900.f);
				Last_Stage_bomb(14100.f, 4900.f);
				Last_Stage_bomb(13900.f, 4900.f);
				Last_Stage_bomb(14500.f, 4900.f);
				Last_Stage_bomb(14700.f, 4900.f);
				Last_Stage_bomb(14300.f, 4900.f);
				Last_Stage_bomb(14100.f, 4900.f);
				Last_Stage_bomb(13900.f, 4900.f);
				Last_Stage_bomb(14500.f, 4900.f);
				Last_Stage_bomb(14700.f, 4900.f);
				Last_Stage_bomb(14300.f, 4900.f);
				Last_Stage_bomb(14100.f, 4900.f);
				Last_Stage_bomb(13900.f, 4900.f);
				Last_Stage_bomb(14500.f, 4900.f);
				Last_Stage_bomb(14700.f, 4900.f);

				mThird_Boss->SetEnding_point(2);
			}
			if (mThird_Boss->GetEnding_point() == 2)
			{
				int a = 1;
				mFinall_stage->Set_end_Stage(a);
				mThird_Boss->SetEnding_point(3);
			}
			if (mFinall_stage->Get_end_Stage() == 2)
			{
				mTime += static_cast<float>(Time::DeltaTime());
				if (mTime > 4)
				{
					ending_boss();
					boss_trash();
					int a = 3;
					mFinall_stage->Set_end_Stage(a);
				}
			}

			if (mBoss_end == 1)
			{
				if (mEnding_boss->GetComponent<Transform>()->GetPos().y > 5400)
				{
					mSonic->Set_Ending(1);
					mTails->Set_Ending(1);
					mBoss_end = 2;
				}
			}
		}


		if (Input::GetKeyDown(eKeyCode::M))
		{
			Vector2 stagepos = mFinall_stage->GetComponent<Transform>()->GetPos();
			mSonic->GetComponent<Transform>()->SetPos(Vector2(14150.f, stagepos.y-50.f));
			mSonic->GetComponent<Rigidbody>()->SetGravity(Vector2{ 0.f,1000.f });
			mSonic->GetComponent<Rigidbody>()->SetFiction(100.f);
			playgr->SetLotation(0);
			Sonic::eSonicState::Idle;
		}


		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::MiniGameplay);
			//CreateBlending();
			mCheck_map = 0;
		}

	}

	void PlayScene4::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene4::Release()
	{
		Scene::Release();
	}

	void PlayScene4::OnEnter()
	{

		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Player, true);//충돌시 가리키는 장면
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Bullet, true);
		CollisionManager::SetLayer(jk_LayerType::Player2, jk_LayerType::Monster, true);
		CollisionManager::SetLayer(jk_LayerType::Player2, jk_LayerType::Bullet, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Item, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Items, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Rings, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::StageSave, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Ground, true);
		CollisionManager::SetLayer(jk_LayerType::Player2, jk_LayerType::Ground, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::BG_props, true);
		CollisionManager::SetLayer(jk_LayerType::Player2, jk_LayerType::BG_props, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Player2, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::MiniBoss, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::BOSS, true);
		CollisionManager::SetLayer(jk_LayerType::MiniBoss, jk_LayerType::BOSS, true);



		Camera::SetTarget(mSonic);
	}

	void PlayScene4::OnExit()
	{
	}

	void PlayScene4::CreateBlending()
	{
		//object::Instantiate<EndingBlend>(jk_LayerType::Blend);
	}

	void PlayScene4::Create_Boss1()
	{
		mAct6_music->Stop(true);
		mBoss_start->Play(true);
		boss_come* boss_run = new boss_come(mSonic);
		boss_run->SetName(L"boss_run");
		AddGameobeject(boss_run, jk_LayerType::MiniBoss);
		boss_run->GetComponent<Transform>()->SetPos(Vector2{ 6607.f, 5265.f });
		boss_run->SetCheckTargetGround(playgr);
	}

	void PlayScene4::Create_Boss2()
	{
		mSecond_Boss = new Second_Boss();
		mSecond_Boss->SetName(L"boss_run");
		AddGameobeject(mSecond_Boss, jk_LayerType::BOSS);
		mSecond_Boss->GetComponent<Transform>()->SetPos(Vector2{ 14750.f, 6000.f });
		mBOSS2_Start = 1;
		//(14350.f, 6670.f)
	}

	void PlayScene4::Create_Boss3()
	{
		//mAct6_music->Stop(true);
		mLast_Boss_f->Play(true);

		Scene* curScene1 = SceneManager::GetActiveScene();
		mThird_Boss = new Third_Boss();
		mThird_Boss->SetName(L"last_boss");
		mThird_Boss->GetComponent<Transform>()->SetPos(Vector2{ 13550.0f,5400.f });
		curScene1->AddGameobeject(mThird_Boss, jk_LayerType::BOSS);

		Scene* curScene2 = SceneManager::GetActiveScene();
		mBoss_Arm = new Boss_Arm(mThird_Boss);
		mBoss_Arm->SetName(L"boss_arm");
		mBoss_Arm->GetComponent<Transform>()->SetPos(Vector2{ 13520.0f,5487.f });
		curScene2->AddGameobeject(mBoss_Arm, jk_LayerType::BOSS);
	}

	void PlayScene4::Last_Stage_bomb(float a, float b)
	{
		mStage_bomb->Play(false);
		Scene* curScene = SceneManager::GetActiveScene();
		Last_Boss_bomb* last_bomb = new Last_Boss_bomb(mFinall_stage);
		last_bomb->SetName(L"last_boss_bomb");
		last_bomb->GetComponent<Transform>()->SetPos(Vector2{ a,b });
		curScene->AddGameobeject(last_bomb, jk_LayerType::Effect);
	}

	void PlayScene4::ending_boss()
	{
		Scene* curScene2 = SceneManager::GetActiveScene();
		mEnding_boss = new Ending_boss(mThird_Boss);
		mEnding_boss->SetName(L"end_boss");
		mEnding_boss->GetComponent<Transform>()->SetPos(Vector2{ 14400,4750 });
		curScene2->AddGameobeject(mEnding_boss, jk_LayerType::BOSS);
		mBoss_end = 1;
	}

	void PlayScene4::boss_trash()
	{
		Scene* curScene2 = SceneManager::GetActiveScene();
		mBoss_trash = new Boss_trash(mEnding_boss);
		mBoss_trash->SetName(L"trash");
		mBoss_trash->GetComponent<Transform>()->SetPos(Vector2{ 14250,4650 });
		curScene2->AddGameobeject(mBoss_trash, jk_LayerType::BOSS);
	}
}
