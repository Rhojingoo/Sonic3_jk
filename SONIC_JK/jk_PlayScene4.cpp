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


#include "jk_Sonic.h"
#include "Electsonic.h"
#include "jk_Tails.h"


#include "jk_Ground.h"
#include "jk_Act6_BG.h"
#include "act6_sky1.h"
#include "act6_sky2.h"
#include "act6_sky3.h"
#include "act6_sky4.h"
#include "act6_sky5.h"
#include "act6_sky6.h"
#include "act6_sky7.h"

#include "Robotnic_machine.h"
#include "boss1_body.h"
#include "boss_come.h"
#include "boss1_object.h"
#include "finall_stage.h"

#include "Second_Boss.h"
#include "Third_Boss.h"
#include "Boss_Arm.h"

#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Item.h"
#include "jk_StageSave.h"




namespace jk
{
	PlayScene4::PlayScene4()
		:Boss_Death_point(0)
		, map_lotation(0)
		
	{
	}
	PlayScene4::~PlayScene4()
	{
	}
	void PlayScene4::Initialize()
	{
		check_map = 3;

		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);

		Sonic::eSonicState::Jeep_line;
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 6000.f, 5085.f });
		mSonic->Set_Fly(1);

		Tails* tails = new Tails(mSonic);
		tails->SetName(L"Player2");
		AddGameobeject(tails, jk_LayerType::Player2);
		Tails::eTailsState::Fly_Waiting;
		tails->GetComponent<Transform>()->SetPos(Vector2{ 840.f, 4830.f });
		tails->Set_Fly(1);


		playgr = new Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, tails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		tails->SetCheckTargetGround(playgr);
	
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

		act6_sky1* sky1 = new act6_sky1();
		sky1->SetName(L"act6_sky1");
		AddGameobeject(sky1, jk_LayerType::foreground);
		sky1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, -500.f });//432

		//act6_sky2* sky2 = new act6_sky2();
		//sky2->SetName(L"act6_sky1");
		//AddGameobeject(sky2, jk_LayerType::foreground);
		//sky2->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 432.f });//546  =  978

		//act6_sky2* sky2_1 = new act6_sky2();
		//sky2_1->SetName(L"act6_sky1");
		//AddGameobeject(sky2_1, jk_LayerType::foreground);
		//sky2_1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 978.f });//546  = 1524

		//act6_sky2* sky2_2 = new act6_sky2();
		//sky2_2->SetName(L"act6_sky1");
		//AddGameobeject(sky2_2, jk_LayerType::foreground);
		//sky2_2->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 1524.f });// 546  = 2070


		//act6_sky3* sky3 = new act6_sky3();
		//sky3->SetName(L"act6_sky3");
		//AddGameobeject(sky3, jk_LayerType::foreground);
		//sky3->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 2070.f });//216  = 2286


		//act6_sky3* sky3_1 = new act6_sky3();
		//sky3_1->SetName(L"act6_sky3");
		//AddGameobeject(sky3_1, jk_LayerType::foreground);
		//sky3_1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 2286.f });//216 = 2502


		//act6_sky4* sky4 = new act6_sky4();
		//sky4->SetName(L"act6_sky4");
		//AddGameobeject(sky1, jk_LayerType::foreground);
		//sky4->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 2502.f });//237 = 2739


		//act6_sky5* sky5 = new act6_sky5();
		//sky5->SetName(L"act6_sky5");
		//AddGameobeject(sky5, jk_LayerType::foreground);
		//sky5->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 2739.f });// 165  = 2904


		//
		//act6_sky3* sky3_2 = new act6_sky3();
		//sky3_2->SetName(L"act6_sky3");
		//AddGameobeject(sky3_2, jk_LayerType::foreground);
		//sky3_2->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 2904.f });//216 = 3120


		//act6_sky4* sky4_1 = new act6_sky4();
		//sky4_1->SetName(L"act6_sky4");
		//AddGameobeject(sky4_1, jk_LayerType::foreground);
		//sky4_1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 3120.f });//237 = 3357


		//act6_sky5* sky5_1 = new act6_sky5();
		//sky5_1->SetName(L"act6_sky5");
		//AddGameobeject(sky5_1, jk_LayerType::foreground);
		//sky5_1->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 3357.f });//165 = 3522


		//act6_sky2* sky2_3 = new act6_sky2();
		//sky2_3->SetName(L"act6_sky1");
		//AddGameobeject(sky2_3, jk_LayerType::foreground);
		//sky2_3->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 3522.f });//546  =4068


		//act6_sky3* sky3_3 = new act6_sky3();
		//sky3_3->SetName(L"act6_sky3");
		//AddGameobeject(sky3_3, jk_LayerType::foreground);
		//sky3_3->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 4068.f }); //216 = 4284


		//act6_sky4* sky4_2 = new act6_sky4();
		//sky4_2->SetName(L"act6_sky4");
		//AddGameobeject(sky4_2, jk_LayerType::foreground);
		//sky4_2->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 4284.f });//237 = 4521


		//act6_sky5* sky5_2 = new act6_sky5();
		//sky5_2->SetName(L"act6_sky5");
		//AddGameobeject(sky5_1, jk_LayerType::foreground);
		//sky5_2->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 4521.f });//165  = 4686


		//act6_sky2* sky2_4 = new act6_sky2();
		//sky2_4->SetName(L"act6_sky1");
		//AddGameobeject(sky2_4, jk_LayerType::foreground);
		//sky2_4->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 4500.f });//546  = 5232 독단 시작


		//act6_sky6* sky6 = new act6_sky6();
		//sky6->SetName(L"act6_sky6");
		//AddGameobeject(sky6, jk_LayerType::foreground);
		//sky6->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 5046.f });// 360 = 5406


		//act6_sky7* sky7 = new act6_sky7();
		//sky7->SetName(L"act6_sky7");
		//AddGameobeject(sky7, jk_LayerType::foreground);
		//sky7->GetComponent<Transform>()->SetPos(Vector2{ 100.f, 5406.f });//288 = 5694


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
		}

		if (map_lotation == 0)//LAST STAGE FIRE
		{
			if (sonic_pos.x >= 9500.f)
			{
				map_lotation = 1;
				stage_final->Set_move_stage(map_lotation);
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

		else if (Camera_Switch == 0)
		{
			Camera::SetTarget(mSonic);
			Camera::SetCamera(0);
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
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Player2, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::MiniBoss, true);
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::BOSS, true);
		CollisionManager::SetLayer(jk_LayerType::BOSS, jk_LayerType::BOSS, true);



		Camera::SetTarget(mSonic);
	}
	void PlayScene4::OnExit()
	{
	}
	void PlayScene4::CreateBlending()
	{
	}
	void PlayScene4::Create_Boss1()
	{
		boss_come* boss_run = new boss_come(mSonic);
		boss_run->SetName(L"boss_run");
		AddGameobeject(boss_run, jk_LayerType::BOSS);
		boss_run->GetComponent<Transform>()->SetPos(Vector2{ 6607.f, 5265.f });
		boss_run->SetCheckTargetGround(playgr);
	}

	void PlayScene4::Create_Boss2()
	{
		second_boss = new Second_Boss();
		second_boss->SetName(L"boss_run");
		AddGameobeject(second_boss, jk_LayerType::BOSS);
		second_boss->GetComponent<Transform>()->SetPos(Vector2{ 14750.f, 6000.f });

		//(14350.f, 6670.f)
	}


}
//Third_Boss
//Boss_Arm

//27,87