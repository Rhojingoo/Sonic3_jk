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


#include "jk_Sonic.h"
#include "Electsonic.h"
#include "jk_Tails.h"

#include "jk_Ground.h"
#include "jk_Gameobject.h"

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
#include "jk_Item.h"
#include "jk_StageSave.h"


#include "jk_Boss.h"

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
		, dir(1)
		, Camera_Switch(0)
		, check_boss(0)
		, frame_check(0)
		, check_map(0)
	{
	}
	PlayScene3::~PlayScene3()
	{
	}
	void PlayScene3::Initialize()
	{
		check_map = 2;

		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 600.f, 3285.f });//시작
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 7800.0f, 3650.0f });//꽃앞
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 18400.f, 3900.f });//왕 앞
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
		act1_2_sky3->GetComponent<Transform>()->SetPos(Vector2(500.f,2940.f));


		Act1_2_sky4* act1_2_sky4 = new Act1_2_sky4();
		act1_2_sky4->SetName(L"act1_2_sky4");
		AddGameobeject(act1_2_sky4, jk_LayerType::foreground);
		act1_2_sky4->GetComponent<Transform>()->SetPos(Vector2(500.f, 3180.f));


		Act1_2_sky5* act1_2_sky5 = new Act1_2_sky5();
		act1_2_sky5->SetName(L"act1_2_sky5");
		AddGameobeject(act1_2_sky5, jk_LayerType::foreground);
		act1_2_sky5->GetComponent<Transform>()->SetPos(Vector2(500.f, 3612.f));

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


		//StageSave* save = new StageSave();
		//save->SetName(L"StageSave");
		//AddGameobeject(save, jk_LayerType::BG_props);
		//save->GetComponent<Transform>()->SetPos(Vector2(2208.f, 2818.f));


		//몬스터
		//Snake_Body_Smoke* snake_Body_Smoke[1];
		//for (int a = 0; a < 1; a++)
		//{
		//	snake_Body_Smoke[a] = new Snake_Body_Smoke();
		//	snake_Body_Smoke[a]->SetName(L"Snake_Body");
		//	AddGameobeject(snake_Body_Smoke[a], jk_LayerType::Monster);
		//}
		//snake_Body_Smoke[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		//snake_Body_Smoke[0]->Set_Snake_Body(Snake_head[0]);
		////snake_Body_Smoke[1]->GetComponent<Transform>()->SetPos(Vector2{ 7710.f, 3756.f });
		////snake_Body_Smoke[1]->Set_Snake_Body(Snake_head[1]);


		//Snake_Body* snake_body[1];
		//for (int a = 0; a < 1; a++)
		//{
		//	snake_body[a] = new Snake_Body();
		//	snake_body[a]->SetName(L"Snake_Body");
		//	AddGameobeject(snake_body[a], jk_LayerType::Monster);
		//}
		//snake_body[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		//snake_body[0]->Set_Snake_Body(snake_Body_Smoke[0]);



		//Snake_body2* snake_body_2 = new Snake_body2();
		//snake_body_2->SetName(L"Snake_Body2");
		//AddGameobeject(snake_body_2, jk_LayerType::Monster);
		//snake_body_2->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		//snake_body_2->Set_Snake_body_third(snake_body[0]);


		//Snake_mTaIl* snake_mT[1];
		//for (int a = 0; a < 1; a++)
		//{
		//	snake_mT[a] = new Snake_mTaIl();
		//	snake_mT[a]->SetName(L"Snake_Body");
		//	AddGameobeject(snake_mT[a], jk_LayerType::Monster);
		//}
		//snake_mT[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		//snake_mT[0]->Set_Snake_body_third(snake_body_2);

		//Snake_Tail_End* Snake_Tail[1];
		//for (int a = 0; a < 1; a++)
		//{
		//	Snake_Tail[a] = new Snake_Tail_End();
		//	Snake_Tail[a]->SetName(L"Snake_Body");
		//	AddGameobeject(Snake_Tail[a], jk_LayerType::Monster);
		//}
		//Snake_Tail[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		//Snake_Tail[0]->Set_Snake_body_third(snake_mT[0]);
		Scene::Initialize();

	}
	void PlayScene3::Update()
	{
		playgr->Set_map_check(check_map);

		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();

		if (sonic_pos.x >= 1155.f)
		{
			Camera::SetCamera(0);
		}

		if (sonic_pos.x >= 8700.f)
		{
			Camera::SetCamera(1);
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
			SceneManager::LoadScene(jk_SceneType::GamePlay4);
		}

		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
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

	void PlayScene3::Create_Boss()
	{		
		mBoss = new Boss(mSonic);
		mBoss->SetName(L"boss");
		AddGameobeject(mBoss, jk_LayerType::BOSS);
		mBoss->GetComponent<Transform>()->SetPos(Vector2{ 19005.f, 3480.f });
	}
}
