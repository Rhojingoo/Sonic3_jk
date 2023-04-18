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
#include "jk_Collapses_Ground.h"
#include "jk_check1.h"
#include "jk_check2.h"

#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Item.h"
#include "jk_StageSave.h"
#include "jk_ItemBigRing.h"

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
		mSonic->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f));


		Tails* tails = new Tails(mSonic);
		tails->SetName(L"Player2");
		AddGameobeject(tails, jk_LayerType::Player2);
		tails->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f));


		//아이템
		//ItemBigRing* Big_Ring = new ItemBigRing();
		//Big_Ring->SetName(L"BIGRING");


		//Item* items = new Item(mSonic);
		//items->SetName(L"items");


		//배경
		Act1_2_BG* act1_2_BG = new Act1_2_BG();
		act1_2_BG->SetName(L"act1_2_BG");
		AddGameobeject(act1_2_BG, jk_LayerType::BG);



		//배경소품
		playgr = new Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, tails);
		AddGameobeject(playgr, jk_LayerType::Ground);

		mSonic->SetCheckTargetGround(playgr);
		tails->SetCheckTargetGround(playgr);

		//StageSave* save = new StageSave;
		//save->SetName(L"StageSave");


		Spring_Up* spring_Up[1];
		for (int a = 0; a < 1; a++)
		{
			spring_Up[a] = new Spring_Up();
			spring_Up[a]->SetName(L"spring_Up");
			AddGameobeject(spring_Up[a], jk_LayerType::BG_props);
		}
		spring_Up[0]->GetComponent<Transform>()->SetPos(Vector2{ 3624.0f, 3381.0f });


		Move_GR* gr_move[1];
		for (int a = 0; a < 1; a++)
		{
			gr_move[a] = new Move_GR();
			gr_move[a]->SetName(L"gr_move");
			AddGameobeject(gr_move[a], jk_LayerType::BG_props);
		}
		gr_move[0]->GetComponent<Transform>()->SetPos(Vector2{ 661.f, 2933.f });
		gr_move[0]->SetCenterpos(Vector2{ 661.f,2933.f });
		gr_move[0]->Setmaxdistance(float{ 100.f });






		//몬스터 및 보스
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

		//Camera::SetTarget(nullptr);
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::MiniGameplay);
			CreateBlending();
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

		Camera::SetTarget(mSonic);
	}
	void PlayScene2::OnExit()
	{
	}
	void PlayScene2::CreateBlending()
	{
	}
	void PlayScene2::Create_Miniboss_show()
	{
	}
}