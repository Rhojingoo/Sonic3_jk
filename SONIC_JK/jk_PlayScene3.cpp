#include "jk_PlayScene3.h"
#include "jk_PlayScene2.h"
#include "jk_PlayScene.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_Camera.h"
#include "jk_CollisionManager.h"
#include "jk_Object.h"
#include "jk_Transform.h"
#include "jk_Blending.h"
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
#include "jk_Gameobject.h"
#include "Add_force.h"
#include "Dead_line.h"


#include "jk_Act1_3_BG.h"
#include "Act1_2_sky1.h"
#include "Act1_2_sky2.h"
#include "Act1_2_sky3.h"
#include "Act1_2_sky4.h"
#include "Act1_2_sky5.h"
#include "jk_Last_Bridge.h"
#include "act3_waterfall1.h"
#include "act1_flower1.h"

#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Item_Elect.h"
#include "jk_StageSave.h"


#include "boss_bomber.h"
#include "show_bomb.h"
#include "Boss_appear.h"
#include "Act1_Boss.h"


#include "jk_Snake.h"
#include "jk_Snake_Body_Smoke.h"
#include "jk_Snake_Body.h"
#include "jk_Snake_Body2.h"
#include "jk_Snake_mTaIl.h"
#include "jk_Snake_Tail_End.h"

namespace jk
{
	PlayScene3::PlayScene3()
		: mSonic(nullptr)
		, tails(nullptr)
		, mBoss(nullptr)
		, mBomber(nullptr)
		, bomb(nullptr)
		, add_force()
		, deathline(nullptr)
		, playgr(nullptr)


		, Act2_music(nullptr)
		, Act6_music(nullptr)
		, Bomber(nullptr)
		, Boss_start(nullptr)


