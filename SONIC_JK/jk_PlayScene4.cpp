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


#include "jk_Ground.h"
#include "jk_Act6_BG.h"
#include "act6_sky1.h"
#include "Deatht_line_act6.h"

#include "Robotnic_machine.h"
#include "boss1_body.h"
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
		, mtails(nullptr)
		, boss_first(nullptr)
		, fly_machine(nullptr)
		, second_boss(nullptr)
		, stage_final(nullptr)
		, boss_arm(nullptr)
		, last_boss(nullptr)
		, sky1(nullptr)
		, trash(nullptr)
		, end_boss(nullptr)
		, death_line(nullptr)


		, Boss_start(nullptr)
		, Act6_music(nullptr)
		, Rocket_Start(nullptr)
		, Last_Boss_f(nullptr)
		, Stage_bomb(nullptr)
		, Ending(nullptr)


		, Camera_Switch(0)
		, check_boss(0)
		, frame_check(0)
		, Boss_Death_point(0)
		, map_lotation(0)
		, BOSS2_Start(0)
		, BOSS3_Start(0)
		, Boss_end(0)
		, arm_lotaion(0)
		, dir(0)
		, check_map(0)
		, time(0.f)
	{
	}
	PlayScene4::~PlayScene4()
	{
	}
	void PlayScene4::Initialize()
	{
		check_map = 3;

		Act6_music = Resources::Load<Sound>(L"Act6_bg", L"..\\Resources\\Sound\\Act6_bg.wav");
		Boss_start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		Rocket_Start = Resources::Load<Sound>(L"Rocket_Start", L"..\\Resources\\Sound\\Rocket_Start.wav");
		Last_Boss_f = Resources::Load<Sound>(L"Last_Boss_f", L"..\\Resources\\Sound\\Last_Boss_f.wav");
		Stage_bomb = Resources::Load<Sound>(L"Stage_bomb", L"..\\Resources\\Sound\\Stage_bomb.wav");



		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);

		Sonic::eSonicState::Jeep_line;
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 6000.f, 5085.f });
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 14350.f, 5550.f });
		mSonic->Set_Fly(1);

		mtails = new Tails(mSonic);
		mtails->SetName(L"Player2");
		AddGameobeject(mtails, jk_LayerType::Player2);
		Tails::eTailsState::Fly_Waiting;
		mtails->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		mtails->Set_Fly(1);


		playgr = new Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, mtails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		mtails->SetCheckTargetGround(playgr);
	


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

		death_line = new Deatht_line_act6();
		death_line->SetName(L"death_line");
		AddGameobeject(death_line, jk_LayerType::BOSS);
		death_line->GetComponent<Transform>()->SetPos(Vector2{ 13500.f,  5900.f });

		
		fly_machine = new Robotnic_machine();
		fly_machine->SetName(L"boss_first");
		AddGameobeject(fly_machine, jk_LayerType::Player);
		fly_machine->GetComponent<Transform>()->SetPos(Vector2{ 6855.0f,5600.0f });


		//First boss
		boss_first = new boss1_body();
		boss_first->SetName(L"boss_first");
		AddGameobeject(boss_first, jk_LayerType::BOSS);
		boss_first->GetComponent<Transform>()->SetPos(Vector2{ 6185.0f,5215.0f });
		boss_first->SetCheckTargetGround(playgr);


		stage_final = new finall_stage();
		stage_final->SetName(L"stage");
		AddGameobeject(stage_final, jk_LayerType::BG_props);
		stage_final->GetComponent<Transform>()->SetPos(Vector2{ 10190.0f,5650.0f });


	//배경
		jk_Act6_BG* act6_BG = new jk_Act6_BG();
		act6_BG->SetName(L"act6_BG");
		AddGameobeject(act6_BG, jk_LayerType::BG);

		sky1 = new act6_sky1();
		sky1->SetName(L"act6_sky1");
		AddGameobeject(sky1, jk_LayerType::foreground);
		sky1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, -500.f });


		Scene::Initialize();

	}
	void PlayScene4::Update()
	{
		playgr->Set_map_check(check_map);;

		
		Boss_Death_point = boss_first->Get_BossDeath();
		
		
		if (Boss_Death_point == 1)
		{
			Camera_Switch = 0;			
		}

		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();
		if ((Boss_Death_point == 0) && (sonic_pos.x >= 6050.f)) //카메라 스위치 변경하면서 보스1 출현
		{
			Camera_Switch = 1;
		}
		else if ((Boss_Death_point == 1) && (sonic_pos.x >= 6150.f))
		{
			Camera_Switch = 0;		
			boss_first->Set__BossDeath(2);
			Act6_music->Play(true);
		}

		if (map_lotation == 0)//LAST STAGE FIRE
		{
			if (sonic_pos.x >= 9500.f)
			{
				map_lotation = 1;
				stage_final->Set_move_stage(map_lotation);
				Vector2 stagepos = stage_final->GetComponent<Transform>()->GetPos();
				
			}
		}

		if (Camera_Switch == 1)//보스1 출현
		{
			Camera::SetCamera(1);
			Camera::SetTarget(nullptr);
			if (check_boss == 0)
			{
				if (check_boss != 0)
					return;
				
				Create_Boss1();
				check_boss = 1;
			}
		}

		if (map_lotation == 1)//SECOND BOSS START
		{
			if (sonic_pos.x >= 14350.f)
			{			
				Camera_Switch = 1;			
				Create_Boss2();
				map_lotation = 2;
			}
		}

		else if (Camera_Switch == 0)
		{
			Camera::SetTarget(mSonic);
			Camera::SetCamera(0);
		}
	//6840
		if ((mtails->GetComponent<Transform>()->GetPos().x > 6840)&& (mtails->GetComponent<Transform>()->GetPos().x < 14100))
		{
			mtails->Set_Fly(3);
		}
		
		if(mtails->Get_Fly()==3)
		{
			if (mtails->GetComponent<Transform>()->GetPos().x > 14100)
			{
				mtails->Set_Fly(4);
			}
		}
		if (mtails->Get_Fly() == 4)
		{
			Rigidbody* rb = mtails->GetComponent<Rigidbody>();
			rb->SetGround(true);
			if (rb->GetGround())
			{
				mtails->Set_Fly(5);
			}
		}

		if (mSonic->GetComponent<Transform>()->GetPos().x > 14000)
		{
			Vector2 Sky_Pos = sky1->GetComponent<Transform>()->GetPos();
		
				Sky_Pos.x -= 50 * static_cast<float>(Time::DeltaTime());
				Sky_Pos.y += 20 * static_cast<float>(Time::DeltaTime());

			sky1->GetComponent<Transform>()->SetPos(Sky_Pos);
		}

		if(BOSS2_Start ==1)
		{
			BOSS3_Start = second_boss->Get_last_BOSS();

			if (BOSS3_Start == 3)
			{
				time += static_cast<float>(Time::DeltaTime());
				if (time > 5)
				{
					Create_Boss3();					
					BOSS3_Start = 4;
					second_boss->Set_last_BOSS(BOSS3_Start);
					//Boomb_point = 4;
					arm_lotaion = 1;
				}
			}
		}
		if (arm_lotaion == 1)
		{
			boss_arm->Set_mDir(last_boss->Get_mDir());
			boss_arm->Set_Hurt(last_boss->Get_Hurt());
			last_boss->Set_Grap(boss_arm->Get_grap());
		}
		if (BOSS3_Start == 4)
		{
			
			if (last_boss->GetEnding_point() == 1)
			{
				time = 0;
				Last_Stage_bomb(14300.f,4900.f);
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

				last_boss->SetEnding_point(2);
			}
			if (last_boss->GetEnding_point() == 2)
			{
				int a = 1;
				stage_final->Set_end_Stage(a);
				last_boss->SetEnding_point(3);
			}
			if (stage_final->Get_end_Stage() == 2)
			{
				time += static_cast<float>(Time::DeltaTime());
				if (time > 4)
				{
					ending_boss();
					boss_trash();
					int a = 3;
					stage_final->Set_end_Stage(a);
				}
			}

			if(Boss_end==1)
			{ 
				if (end_boss->GetComponent<Transform>()->GetPos().y > 5400)
				{
					mSonic->Set_Ending(1);
					mtails->Set_Ending(1);
					Boss_end = 2;
				}
			}
		}



		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::MiniGameplay);
			//CreateBlending();
			check_map = 0;
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
		Act6_music->Stop(true);
		Boss_start->Play(true);
		boss_come* boss_run = new boss_come(mSonic);
		boss_run->SetName(L"boss_run");
		AddGameobeject(boss_run, jk_LayerType::MiniBoss);
		boss_run->GetComponent<Transform>()->SetPos(Vector2{ 6607.f, 5265.f });
		boss_run->SetCheckTargetGround(playgr);
	}

	void PlayScene4::Create_Boss2()
	{	
		second_boss = new Second_Boss();
		second_boss->SetName(L"boss_run");
		AddGameobeject(second_boss, jk_LayerType::BOSS);
		second_boss->GetComponent<Transform>()->SetPos(Vector2{ 14750.f, 6000.f });
		BOSS2_Start = 1;
		//(14350.f, 6670.f)
	}

	void PlayScene4::Create_Boss3()
	{
		//Act6_music->Stop(true);
		Last_Boss_f->Play(true);

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

	void PlayScene4::Last_Stage_bomb(float a, float b)
	{
		Stage_bomb->Play(false);
		Scene* curScene = SceneManager::GetActiveScene();
		Last_Boss_bomb* last_bomb = new Last_Boss_bomb(stage_final);
		last_bomb->SetName(L"last_boss_bomb");
		last_bomb->GetComponent<Transform>()->SetPos(Vector2{ a,b });
		curScene->AddGameobeject(last_bomb, jk_LayerType::Effect);
	}

	void PlayScene4::ending_boss()
	{
		Scene* curScene2 = SceneManager::GetActiveScene();
		end_boss = new Ending_boss(last_boss);
		end_boss->SetName(L"end_boss");
		end_boss->GetComponent<Transform>()->SetPos(Vector2{ 14400,4750 });
		curScene2->AddGameobeject(end_boss, jk_LayerType::BOSS);
		Boss_end = 1;
	}

	void PlayScene4::boss_trash()
	{
		Scene* curScene2 = SceneManager::GetActiveScene();
		trash= new Boss_trash(end_boss);
		trash->SetName(L"trash");
		trash->GetComponent<Transform>()->SetPos(Vector2{ 14250,4650 });
		curScene2->AddGameobeject(trash, jk_LayerType::BOSS);
	}
}
