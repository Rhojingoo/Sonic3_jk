#include "jk_PlayScene.h"
#include "jk_Sonic.h"
#include "jk_Transform.h"
#include "jk_Tails.h"
#include "jk_tails_tail.h"
#include "jk_Act1_BG_object.h"
#include "jk_Boss.h"
#include "jk_Monster.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_BaseBullet.h"
#include "jk_ItemBigRing.h"
#include "jk_StageSave.h"
#include "jk_Camera.h"
#include "jk_CollisionManager.h"
#include "JK_Act1skyBG.h"
#include "jk_Object.h"
#include "jk_Item.h"
#include "jk_Blending.h"
#include "jk_Ground.h"
#include "act1_forest1.h"
#include "acr1_forest2.h"
#include "midlesky.h"
#include "jk_Ring.h"
#include "jk_Ring_Falling.h"
#include "jk_Monkey.h"
#include "jk_Cannon.h"
#include "jk_Snake.h"
#include "jk_Snake_Body_Smoke.h"
#include "jk_Snake_Body.h"
#include "jk_Snake_Body2.h"
#include "jk_Snake_mTaIl.h"
#include "jk_Snake_Tail_End.h"
#include "jk_Sky.h"
#include "jk_Rock_small.h"
#include "jk_Move_GR.h""
#include "jk_Gameobject.h"
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
#include "jk_Cylinder.h"
#include "jk_Lttle_miniboss.h"
#include "jk_minibos_show.h"
#include "jk_Act1_Water.h"
#include "act1_waterfall1.h"
#include "act1_waterfall2.h"
#include "act1_waterfall3.h"
#include "act1_flower1.h"
#include "act1_flower2.h"