		, dir(1)
		, check_map(0)
		, Camera_Switch(0)
		, check_boss(0)
		, frame_check(0)
		, boomber(0)
		, boss_death(0)
		, bomb_check(0)
		, boss_appear(0)
	{
	}
	PlayScene3::~PlayScene3()
	{
	}
	void PlayScene3::Initialize()
	{
		check_map = 2;

		Act2_music = Resources::Load<Sound>(L"Act2_bg", L"..\\Resources\\Sound\\Act2_bg.wav");
		Bomber = Resources::Load<Sound>(L"Bommber_start", L"..\\Resources\\Sound\\Bommber_start.wav");
		Boss_start = Resources::Load<Sound>(L"Boss_start", L"..\\Resources\\Sound\\Boss_start.wav");
		Act6_music = Resources::Load<Sound>(L"Act6_bg", L"..\\Resources\\Sound\\Act6_bg.wav");


		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 600.f, 3285.f });//시작
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 7800.0f, 3650.0f });//꽃앞
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 18400.f, 3900.f });//왕 앞
		//13770.f, 2880.f 


		tails = new Tails(mSonic);
		tails->SetName(L"Player2");
		AddGameobeject(tails, jk_LayerType::Player2);
		tails->GetComponent<Transform>()->SetPos(Vector2{ 600.f, 3285.f });


		playgr = new Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, tails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		tails->SetCheckTargetGround(playgr);
		

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


		deathline = new Dead_line();
		deathline->SetName(L"deathline");
		AddGameobeject(deathline, jk_LayerType::BOSS);
		deathline->GetComponent<Transform>()->SetPos(Vector2{ 19000.f, 4030.f });



		add_force[9];
		for (int a = 0; a < 9; a++)
		{
			add_force[a] = new Add_force();
			add_force[a]->SetName(L"add_force");
			AddGameobeject(add_force[a], jk_LayerType::BG_props);
		}
		add_force[0]->GetComponent<Transform>()->SetPos(Vector2{1165.f, 3340.f });
		add_force[1]->GetComponent<Transform>()->SetPos(Vector2{1240.f, 4030.f});
		add_force[2]->GetComponent<Transform>()->SetPos(Vector2{ 1950.f, 3940.f });
		add_force[3]->GetComponent<Transform>()->SetPos(Vector2{ 2705.f, 3940.f });
		add_force[4]->GetComponent<Transform>()->SetPos(Vector2{ 3480.f, 3940.f });
		add_force[5]->GetComponent<Transform>()->SetPos(Vector2{ 4250.f, 3940.f });
		add_force[6]->GetComponent<Transform>()->SetPos(Vector2{ 5010.f, 3940.f });
		add_force[7]->GetComponent<Transform>()->SetPos(Vector2{ 5790.f, 3940.f });
		add_force[8]->GetComponent<Transform>()->SetPos(Vector2{ 7200.f, 3985.f });
		add_force[8]->SetAddforce(1);

		//배경
		Act1_3_BG* act1_3_BG = new Act1_3_BG();
		act1_3_BG->SetName(L"act1_3_BG");
		AddGameobeject(act1_3_BG, jk_LayerType::BG);


		Act1_2_sky1* act1_2_sky1 = new Act1_2_sky1();
		act1_2_sky1->SetName(L"act1_2_sky1");
		AddGameobeject(act1_2_sky1, jk_LayerType::foreground);
		act1_2_sky1->GetComponent<Transform>()->SetPos(Vector2(0.f, 1988.f));


		Act1_2_sky2* act1_2_sky2 = new Act1_2_sky2();
		act1_2_sky2->SetName(L"act2_sky2");
		AddGameobeject(act1_2_sky2, jk_LayerType::foreground);
		act1_2_sky2->GetComponent<Transform>()->SetPos(Vector2(0.f,2043.f));


		Act1_2_sky3* act1_2_sky3 = new Act1_2_sky3();
		act1_2_sky3->SetName(L"act1_2_sky3");
		AddGameobeject(act1_2_sky3, jk_LayerType::foreground);
		act1_2_sky3->GetComponent<Transform>()->SetPos(Vector2(-200.f,2940.f));


		Act1_2_sky4* act1_2_sky4 = new Act1_2_sky4();
		act1_2_sky4->SetName(L"act1_2_sky4");
		AddGameobeject(act1_2_sky4, jk_LayerType::foreground);
		act1_2_sky4->GetComponent<Transform>()->SetPos(Vector2(-300.f, 3180.f));

	
		Act1_2_sky5* act1_2_sky5 = new Act1_2_sky5();
		act1_2_sky5->SetName(L"act1_2_sky5");
		AddGameobeject(act1_2_sky5, jk_LayerType::foreground);
		act1_2_sky5->GetComponent<Transform>()->SetPos(Vector2(-100.f, 3612.f));

		act3_waterfall1* waterfall_1 = new act3_waterfall1();
		AddGameobeject(waterfall_1, jk_LayerType::BG);
		waterfall_1->SetName(L"waterfall_1");
		waterfall_1->GetComponent<Transform>()->SetPos(Vector2{ 19269.f, 3974.f });




		act1_flower1* flower1[4];
		for (int a = 0; a < 4; a++)
		{
			flower1[a] = new act1_flower1();
			flower1[a]->SetName(L"flower1");
			AddGameobeject(flower1[a], jk_LayerType::BG);
		}
		flower1[0]->GetComponent<Transform>()->SetPos(Vector2{ 465.0f, 3330.0f });
		flower1[1]->GetComponent<Transform>()->SetPos(Vector2{ 700.0f, 3330.0f });
		flower1[2]->GetComponent<Transform>()->SetPos(Vector2{ 7365.0f, 3650.0f });
		flower1[3]->GetComponent<Transform>()->SetPos(Vector2{ 7800.0f, 3650.0f });	
		


		//배경 소품
		Last_Bridge* last_Bridge = new Last_Bridge();
		last_Bridge->SetName(L"last_Bridge");
		AddGameobeject(last_Bridge, jk_LayerType::BG_props);
		last_Bridge->GetComponent<Transform>()->SetPos(Vector2{ 18980.f, 3930.f });



		Scene::Initialize();

	}
	void PlayScene3::Update()
	{
		playgr->Set_map_check(check_map);
		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();

		//if (sonic_pos.x > 6900.f)
		//{
		//	Camera::SetCamera(0);
		//}		

		if (sonic_pos.x >= 1155.f)
		{
			Camera::SetCamera(0);
		}
		


		float sonic_bomber = 0;
		if (sonic_pos.x >= 8700.f)
		{
			Camera::SetCamera(1);
			if(boomber == 0)
			{
			Create_Boomber_show();			
			boomber = 1;
			}
		}		

		if (boomber == 1)
		{
			sonic_bomber = mBomber->GetComponent<Transform>()->GetPos().x - sonic_pos.x;
			Vector2 mBomber_pos1;
			Vector2 mBomber_pos2;
			Vector2 mBomber_pos3;
			mBomber_pos1 = mBomber->GetComponent<Transform>()->GetPos();
			mBomber_pos2 = mBomber->GetComponent<Transform>()->GetPos();
			mBomber_pos3 = mBomber->GetComponent<Transform>()->GetPos();
			mBomber_pos1.x = mBomber_pos3.x + 480; //맨앞
			mBomber_pos2.x = mBomber_pos3.x + 280; //중간
			mBomber_pos3.x = mBomber_pos3.x + 120; //맨뒤


			if((bomb_check==0)&&(mBomber_pos1.x+200 >= sonic_pos.x))
			{
				Create_Boomber_bombing(mBomber_pos1.x, mBomber_pos1.y + 384);			
				bomb_check = 1;
			}
			if((bomb_check==1)&&(mBomber_pos2.x + 200 >= sonic_pos.x))
			{
				Create_Boomber_bombing(mBomber_pos2.x, mBomber_pos2.y + 384);		
				bomb_check = 2;
			}
			if((bomb_check==2)&&(mBomber_pos3.x+200 >= sonic_pos.x))
			{
				Create_Boomber_bombing(mBomber_pos3.x, mBomber_pos3.y + 384);			
				bomb_check = 3;
			}
		}

		if (sonic_bomber >= 800.f)
		{
			Bomber->Stop(true);
		}

		if (sonic_pos.x >= 14640.f)
		{			
			if (boss_appear == 0)
			{
				Create_Boss_Apear();			
				boss_appear = 1;
			}
		}

		if (sonic_pos.x >= 19470.f)
		{
			Camera_Switch = 1;
		}

		if (Camera_Switch == 1)
		{
			
			Camera::SetTarget(nullptr);
			
			if (check_boss == 0)
			{
				if (check_boss != 0)
					return;
				Create_Deathtline();
				Create_Boss();
				check_boss = 1;
			}
		}

		if (check_boss == 1)
		{
			Vector2 Boss_Pos = mBoss->GetComponent<Transform>()->GetPos();
			if (Boss_Pos.x > 19500.f)
			{				
				Camera::SetCamera(2);
				Camera::SetTarget(mBoss);								
			}
			if (Boss_Pos.x > 19940.f)
			{				
				Camera::SetTarget(nullptr);
				check_boss = 2;
			}			
		}

		if (check_boss == 2)
		{
 			boss_death = mBoss->Boss_Death();
			if (boss_death == 3)
			{
				int boss_run = 1;
				tails->Set_Pursue_boss(boss_run);
				check_boss = 3;
			}
		}

		if ((boss_death == 3) && (sonic_pos.x > 20885.f))
		{
			Act2_music->Stop(true);
			Act6_music->Play(true);
			SceneManager::LoadScene(jk_SceneType::GamePlay4);
		}

		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			Act2_music->Stop(true);
			Act6_music->Play(true);
			SceneManager::LoadScene(jk_SceneType::GamePlay4);
			//CreateBlending();
			check_map = 3;
		}
	}


	void PlayScene3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene3::Release()
	{
		Scene::Release();
	}

	void PlayScene3::OnEnter()
	{
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Monster, true);//충돌시 가리키는 장면
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
		CollisionManager::SetLayer(jk_LayerType::Bullet, jk_LayerType::BG_props, true);

		Camera::SetTarget(mSonic);
	}

	void PlayScene3::OnExit()
	{
	}

	void PlayScene3::CreateBlending()
	{
	}

	void PlayScene3::Create_Boss_Apear()
	{		
		Boss_appear* boss_apear = new Boss_appear(mSonic);
		boss_apear->SetName(L"boss_apear");
		AddGameobeject(boss_apear, jk_LayerType::foreground);
		boss_apear->GetComponent<Transform>()->SetPos(Vector2{ 14640.f, 3630.f });
	}


	void PlayScene3::Create_Boss()
	{	
		Act2_music->Stop(true);
		Boss_start->Play(true);


		mBoss = new Act1_Boss(mSonic);
		mBoss->SetName(L"boss");
		AddGameobeject(mBoss, jk_LayerType::BOSS);
		mBoss->GetComponent<Transform>()->SetPos(Vector2{ 19005.f, 3480.f });
	}

	void PlayScene3::Create_Deathtline()
	{

	}


	void PlayScene3::Create_Boomber_show()
	{
		Bomber->Play(true);
		mBomber = new boss_bomber(mSonic);
		mBomber->SetName(L"bomber");
		AddGameobeject(mBomber, jk_LayerType::MiniBoss);
		mBomber->GetComponent<Transform>()->SetPos(Vector2{ 7000.f, 3150.f });
	}


	void PlayScene3::Create_Boomber_bombing(float a, float b)
	{
		bomb = new show_bomb(mSonic);
		bomb->SetName(L"act1_3_bomb");
		AddGameobeject(bomb, jk_LayerType::Bullet);
		bomb->GetComponent<Transform>()->SetPos(Vector2{ a, b });
		bomb->SetCheckTargetGround(playgr);
	}
}
