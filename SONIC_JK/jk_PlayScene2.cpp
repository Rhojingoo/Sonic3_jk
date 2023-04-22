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


#include "jk_Act1_2_BG.h"

#include "jk_Rock_small.h"
#include "jk_Move_GR.h""
#include "jk_Spring_Up.h"
#include "jk_Spring_Left.h"
#include "jk_Spike_Up.h"
#include "jk_Rock_middle.h"
#include "jk_Rock_big.h"
#include "jk_Jeep_line.h"
#include "jk_Jeep_line_Handle.h"
#include "Jeepline_play.h"
#include "jk_Collapses_Ground.h"
#include "jk_Collapses_GR_left.h"
#include "jk_check1.h"
#include "jk_check2.h"
#include "jk_Clean_wall.h"

#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Item.h"
#include "jk_StageSave.h"
#include "jk_ItemBigRing.h"

#include "jk_Minibos.h"

#include "jk_Monster.h"
#include "jk_Monkey.h"
#include "jk_Cannon.h"
#include "jk_Snake.h"
#include "jk_Snake_Body_Smoke.h"
#include "jk_Snake_Body.h"
#include "jk_Snake_Body2.h"
#include "jk_Snake_mTaIl.h"
#include "jk_Snake_Tail_End.h"


namespace jk
{
	PlayScene2::PlayScene2()
		: mSonic(nullptr)
		, dir(1)
		, Camera_Switch(0)
		, check_minibos(0)
		, frame_check(0)
		, check_map(0)
	{
	}
	PlayScene2::~PlayScene2()
	{
	}
	void PlayScene2::Initialize()
	{
		check_map = 1;
		
		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);
		//mSonic->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f)); 시작위치
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 13100.f,3240.f }); 미니 보스

		//13770.f, 2880.f

		Tails* tails = new Tails(mSonic);
		tails->SetName(L"Player2");
		AddGameobeject(tails, jk_LayerType::Player2);
		tails->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f));
	

		playgr = new Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, tails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		tails->SetCheckTargetGround(playgr);

		//아이템
		//ItemBigRing* Big_Ring = new ItemBigRing();
		//Big_Ring->SetName(L"BIGRING");

		Item* items = new Item(mSonic);
		items->SetName(L"items");
		AddGameobeject(items, jk_LayerType::Item);
		items->GetComponent<Transform>()->SetPos(Vector2(800.f, 3033.f));

		//배경
		Act1_2_BG* act1_2_BG = new Act1_2_BG();
		act1_2_BG->SetName(L"act1_2_BG");
		AddGameobeject(act1_2_BG, jk_LayerType::BG);


		//배경소품
		StageSave* save = new StageSave();
		save->SetName(L"StageSave");
		AddGameobeject(save, jk_LayerType::BG_props);
		save->GetComponent<Transform>()->SetPos(Vector2(2208.f, 2818.f));

		Jeepline_play* jeepline = new Jeepline_play();
		jeepline->SetName(L"jeepline");
		AddGameobeject(jeepline, jk_LayerType::BG_props);
		jeepline->GetComponent<Transform>()->SetPos(Vector2(6580.f, 2940.f));
		mSonic->GetComponent<Transform>()->SetPos(Vector2(6450.f, 2940.f));

		Rock_big* rock_big[1];
		for (int a = 0; a < 1; a++)
		{
			rock_big[a] = new Rock_big();
			rock_big[a]->SetName(L"rock_big");
			AddGameobeject(rock_big[a], jk_LayerType::BG_props);
		}
		rock_big[0]->GetComponent<Transform>()->SetPos(Vector2{ 2096.0f, 3363.0f });
		rock_big[0]->SetCheckTargetGround(playgr);


		Collapses_Ground* collapses_Ground[5];
		for (int a = 0; a < 5; a++)
		{
			collapses_Ground[a] = new Collapses_Ground();
			collapses_Ground[a]->SetName(L"collapses_Ground");
			AddGameobeject(collapses_Ground[a], jk_LayerType::BG_props);
		}
		collapses_Ground[0]->GetComponent<Transform>()->SetPos(Vector2{ 4335.0f, 3300.0f });
		collapses_Ground[1]->GetComponent<Transform>()->SetPos(Vector2{ 6640.f, 3410.f });
		collapses_Ground[2]->GetComponent<Transform>()->SetPos(Vector2{ 8180.f, 3990.f });
		collapses_Ground[3]->GetComponent<Transform>()->SetPos(Vector2{ 4720.f, 4560.f });
		collapses_Ground[4]->GetComponent<Transform>()->SetPos(Vector2{ 11050.f, 3415.f });
		

		Collapses_GR_left* collapses_GR_left[4];
		for (int a = 0; a < 4; a++)
		{
			collapses_GR_left[a] = new Collapses_GR_left();
			collapses_GR_left[a]->SetName(L"collapses_Ground_L");
			AddGameobeject(collapses_GR_left[a], jk_LayerType::BG_props);
		}
		collapses_GR_left[0]->GetComponent<Transform>()->SetPos(Vector2{ 4825.0f, 3410.0f });
		collapses_GR_left[1]->GetComponent<Transform>()->SetPos(Vector2{ 7125.f, 3980.f });
		collapses_GR_left[2]->GetComponent<Transform>()->SetPos(Vector2{ 8490.f, 3800.f });
		collapses_GR_left[3]->GetComponent<Transform>()->SetPos(Vector2{ 11550.f, 3210.f });
		


		Spring_Up* spring_Up[5];
		for (int a = 0; a < 5; a++)
		{
			spring_Up[a] = new Spring_Up();
			spring_Up[a]->SetName(L"spring_Up");
			AddGameobeject(spring_Up[a], jk_LayerType::BG_props);
		}
		spring_Up[0]->GetComponent<Transform>()->SetPos(Vector2{ 3624.0f, 3381.0f });
		spring_Up[1]->GetComponent<Transform>()->SetPos(Vector2{ 1750.0f, 4558.0f });
		spring_Up[2]->GetComponent<Transform>()->SetPos(Vector2{ 5550.0f, 5000.0f });
		spring_Up[3]->GetComponent<Transform>()->SetPos(Vector2{ 10248.0f, 4812.0f });
		spring_Up[4]->GetComponent<Transform>()->SetPos(Vector2{ 11300.0f, 4400.0f });
		

		Move_GR* gr_move[2];
		for (int a = 0; a < 2; a++)
		{
			gr_move[a] = new Move_GR();
			gr_move[a]->SetName(L"gr_move");
			AddGameobeject(gr_move[a], jk_LayerType::BG_props);
		}
		gr_move[0]->GetComponent<Transform>()->SetPos(Vector2{ 661.f, 2933.f });
		gr_move[0]->SetCenterpos(Vector2{ 661.f,2933.f });
		gr_move[0]->Setmaxdistance(float{ 100.f });
		gr_move[1]->GetComponent<Transform>()->SetPos(Vector2{ 9714.f,5346.f });
		gr_move[1]->SetCenterpos(Vector2{ 9714.f,5346.f });
		gr_move[1]->Setmaxdistance(float{ 150.f });


		//몬스터 및 보스
		Monster* mRino = new Monster();
		mRino->SetName(L"RinoMonster2");
		AddGameobeject(mRino, jk_LayerType::Monster);
		mRino->GetComponent<Transform>()->SetPos(Vector2{6450.0f,4350.0f });
		mRino->SetCenterpos(Vector2{ 6540.0f, 4350.0f });
		mRino->SetCheckTargetGround(playgr);


		Snake* Snake_head[1];
		for (int a = 0; a < 1; a++)
		{
			Snake_head[a] = new Snake(mSonic);
			Snake_head[a]->SetName(L"Snake_head");
			AddGameobeject(Snake_head[a], jk_LayerType::Monster);
		}
		Snake_head[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		Snake_head[0]->SetCenterpos(Vector2{ 6270.f, 3210.f });
		//Snake_head[1]->GetComponent<Transform>()->SetPos(Vector2{ 7710.f, 3756.f });
		//Snake_head[1]->SetCenterpos(Vector2{ 7710.f, 3756.f });


		Snake_Body_Smoke* snake_Body_Smoke[1];
		for (int a = 0; a < 1; a++)
		{
			snake_Body_Smoke[a] = new Snake_Body_Smoke();
			snake_Body_Smoke[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_Body_Smoke[a], jk_LayerType::Monster);
		}
		snake_Body_Smoke[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		snake_Body_Smoke[0]->Set_Snake_Body(Snake_head[0]);
		//snake_Body_Smoke[1]->GetComponent<Transform>()->SetPos(Vector2{ 7710.f, 3756.f });
		//snake_Body_Smoke[1]->Set_Snake_Body(Snake_head[1]);


		Snake_Body* snake_body[1];
		for (int a = 0; a < 1; a++)
		{
			snake_body[a] = new Snake_Body();
			snake_body[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_body[a], jk_LayerType::Monster);
		}
		snake_body[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		snake_body[0]->Set_Snake_Body(snake_Body_Smoke[0]);



		Snake_body2* snake_body_2 = new Snake_body2();
		snake_body_2->SetName(L"Snake_Body2");
		AddGameobeject(snake_body_2, jk_LayerType::Monster);
		snake_body_2->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		snake_body_2->Set_Snake_body_third(snake_body[0]);


		Snake_mTaIl* snake_mT[1];
		for (int a = 0; a < 1; a++)
		{
			snake_mT[a] = new Snake_mTaIl();
			snake_mT[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_mT[a], jk_LayerType::Monster);
		}
		snake_mT[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		snake_mT[0]->Set_Snake_body_third(snake_body_2);

		Snake_Tail_End* Snake_Tail[1];
		for (int a = 0; a < 1; a++)
		{
			Snake_Tail[a] = new Snake_Tail_End();
			Snake_Tail[a]->SetName(L"Snake_Body");
			AddGameobeject(Snake_Tail[a], jk_LayerType::Monster);
		}
		Snake_Tail[0]->GetComponent<Transform>()->SetPos(Vector2{ 6270.f, 3210.f });
		Snake_Tail[0]->Set_Snake_body_third(snake_mT[0]);


		//Boss* ROBOT = new Boss(mSonic);
		//ROBOT->SetName(L"BOSS");


		//링위치
		//Ring* ring[100];
		//for (int a = 0; a < 100; a++)
		//{
		//	ring[a] = new Ring(mSonic);
		//	AddGameobeject(ring[a], jk_LayerType::Rings);
		//}
		//ring[0]->GetComponent<Transform>()->SetPos(Vector2{ 11276.0f, 3056.0f });
		//ring[1]->GetComponent<Transform>()->SetPos(Vector2{ 11376.0f, 3056.0f });
		//ring[2]->GetComponent<Transform>()->SetPos(Vector2{ 11476.0f, 3056.0f });
		//ring[3]->GetComponent<Transform>()->SetPos(Vector2{ 11712.0f, 3161.0f });
		//ring[4]->GetComponent<Transform>()->SetPos(Vector2{ 11812.0f, 3211.0f });
		//ring[5]->GetComponent<Transform>()->SetPos(Vector2{ 11912.0f, 3261.0f });
		//ring[6]->GetComponent<Transform>()->SetPos(Vector2{ 12012.0f, 3311.0f });
		//ring[7]->GetComponent<Transform>()->SetPos(Vector2{ 12112.0f, 3361.0f });
		//ring[8]->GetComponent<Transform>()->SetPos(Vector2{ 12627.f, 3405.f });
		//ring[9]->GetComponent<Transform>()->SetPos(Vector2{ 12727.f, 3355.f });
		//ring[10]->GetComponent<Transform>()->SetPos(Vector2{ 12797.f, 3285.f });
		//ring[11]->GetComponent<Transform>()->SetPos(Vector2{ 13687.f, 3208.f });
		//ring[12]->GetComponent<Transform>()->SetPos(Vector2{ 13787.f, 3208.f });
		//ring[13]->GetComponent<Transform>()->SetPos(Vector2{ 13887.f, 3208.f });
		//ring[14]->GetComponent<Transform>()->SetPos(Vector2{ 17232.f, 3783.f });
		//ring[15]->GetComponent<Transform>()->SetPos(Vector2{ 17332.f, 3733.f });
		//ring[16]->GetComponent<Transform>()->SetPos(Vector2{ 17432.f, 3683.f });
		//ring[17]->GetComponent<Transform>()->SetPos(Vector2{ 20013.f, 3376.f });
		//ring[18]->GetComponent<Transform>()->SetPos(Vector2{ 20092.f, 3226.f });
		//ring[19]->GetComponent<Transform>()->SetPos(Vector2{ 20258.f, 3163.f });
		//ring[20]->GetComponent<Transform>()->SetPos(Vector2{ 20426.f, 3225.f });
		//ring[21]->GetComponent<Transform>()->SetPos(Vector2{ 20498.f, 3379.f });


		Scene::Initialize();

	}

	void PlayScene2::Update()
	{
		playgr->Set_map_check(check_map);

		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();

		if (sonic_pos.x >= 13200.f)
		{
			Camera_Switch = 1;
		}
		if (Camera_Switch == 1)
		{
			Camera::SetTarget(nullptr);
			if (check_minibos == 0)
			{
				if (check_minibos != 0)
					return;

				Create_Miniboss();
				check_minibos = 1;
			}
		}

		//Camera::SetTarget(nullptr);
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::GamePlay3);
			//CreateBlending();
			check_map = 0;
		}
	}
	void PlayScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene2::Release()
	{
		Scene::Release();
	}
	void PlayScene2::OnEnter()
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


		Camera::SetTarget(mSonic);
	}
	void PlayScene2::OnExit()
	{
	}
	void PlayScene2::CreateBlending()
	{
	}
	void PlayScene2::Create_Miniboss()
	{
		Minibos* mboss = new Minibos(mSonic);
		mboss->SetName(L"mboss");
		AddGameobeject(mboss, jk_LayerType::MiniBoss);
		mboss->GetComponent<Transform>()->SetPos(Vector2{ 13770.f, 2880.f });
	}

}