namespace jk
{
	PlayScene::PlayScene()
		: mSonic(nullptr)
		, dir(1)
		, Camera_Switch(0)
		, check_minibos(0)
		, frame_check(0)
	{
	
	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{	

	
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);
		mSonic->GetComponent<Transform>()->SetPos(Vector2{ 2790.0f * 3, 3200.f });
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 28821.f, 1363.f });//끝

		mTails = new Tails(mSonic);
		mTails->SetName(L"Player2");
		AddGameobeject(mTails, jk_LayerType::Player2);
		mTails->GetComponent<Transform>()->SetPos(Vector2{ 2790.0f * 3, 3200.f });		

	
	   //뒷배경
		Act1skyBG*  act1sky = new Act1skyBG();
		act1sky->SetName(L"SkyBG");
		AddGameobeject(act1sky, jk_LayerType::foreground);
		
		act1_forest1* forestup = new act1_forest1();
		forestup->SetName(L"fOREST1");
		AddGameobeject(forestup, jk_LayerType::foreground);

		acr1_forest2* forest2 = new acr1_forest2();		
		AddGameobeject(forest2, jk_LayerType::foreground);

		midlesky* msky = new midlesky();
		msky->SetName(L"msky");
		AddGameobeject(msky, jk_LayerType::foreground);
		
		Sky* sky = new Sky();
		sky->SetName(L"sky");
		AddGameobeject(sky, jk_LayerType::foreground);

		Act1_BG_object* bg = new Act1_BG_object();
		AddGameobeject(bg, jk_LayerType::BG);
		bg->SetName(L"Act1BG");		 
		bg->Set_Owner(mSonic);

		Act1_Water* act1_Water = new Act1_Water();
		AddGameobeject(act1_Water, jk_LayerType::Blend);
		act1_Water->SetName(L"act1_Water");
	
		act1_waterfall1* waterfall_1 = new act1_waterfall1();
		AddGameobeject(waterfall_1, jk_LayerType::BG);
		waterfall_1->SetName(L"waterfall_1");
		waterfall_1->GetComponent<Transform>()->SetPos(Vector2{ 8825.f,1147.f });

		act1_waterfall2* waterfall_2 = new act1_waterfall2();
		AddGameobeject(waterfall_2, jk_LayerType::BG);
		waterfall_2->SetName(L"waterfall_2");
		waterfall_2->GetComponent<Transform>()->SetPos(Vector2{ 21748.f,1363.f });

		act1_waterfall3* waterfall_3 = new act1_waterfall3();
		AddGameobeject(waterfall_3, jk_LayerType::BG);
		waterfall_3->SetName(L"waterfall_3");
		waterfall_3->GetComponent<Transform>()->SetPos(Vector2{ 29153.f,986.f });//986

		act1_flower1* flower1[8];
		for (int a = 0; a < 8; a++)
		{
			flower1[a] = new act1_flower1();
			flower1[a]->SetName(L"flower1");
			AddGameobeject(flower1[a], jk_LayerType::BG);
		}
		flower1[0]->GetComponent<Transform>()->SetPos(Vector2{ 12315.0f, 3380.0f });
		flower1[1]->GetComponent<Transform>()->SetPos(Vector2{ 12520.0f, 3380.0f });
		flower1[2]->GetComponent<Transform>()->SetPos(Vector2{ 14620.0f, 3000.0f });
		flower1[3]->GetComponent<Transform>()->SetPos(Vector2{ 14825.0f, 3000.0f });
		flower1[4]->GetComponent<Transform>()->SetPos(Vector2{ 16920.0f, 3775.0f });
		flower1[5]->GetComponent<Transform>()->SetPos(Vector2{ 17125.0f, 3775.0f });
		flower1[6]->GetComponent<Transform>()->SetPos(Vector2{ 23835.0f, 3765.0f });
		flower1[7]->GetComponent<Transform>()->SetPos(Vector2{ 24040.0f, 3765.0f });
		

		act1_flower2* flower2[3];
		for (int a = 0; a < 3; a++)
		{
			flower2[a] = new act1_flower2();
			flower2[a]->SetName(L"flower2");
			AddGameobeject(flower2[a], jk_LayerType::BG);
		}
		flower2[0]->GetComponent<Transform>()->SetPos(Vector2{ 13570.0f,3195.0f });
		flower2[1]->GetComponent<Transform>()->SetPos(Vector2{ 17700.0f, 3585.0f });
		flower2[2]->GetComponent<Transform>()->SetPos(Vector2{ 21640.0f, 3960.0f });

	



		//배경소품
		Spring_Up* spring_Up[2];
		for (int a = 0; a < 2; a++)
		{
			spring_Up[a] = new Spring_Up();
			spring_Up[a]->SetName(L"spring_Up");
			AddGameobeject(spring_Up[a], jk_LayerType::BG_props);
		}
		spring_Up[0]->GetComponent<Transform>()->SetPos(Vector2{ 13318.0f, 3224.0f });
		spring_Up[1]->GetComponent<Transform>()->SetPos(Vector2{ 13169.0f, 2808.0f });


		Spring_Left* spring_Left[3];
		for (int a = 0; a < 3; a++)
		{
			spring_Left[a] = new Spring_Left();
			spring_Left[a]->SetName(L"spring_Left");
			AddGameobeject(spring_Left[a], jk_LayerType::BG_props);
		}
		spring_Left[0]->GetComponent<Transform>()->SetPos(Vector2{ 14080.0f, 3135.0f });
		spring_Left[1]->GetComponent<Transform>()->SetPos(Vector2{ 17739.0f, 3615.0f });
		spring_Left[2]->GetComponent<Transform>()->SetPos(Vector2{ 18111.0f, 3515.0f });


		Rock_small* s_rock[3];
		for (int a = 0; a < 3; a++)
		{
			s_rock[a] = new Rock_small();
			s_rock[a]->SetName(L"s_rock");
			AddGameobeject(s_rock[a], jk_LayerType::BG_props);
		}
		s_rock[0]->GetComponent<Transform>()->SetPos(Vector2{ 13308.0f, 3174.0f });
		s_rock[0]->GetComponent<Collider>()->SetPos(Vector2{ 13308.0f, 3174.0f });
		s_rock[1]->GetComponent<Transform>()->SetPos(Vector2{ 19398.0f, 2766.0f });
		s_rock[1]->GetComponent<Collider>()->SetPos(Vector2{ 19398.0f, 2766.0f });
		s_rock[2]->GetComponent<Transform>()->SetPos(Vector2{ 25000.0f, 3340.0f });
		s_rock[1]->GetComponent<Collider>()->SetPos(Vector2{ 25000.0f, 3340.0f });


		Rock_middle* rock_middle[1];
		for (int a = 0; a < 1; a++)
		{
			rock_middle[a] = new Rock_middle();
			rock_middle[a]->SetName(L"rock_middle");
			AddGameobeject(rock_middle[a], jk_LayerType::BG_props);
		}
		rock_middle[0]->GetComponent<Transform>()->SetPos(Vector2{ 19611.0f, 2724.0f });


		Rock_big* rock_big[2];
		for (int a = 0; a < 2; a++)
		{
			rock_big[a] = new Rock_big();
			rock_big[a]->SetName(L"rock_big");
			AddGameobeject(rock_big[a], jk_LayerType::BG_props);
		}
		rock_big[0]->GetComponent<Transform>()->SetPos(Vector2{ 15993.0f, 3628.0f });
		rock_big[1]->GetComponent<Transform>()->SetPos(Vector2{ 19824.0f, 2625.0f });


		Collapses_Ground* collapses_Ground[1];
		for (int a = 0; a < 1; a++)
		{
			collapses_Ground[a] = new Collapses_Ground();
			collapses_Ground[a]->SetName(L"collapses_Ground");
			AddGameobeject(collapses_Ground[a], jk_LayerType::BG_props);
		}
		collapses_Ground[0]->GetComponent<Transform>()->SetPos(Vector2{ 16350.0f, 3070.0f });


		Jeep_line_Handle* jeep_line_Handle[3];
		for (int a = 0; a < 3; a++)
		{
			jeep_line_Handle[a] = new Jeep_line_Handle();
			jeep_line_Handle[a]->SetName(L"jeep_line_Handle");
			AddGameobeject(jeep_line_Handle[a], jk_LayerType::BG_props);
		}
		jeep_line_Handle[0]->GetComponent<Transform>()->SetPos(Vector2{ 16906.f, 2725.f });
		jeep_line_Handle[0]->SetCenterpos(Vector2{ 16906.f, 2725.f });
		jeep_line_Handle[0]->SetAngle(float{ 90 });
		jeep_line_Handle[0]->SetDirect(int{ -1 });
		jeep_line_Handle[1]->GetComponent<Transform>()->SetPos(Vector2{ 17621.f, 2725.f });
		jeep_line_Handle[1]->SetCenterpos(Vector2{ 17621.f, 2725.f });
		jeep_line_Handle[1]->SetAngle(float{ 90 });
		jeep_line_Handle[1]->SetDirect(int{ 1 });
		jeep_line_Handle[2]->GetComponent<Transform>()->SetPos(Vector2{ 18321.f, 2725.f });
		jeep_line_Handle[2]->SetCenterpos(Vector2{ 18321.f, 2725.f });
		jeep_line_Handle[2]->SetAngle(float{ 90 });
		jeep_line_Handle[2]->SetDirect(int{ -1 });
		


		Jeep_line* jeep_line[3];
		for (int a = 0; a < 3; a++)
		{
			jeep_line[a] = new Jeep_line(jeep_line_Handle[a]);
			jeep_line[a]->SetName(L"jeep_line");
			AddGameobeject(jeep_line[a], jk_LayerType::BG_props);
		}
		jeep_line[0]->GetComponent<Transform>()->SetPos(Vector2{ 16806.f, 2743.f });
		jeep_line[0]->SetCheck_JeepLine(jeep_line_Handle[0]);
		jeep_line[1]->GetComponent<Transform>()->SetPos(Vector2{ 17521.f, 2743.f });
		jeep_line[1]->SetCheck_JeepLine(jeep_line_Handle[1]);
		jeep_line[2]->GetComponent<Transform>()->SetPos(Vector2{ 18221.f, 2743.f });
		jeep_line[2]->SetCheck_JeepLine(jeep_line_Handle[2]);
	


		Move_GR* gr_move[3];
		for (int a = 0; a < 3; a++)
		{
			gr_move[a] = new Move_GR();
			gr_move[a]->SetName(L"gr_move");
			AddGameobeject(gr_move[a], jk_LayerType::BG_props);
		}
		gr_move[0]->GetComponent<Transform>()->SetPos(Vector2{ 12450.0f, 2444.0f });
		gr_move[0]->SetCenterpos(Vector2{ 12450.0f, 2444.0f });
		gr_move[0]->Setmaxdistance(float{ 100.f });
		gr_move[1]->GetComponent<Transform>()->SetPos(Vector2{ 14891.0f, 2989.0f });
		gr_move[1]->SetCenterpos(Vector2{ 14891.0f, 2989.0f });
		gr_move[1]->Setmaxdistance(float{ 500.f });
		gr_move[2]->GetComponent<Transform>()->SetPos(Vector2{ 14691.0f, 2189.0f });
		gr_move[2]->SetCenterpos(Vector2{ 14691.0f, 2189.0f });
		gr_move[2]->Setmaxdistance(float{ 300.f });



		Spike_Up* spike_Up[4];
		for (int a = 0; a < 4; a++)
		{
			spike_Up[a] = new Spike_Up();
			spike_Up[a]->SetName(L"spike_Up");
			AddGameobeject(spike_Up[a], jk_LayerType::BG_props);
		}
		spike_Up[0]->GetComponent<Transform>()->SetPos(Vector2{ 15621.0f, 2950.0f });
		spike_Up[1]->GetComponent<Transform>()->SetPos(Vector2{ 16032.0f, 2950.0f });
		spike_Up[2]->GetComponent<Transform>()->SetPos(Vector2{ 19101.0f, 1858.0f });
		spike_Up[3]->GetComponent<Transform>()->SetPos(Vector2{ 19532.0f, 1858.0f });



		Cylinder* cylinder =  new Cylinder();
		cylinder->SetName(L"cylinder");
		AddGameobeject(cylinder, jk_LayerType::BG_props);
		cylinder->GetComponent<Transform>()->SetPos(Vector2{ 28085.0f, 2510.0f });

		//StageSave* save = new StageSave;
		//save->SetName(L"StageSave");




		//몬스터
		Monster* mRino[3];
		for (int a = 0; a <3; a++)
		{
			mRino[a] = new Monster();
			mRino[a]->SetName(L"RinoMonster");
			AddGameobeject(mRino[a], jk_LayerType::Monster);
		}
		mRino[0]->GetComponent<Transform>()->SetPos(Vector2{ 14524.0f, 3021.0f });
		mRino[0]->SetCenterpos(Vector2{ 14524.0f, 3021.0f });
		mRino[1]->GetComponent<Transform>()->SetPos(Vector2{ 18126.0f, 1770.0f });
		mRino[1]->SetCenterpos(Vector2{ 18126.0f, 1770.0f });
		mRino[2]->GetComponent<Transform>()->SetPos(Vector2{ 24332.0f, 2417.0f });
		mRino[2]->SetCenterpos(Vector2{ 24332.0f, 2417.0f });

	
		
		Monkey* mMokey[5];
		for (int a = 0; a < 5; a++)
		{
			mMokey[a] = new Monkey(mSonic);
			mMokey[a]->SetName(L"Monkey");
			AddGameobeject(mMokey[a], jk_LayerType::Monster);
		}
		//mMokey[0]->GetComponent<Transform>()->SetPos(Vector2{ 12450.0f, 3111.0f }); 오른쪽 원숭이
		mMokey[0]->GetComponent<Transform>()->SetPos(Vector2{ 12280.0f, 3111.0f });
		mMokey[0]->SetCenterpos(Vector2{ 12280.f,3111.f });
		mMokey[1]->GetComponent<Transform>()->SetPos(Vector2{ 16865.0f, 3503.0f });
		mMokey[1]->SetCenterpos(Vector2{ 16865.0f, 3503.0f });
		mMokey[2]->GetComponent<Transform>()->SetPos(Vector2{ 18410.0f, 1550.0f });
		mMokey[2]->SetCenterpos(Vector2{ 18410.0f, 1550.0f });
		mMokey[3]->GetComponent<Transform>()->SetPos(Vector2{ 23796.0f, 3463.0f });
		mMokey[3]->SetCenterpos(Vector2{ 23796.0f, 3463.0f });
		mMokey[4]->GetComponent<Transform>()->SetPos(Vector2{ 23395.0f, 2350.0f });
		mMokey[4]->SetCenterpos(Vector2{ 23395.0f, 2350.0f });


		Cannon* cannon[3];
		for (int a = 0; a < 3; a++)
		{
			cannon[a] = new Cannon(mSonic);
			cannon[a]->SetName(L"Cannon");
			AddGameobeject(cannon[a], jk_LayerType::Monster);
		}
		cannon[0]->GetComponent<Transform>()->SetPos(Vector2{ 13518.0f, 3174.0f });
		cannon[1]->GetComponent<Transform>()->SetPos(Vector2{ 16563.0f, 1887.0f });
		cannon[2]->GetComponent<Transform>()->SetPos(Vector2{ 20928.0f, 2680.0f });



		Snake* Snake_head[1];
		for (int a = 0; a < 1; a++)
		{
			Snake_head[a] = new Snake(mSonic);
			Snake_head[a]->SetName(L"Snake_head");
			AddGameobeject(Snake_head[a], jk_LayerType::Monster);
		}
		Snake_head[0]->GetComponent<Transform>()->SetPos(Vector2{ 8370.f, 3250.f });

		Snake_Body_Smoke* snake_Body_Smoke[1];
		for (int a = 0; a < 1; a++)
		{
			snake_Body_Smoke[a] = new Snake_Body_Smoke();
			snake_Body_Smoke[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_Body_Smoke[a], jk_LayerType::Monster);
		}
		snake_Body_Smoke[0]->GetComponent<Transform>()->SetPos(Vector2{ 8370.f, 3250.f });
		snake_Body_Smoke[0]->Set_Snake_Body(Snake_head[0]);
	

		Snake_Body* snake_body[1];
		for (int a = 0; a < 1; a++)
		{
			snake_body[a] = new Snake_Body();
			snake_body[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_body[a], jk_LayerType::Monster);
		}
		snake_body[0]->GetComponent<Transform>()->SetPos(Vector2{ 8370.f, 3250.f });
		snake_body[0]->Set_Snake_Body(snake_Body_Smoke[0]);
				

		Snake_body2* snake_body_2 = new Snake_body2();
		snake_body_2->SetName(L"Snake_Body2");
		AddGameobeject(snake_body_2, jk_LayerType::Monster);
		snake_body_2->GetComponent<Transform>()->SetPos(Vector2{ 8370.f, 3250.f });
		snake_body_2->Set_Snake_body_third(snake_body[0]);	


		Snake_mTaIl* snake_mT[1];
		for (int a = 0; a < 1; a++)
		{
			snake_mT[a] = new Snake_mTaIl();
			snake_mT[a]->SetName(L"Snake_Body");
			AddGameobeject(snake_mT[a], jk_LayerType::Monster);
		}
		snake_mT[0]->GetComponent<Transform>()->SetPos(Vector2{8370.f, 3250.f});
		snake_mT[0]->Set_Snake_body_third(snake_body_2);



		Snake_Tail_End* Snake_Tail[1];
		for (int a = 0; a < 1; a++)
		{
			Snake_Tail[a] = new Snake_Tail_End();
			Snake_Tail[a]->SetName(L"Snake_Body");
			AddGameobeject(Snake_Tail[a], jk_LayerType::Monster);
		}
		Snake_Tail[0]->GetComponent<Transform>()->SetPos(Vector2{ 8370.f, 3250.f });
		Snake_Tail[0]->Set_Snake_body_third(snake_mT[0]);


		
		//원체크
		check1* circle_chek = new check1();
		AddGameobeject(circle_chek, jk_LayerType::Player2);

		check2* circle_chek2 = new check2();
		AddGameobeject(circle_chek2, jk_LayerType::Player2);

		Ground* playgr = new Ground();
		playgr->SetName(L"Ground");
		playgr->SetPlayer(mSonic, mTails);
		AddGameobeject(playgr, jk_LayerType::Ground);


	
		mSonic->SetCheckTargetGround(playgr);
		mTails->SetCheckTargetGround(playgr);
		
	
		s_rock[0]->SetCheckTargetGround(playgr);
		s_rock[1]->SetCheckTargetGround(playgr); 
		s_rock[2]->SetCheckTargetGround(playgr);
		rock_middle[0]->SetCheckTargetGround(playgr);
		rock_big[0]->SetCheckTargetGround(playgr);
		rock_big[1]->SetCheckTargetGround(playgr);
		cannon[0]->SetCheckTargetGround(playgr);
		cannon[1]->SetCheckTargetGround(playgr);
		cannon[2]->SetCheckTargetGround(playgr);
		mRino[0]->SetCheckTargetGround(playgr);
		mRino[1]->SetCheckTargetGround(playgr);
		mRino[2]->SetCheckTargetGround(playgr);
		mMokey[0]->SetCheckTargetGround(playgr);
		mMokey[1]->SetCheckTargetGround(playgr);
		mMokey[2]->SetCheckTargetGround(playgr);
		mMokey[3]->SetCheckTargetGround(playgr);
		mMokey[4]->SetCheckTargetGround(playgr);
		circle_chek->SetCheckTargetGround(playgr);
		circle_chek2->SetCheckTargetGround(playgr);	

		//빅링위치
		ItemBigRing* Big_Ring = new ItemBigRing();
		Big_Ring->SetName(L"BIGRING");
		AddGameobeject(Big_Ring, jk_LayerType::Item);
		Big_Ring->GetComponent<Transform>()->SetPos(Vector2(15064.f, 3680.0f));


		//링위치
		Ring* ring[22];
		for (int a = 0; a < 22; a++)
		{
			ring[a] = new Ring(mSonic);
			AddGameobeject(ring[a], jk_LayerType::Rings);
		}				
		ring[0]->GetComponent<Transform>()->SetPos(Vector2{ 11276.0f, 3056.0f});	
		ring[1]->GetComponent<Transform>()->SetPos(Vector2{ 11376.0f, 3056.0f});
		ring[2]->GetComponent<Transform>()->SetPos(Vector2{ 11476.0f, 3056.0f });
		ring[3]->GetComponent<Transform>()->SetPos(Vector2{ 11712.0f, 3161.0f });
		ring[4]->GetComponent<Transform>()->SetPos(Vector2{ 11812.0f, 3211.0f });
		ring[5]->GetComponent<Transform>()->SetPos(Vector2{ 11912.0f, 3261.0f });
		ring[6]->GetComponent<Transform>()->SetPos(Vector2{ 12012.0f, 3311.0f });
		ring[7]->GetComponent<Transform>()->SetPos(Vector2{ 12112.0f, 3361.0f });
		ring[8]->GetComponent<Transform>()->SetPos(Vector2{ 12627.f, 3405.f });
		ring[9]->GetComponent<Transform>()->SetPos(Vector2{ 12727.f, 3355.f });
		ring[10]->GetComponent<Transform>()->SetPos(Vector2{ 12797.f, 3285.f });
		ring[11]->GetComponent<Transform>()->SetPos(Vector2{ 13687.f, 3208.f });
		ring[12]->GetComponent<Transform>()->SetPos(Vector2{ 13787.f, 3208.f });
		ring[13]->GetComponent<Transform>()->SetPos(Vector2{ 13887.f, 3208.f });
		ring[14]->GetComponent<Transform>()->SetPos(Vector2{ 17232.f, 3783.f });
		ring[15]->GetComponent<Transform>()->SetPos(Vector2{ 17332.f, 3733.f });
		ring[16]->GetComponent<Transform>()->SetPos(Vector2{ 17432.f, 3683.f });
		ring[17]->GetComponent<Transform>()->SetPos(Vector2{ 20013.f, 3376.f });
		ring[18]->GetComponent<Transform>()->SetPos(Vector2{ 20092.f, 3226.f });
		ring[19]->GetComponent<Transform>()->SetPos(Vector2{ 20258.f, 3163.f });
		ring[20]->GetComponent<Transform>()->SetPos(Vector2{ 20426.f, 3225.f });
		ring[21]->GetComponent<Transform>()->SetPos(Vector2{ 20498.f, 3379.f });
		


		Scene::Initialize();		
	}

	void PlayScene::Update()
	{

		frame_check = 1;

		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();
		
		if (sonic_pos.x >= 29720.f)
		{
			Camera_Switch = 1;
		}
		if (Camera_Switch == 1)
		{
			//Camera::SetTarget(nullptr);
			Camera::SetCamera(1);
			if (sonic_pos.x >= 30400.f)
			{
				Camera::SetTarget(nullptr);
				if (check_minibos == 0)
				{
					if (check_minibos != 0)
						return;

					Create_Miniboss_show();
					check_minibos = 1;
				}
			}
		}
		
		Scene::Update();		
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::GamePlay2);			
			CreateBlending();
		}
	}  

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}

	void PlayScene::OnEnter()
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
		CollisionManager::SetLayer(jk_LayerType::Player, jk_LayerType::Blend, true);
		
		if (Camera_Switch == 0)
		{
		Camera::SetTarget(mSonic);
		}
		
	}

	void PlayScene::OnExit()
	{ 
		//mSonic->SetPos(Vector2{ 0.0f, 0.0f }); (씬넘길때 원상복귀 시키는것(매스와 지금 문제가 이써안됨)	
		Camera::Clear();
	}

	void PlayScene::CreateBlending()
	{	
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}

	void PlayScene::Create_Miniboss_show()
	{
		minibos_show* mbos_show = new minibos_show();
		mbos_show->SetName(L"mbos_show");
		AddGameobeject(mbos_show, jk_LayerType::MiniBoss);
		mbos_show->GetComponent<Transform>()->SetPos(Vector2{ 30792.f, 2407.f });	

		//= new Lttle_miniboss();
		//little_miniboss->SetName(L"little_miniboss");
		//little_miniboss->GetComponent<Transform>()->SetPos(Vector2{ 30652.f, 2517.f });
		//curScene[3]->AddGameobeject(little_miniboss, jk_LayerType::Player);

		Lttle_miniboss* little_miniboss[3];
		for (int a = 0; a < 3; a++)
		{
			little_miniboss[a] = new Lttle_miniboss();
			little_miniboss[a]->SetName(L"little_miniboss");
			AddGameobeject(little_miniboss[a], jk_LayerType::MiniBoss);
		}
		little_miniboss[0] -> GetComponent<Transform>()->SetPos(Vector2{ 30352.f, 2267.f });
		little_miniboss[0]->SetCenterpos(Vector2{ 30652.f, 2517.f });
		little_miniboss[1] -> GetComponent<Transform>()->SetPos(Vector2{ 30252.f, 2367.f });
		little_miniboss[1]->SetCenterpos(Vector2{ 30552.f, 2467.f });
		little_miniboss[2] -> GetComponent<Transform>()->SetPos(Vector2{ 30302.f, 2167.f });	
		little_miniboss[2]->SetCenterpos(Vector2{ 30602.f, 2617.f });

	}
}
