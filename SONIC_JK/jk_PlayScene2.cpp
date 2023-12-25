#include "jk_PlayScene2.h"
#include "jk_PlayScene.h"
#include "jk_Input.h"
#include "jk_SceneManager.h"
#include "jk_Camera.h"
#include "jk_CollisionManager.h"
#include "jk_Object.h"
#include "jk_Transform.h"
#include "jk_Blending.h"
#include "Rigidbody.h"

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
#include "jk_Gameobject.h"
#include "jk_Resources.h"
#include "Act1_2_Boss_wall.h"



#include "jk_Act1_2_BG.h"
#include "Act1_2_sky1.h"
#include "Act1_2_sky2.h"
#include "Act1_2_sky3.h"
#include "Act1_2_sky4.h"
#include "Act1_2_sky5.h"
#include "jk_check_circle.h"
#include "act2_waterfall1.h"
#include "act2_waterfall_2.h"
#include "act2_waterfall3.h"
#include "act1_flower1.h"
#include "act1_flower2.h"
#include "act2_water.h"


#include "jk_Rock_small.h"
#include "jk_Move_GR.h"
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
#include "jk_Item_Elect.h"
#include "jk_Item_water.h"
#include "jk_Item_Fire.h"
#include "jk_StageSave.h"
#include "jk_ItemBigRing.h"


#include "jk_Miniboss.h"


#include "jk_Rino.h"
#include "jk_Monkey.h"
#include "jk_Cannon.h"

#include "jk_Snake.h"
#include "jk_Snake_Head.h"
#include "jk_Snake_First_Body.h"
#include "jk_Snake_Second_Body.h"
#include "jk_Snake_Third_Body.h"
#include "jk_Snake_Last_Body.h"
#include "jk_Snake_Tail.h"

namespace jk
{
	PlayScene2::PlayScene2()
		: mSonic(nullptr)
		, playgr(nullptr)
		, Act2_music(nullptr)
		, Miniboss2(nullptr)
		, dir(1)
		, check_map(0)
		, Camera_Switch(0)
		, check_minibos(0)
		, frame_check(0)
	{
	}
	PlayScene2::~PlayScene2()
	{
	}
	void PlayScene2::Initialize()
	{
		check_map = 1;
		Act2_music = Resources::Load<Sound>(L"Act2_bg", L"..\\Resources\\Sound\\Act2_bg.wav");
		Miniboss2 = Resources::Load<Sound>(L"Miniboss2", L"..\\Resources\\Sound\\Miniboss2.wav");


		//캐릭터
		mSonic = new Sonic();
		mSonic->SetName(L"Player");
		AddGameobeject(mSonic, jk_LayerType::Player);
		
		mSonic->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f)); //시작위치
		//mSonic->GetComponent<Transform>()->SetPos(Vector2(11700.f, 3770.f)); //보스전

		//mSonic->GetComponent<Transform>()->SetPos(Vector2(7755.0f, 5070.0f));//워터시작
		//mSonic->GetComponent<Transform>()->SetPos(Vector2{ 13100.f,3240.f }); //미니 보스

		//mSonic->GetComponent<Transform>()->SetPos(Vector2(6450.f, 2940.f)); //집라인 시작
		//mSonic->GetComponent<Transform>()->SetPos(Vector2(7680.0f, 3660.0f)); //rino위치
		//mSonic->GetComponent<Transform>()->SetPos(Vector2(8712.f, 3396.f)); //집라인 끝위치
		//mSonic->GetComponent<Transform>()->SetPos(Vector2(3993.f, 1775.f)); //상부배경확인
		// 
		//13770.f, 2880.f
		//8712.f, 3396.f

		Tails* tails = new Tails(mSonic);
		tails->SetName(L"Player2");
		AddGameobeject(tails, jk_LayerType::Player2);
		tails->GetComponent<Transform>()->SetPos(Vector2(661.f, 3033.f));


		playgr = new Pixel_Ground();
		playgr->SetName(L"Ground2");
		playgr->SetPlayer(mSonic, tails);
		AddGameobeject(playgr, jk_LayerType::Ground);
		mSonic->SetCheckTargetGround(playgr);
		tails->SetCheckTargetGround(playgr);
		playgr->Set_Circle_Center(Vector2{ 9500.f, 3605.f });


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





		//아이템
		//ItemBigRing* Big_Ring = new ItemBigRing();
		//Big_Ring->SetName(L"BIGRING");

		//jk_Item_Elect* items = new jk_Item_Elect(mSonic);
		//items->SetName(L"items");
		//AddGameobeject(items, jk_LayerType::jk_Item_Elect);
		//items->GetComponent<Transform>()->SetPos(Vector2(800.f, 3150.f));


		//Item_water* water_item = new Item_water(mSonic);
		//water_item->SetName(L"items");
		//AddGameobeject(water_item, jk_LayerType::jk_Item_Elect);
		//water_item->GetComponent<Transform>()->SetPos(Vector2(1100.f, 3150.f));


		//Item_Fire* fire_item = new Item_Fire(mSonic);
		//fire_item->SetName(L"items");
		//AddGameobeject(fire_item, jk_LayerType::jk_Item_Elect);
		//fire_item->GetComponent<Transform>()->SetPos(Vector2(1400.f, 3150.f));


		//배경
		Act1_2_BG* act1_2_BG = new Act1_2_BG();
		act1_2_BG->SetName(L"act1_2_BG");
		AddGameobeject(act1_2_BG, jk_LayerType::BG);


		Act1_2_sky1* sky = new Act1_2_sky1();
		sky->SetName(L"act1_2_sky1");
		AddGameobeject(sky, jk_LayerType::foreground);
		sky->GetComponent<Transform>()->SetPos(Vector2(100.f, 1465.f));


		Act1_2_sky1* act1_2_sky = new Act1_2_sky1();
		act1_2_sky->SetName(L"act1_2_sky1");
		AddGameobeject(act1_2_sky, jk_LayerType::foreground);
		act1_2_sky->GetComponent<Transform>()->SetPos(Vector2(200.f, 1510.f));


		Act1_2_sky1* act1_2_sky0 = new Act1_2_sky1();
		act1_2_sky0->SetName(L"act1_2_sky1");
		AddGameobeject(act1_2_sky0, jk_LayerType::foreground);
		act1_2_sky0->GetComponent<Transform>()->SetPos(Vector2(300.f, 1555.f));


		Act1_2_sky1* act1_2_sky1 = new Act1_2_sky1();
		act1_2_sky1->SetName(L"act1_2_sky1");
		AddGameobeject(act1_2_sky1, jk_LayerType::foreground);
		act1_2_sky1->GetComponent<Transform>()->SetPos(Vector2(400.f, 1600.f));


		Act1_2_sky1* act1_2_sky1_1 = new Act1_2_sky1();
		act1_2_sky1_1->SetName(L"act1_2_sky1");
		AddGameobeject(act1_2_sky1_1, jk_LayerType::foreground);
		act1_2_sky1_1->GetComponent<Transform>()->SetPos(Vector2(500.f, 1645.f));


		Act1_2_sky2* act1_2_sky2 = new Act1_2_sky2();
		act1_2_sky2->SetName(L"act2_sky2");
		AddGameobeject(act1_2_sky2, jk_LayerType::foreground);
		act1_2_sky2->GetComponent<Transform>()->SetPos(Vector2(500.f, 1690.f));


		Act1_2_sky2* act1_2_sky2_1 = new Act1_2_sky2();
		act1_2_sky2_1->SetName(L"act2_sky2");
		AddGameobeject(act1_2_sky2_1, jk_LayerType::foreground);
		act1_2_sky2_1->GetComponent<Transform>()->SetPos(Vector2(500.f, 2287.f));//2386.5

		//448.5
		Act1_2_sky2* act1_2_sky2_2 = new Act1_2_sky2();
		act1_2_sky2_2->SetName(L"act2_sky2");
		AddGameobeject(act1_2_sky2_2, jk_LayerType::foreground);
		act1_2_sky2_2->GetComponent<Transform>()->SetPos(Vector2(500.f, 2735.f));//3236,897


		Act1_2_sky3* act1_2_sky3 = new Act1_2_sky3();
		act1_2_sky3->SetName(L"act1_2_sky3");
		AddGameobeject(act1_2_sky3, jk_LayerType::foreground);
		act1_2_sky3->GetComponent<Transform>()->SetPos(Vector2(500.f, 3632.f));//3484


		Act1_2_sky4* act1_2_sky4 = new Act1_2_sky4();
		act1_2_sky4->SetName(L"act1_2_sky4");
		AddGameobeject(act1_2_sky4, jk_LayerType::foreground);
		act1_2_sky4->GetComponent<Transform>()->SetPos(Vector2(500.f,3872.f));//4172.5


		Act1_2_sky5* act1_2_sky5 = new Act1_2_sky5();
		act1_2_sky5->SetName(L"act1_2_sky5");
		AddGameobeject(act1_2_sky5, jk_LayerType::foreground);
		act1_2_sky5->GetComponent<Transform>()->SetPos(Vector2(500.f, 4304.f));
		

		act2_waterfall1* waterfall_1 = new act2_waterfall1();
		AddGameobeject(waterfall_1, jk_LayerType::BG);
		waterfall_1->SetName(L"waterfall_1");
		waterfall_1->GetComponent<Transform>()->SetPos(Vector2{ 304.f,2987.f });//56/968

	
		act2_waterfall_2* waterfall_2 = new act2_waterfall_2();
		AddGameobeject(waterfall_2, jk_LayerType::BG);
		waterfall_2->SetName(L"waterfall_2");
		waterfall_2->GetComponent<Transform>()->SetPos(Vector2{ 4490.f,3009.f });//1432,710

		
		act2_waterfall3* waterfall_3 = new act2_waterfall3();
		AddGameobeject(waterfall_3, jk_LayerType::BG);
		waterfall_3->SetName(L"waterfall_3");
		waterfall_3->GetComponent<Transform>()->SetPos(Vector2{ 6922.f,3265.f });//2200,838


		act2_water* act2_Water = new act2_water();
		AddGameobeject(act2_Water, jk_LayerType::Blend);
		act2_Water->SetName(L"act2_Water");


		act1_flower1* flower1[6];
		for (int a = 0; a < 6; a++)
		{
			flower1[a] = new act1_flower1();
			flower1[a]->SetName(L"flower1");
			AddGameobeject(flower1[a], jk_LayerType::BG);
		}
		flower1[0]->GetComponent<Transform>()->SetPos(Vector2{5025.0f, 4965.0f });
		flower1[1]->GetComponent<Transform>()->SetPos(Vector2{ 5325.0f, 4965.0f });
		flower1[2]->GetComponent<Transform>()->SetPos(Vector2{ 7755.0f, 5070.0f });
		flower1[3]->GetComponent<Transform>()->SetPos(Vector2{ 8055.0f, 5070.0f });
		flower1[4]->GetComponent<Transform>()->SetPos(Vector2{ 13155.0f, 3330.0f });
		flower1[5]->GetComponent<Transform>()->SetPos(Vector2{ 13455.0f, 3330.0f });

	
		//배경소품
		StageSave* save = new StageSave();
		save->SetName(L"StageSave");
		AddGameobeject(save, jk_LayerType::BG_props);
		save->GetComponent<Transform>()->SetPos(Vector2(2208.f, 2818.f));





		//집라인 
		Jeepline_play* jeepline = new Jeepline_play();
		jeepline->SetName(L"jeepline");
		AddGameobeject(jeepline, jk_LayerType::BG_props);
		jeepline->GetComponent<Transform>()->SetPos(Vector2(6580.f, 2940.f));
		jeepline->Set_StartArea(Vector2{ 6580.f, 2940.f });
		jeepline->Set_FinalArea(Vector2{ 8715.f, 3460.f });
			

		//집라인 멈추게하는 역할로 만들어봄
		Clean_wall* clean_wall = new Clean_wall();
		clean_wall->SetName(L"clean_wall");
		AddGameobeject(clean_wall, jk_LayerType::BG_props);
		clean_wall->GetComponent<Transform>()->SetPos(Vector2(8712.f, 3396.f));
		
		//원돌기
		//check_circle* Check_circle = new check_circle();
		//Check_circle->SetName(L"clean_wall");
		//AddGameobeject(clean_wall, jk_LayerType::BG_props);
		//Check_circle->GetComponent<Transform>()->SetPos(Vector2{ 9012.f, 3500.f });

		//돌댕이
		//Rock_big* rock_big[1];
		//for (int a = 0; a < 1; a++)
		//{
		//	rock_big[a] = new Rock_big();
		//	rock_big[a]->SetName(L"rock_big");
		//	AddGameobeject(rock_big[a], jk_LayerType::BG_props);
		//}
		//rock_big[0]->GetComponent<Transform>()->SetPos(Vector2{ 2096.0f, 3363.0f });
		//rock_big[0]->SetCheckTargetGround(playgr);


		Collapses_Ground* collapses_Ground[5];
		for (int a = 0; a < 5; a++)
		{
			collapses_Ground[a] = new Collapses_Ground();
			collapses_Ground[a]->SetName(L"collapses_Ground");
			AddGameobeject(collapses_Ground[a], jk_LayerType::Ground);
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
			AddGameobeject(collapses_GR_left[a], jk_LayerType::Ground);
		}
		collapses_GR_left[0]->GetComponent<Transform>()->SetPos(Vector2{ 4825.0f, 3410.0f });
		collapses_GR_left[1]->GetComponent<Transform>()->SetPos(Vector2{ 7125.f, 3980.f });
		collapses_GR_left[2]->GetComponent<Transform>()->SetPos(Vector2{ 8490.f, 3800.f });
		collapses_GR_left[3]->GetComponent<Transform>()->SetPos(Vector2{ 11550.f, 3210.f });
		

		Spring_Up* spring_Up[6];
		for (int a = 0; a < 6; a++)
		{
			spring_Up[a] = new Spring_Up();
			spring_Up[a]->SetName(L"spring_Up");
			AddGameobeject(spring_Up[a], jk_LayerType::Ground);
		}
		spring_Up[0]->GetComponent<Transform>()->SetPos(Vector2{ 3624.0f, 3381.0f });
		spring_Up[1]->GetComponent<Transform>()->SetPos(Vector2{ 1750.0f, 4558.0f });
		spring_Up[2]->GetComponent<Transform>()->SetPos(Vector2{ 5550.0f, 5000.0f });
		spring_Up[3]->GetComponent<Transform>()->SetPos(Vector2{ 10248.0f, 4812.0f });
		spring_Up[4]->GetComponent<Transform>()->SetPos(Vector2{ 11300.0f, 4400.0f });
		spring_Up[5]->GetComponent<Transform>()->SetPos(Vector2{ 11700.f,3770.f });

		Move_GR* gr_move[1];
		for (int a = 0; a < 1; a++)
		{
			gr_move[a] = new Move_GR();
			gr_move[a]->SetName(L"gr_move");
			AddGameobeject(gr_move[a], jk_LayerType::Ground);
		}
		gr_move[0]->GetComponent<Transform>()->SetPos(Vector2{ 9714.f,5346.f });
		gr_move[0]->SetCenterpos(Vector2{ 9714.f,5346.f });
		gr_move[0]->Setmaxdistance(float{ 150.f });


		ItemBigRing* Big_Ring = new ItemBigRing();
		Big_Ring->SetName(L"BIGRING");
		AddGameobeject(Big_Ring, jk_LayerType::Item);
		Big_Ring->GetComponent<Transform>()->SetPos(Vector2(1745.f, 3570.0f));


		//몬스터 및 보스
		Rino* mRino = new Rino();
		mRino->SetName(L"RinoMonster2");
		AddGameobeject(mRino, jk_LayerType::Monster);
		mRino->GetComponent<Transform>()->SetPos(Vector2{6450.0f,4350.0f });
		mRino->SetCenterpos(Vector2{ 6540.0f, 4350.0f });
		mRino->SetCheckTargetGround(playgr);


		Rino* mRino1 = new Rino();
		mRino1->SetName(L"RinoMonster2-1");
		AddGameobeject(mRino1, jk_LayerType::Monster);
		mRino1->GetComponent<Transform>()->SetPos(Vector2{ 7680.0f, 3660.0f });
		mRino1->SetCenterpos(Vector2{ 7680.0f, 3660.0f });
		mRino1->SetCheckTargetGround(playgr);


		Cannon* cannon[1];
		for (int a = 0; a < 1; a++)
		{
			cannon[a] = new Cannon(mSonic);
			cannon[a]->SetName(L"Cannon");
			AddGameobeject(cannon[a], jk_LayerType::Monster);
		}	
		cannon[0]->GetComponent<Transform>()->SetPos(Vector2{ 10785.0f, 3225.0f });
		cannon[0]->SetCheckTargetGround(playgr);



		mSnake = new Snake(Vector2{ 6270.f, 3210.f });
		mSnake->SetLife(false);
		AddGameobeject(mSnake, jk_LayerType::Monster);
		mSnake->SetName(L"Snake_one");

	


		//Boss* ROBOT = new Boss(mSonic);
		//ROBOT->SetName(L"BOSS");
		//링위치
		Ring* ring[100];
		for (int a = 0; a < 100; a++)
		{
			ring[a] = new Ring(mSonic);
			AddGameobeject(ring[a], jk_LayerType::Rings);
		}
		ring[0]->GetComponent<Transform>()->SetPos(Vector2{ 2850.0f, 2910.0f });
		ring[1]->GetComponent<Transform>()->SetPos(Vector2{ 2950.0f, 2960.0f });
		ring[2]->GetComponent<Transform>()->SetPos(Vector2{ 3050.0f, 3010.0f });
		ring[3]->GetComponent<Transform>()->SetPos(Vector2{ 4450.0f, 3030.0f });
		ring[4]->GetComponent<Transform>()->SetPos(Vector2{ 4550.0f, 3030.0f });
		ring[5]->GetComponent<Transform>()->SetPos(Vector2{ 4650.0f, 3030.0f });
		ring[6]->GetComponent<Transform>()->SetPos(Vector2{ 5550.0f, 3300.0f });
		ring[7]->GetComponent<Transform>()->SetPos(Vector2{ 5650.0f, 3350.0f });
		ring[8]->GetComponent<Transform>()->SetPos(Vector2{ 5750.0f, 3400.0f });


		//집라인
		ring[9]->GetComponent<Transform>()->SetPos(Vector2{ 6750.f, 3120.f });
		ring[10]->GetComponent<Transform>()->SetPos(Vector2{ 6950.f, 3160.f });
		ring[11]->GetComponent<Transform>()->SetPos(Vector2{ 7150.f, 3220.f });
		ring[12]->GetComponent<Transform>()->SetPos(Vector2{ 7350.f, 3260.f });
		ring[13]->GetComponent<Transform>()->SetPos(Vector2{ 7550.f, 3300.f });
		ring[14]->GetComponent<Transform>()->SetPos(Vector2{ 7750.f, 3340.f });
		ring[15]->GetComponent<Transform>()->SetPos(Vector2{ 7950.f, 3380.f });
		ring[16]->GetComponent<Transform>()->SetPos(Vector2{ 8150.f, 3420.f });
		ring[17]->GetComponent<Transform>()->SetPos(Vector2{ 8350.f, 3460.f });
		ring[18]->GetComponent<Transform>()->SetPos(Vector2{ 8550.f, 3500.f });


		//원
		ring[19]->GetComponent<Transform>()->SetPos(Vector2{ 9810.f, 3870.f });
		ring[20]->GetComponent<Transform>()->SetPos(Vector2{9885.f, 3720.f });
		ring[21]->GetComponent<Transform>()->SetPos(Vector2{ 9810.f, 3570.f });
		ring[22]->GetComponent<Transform>()->SetPos(Vector2{9660.f, 3510.f });
		ring[23]->GetComponent<Transform>()->SetPos(Vector2{ 9510.f, 3570.f });
		ring[24]->GetComponent<Transform>()->SetPos(Vector2{ 9420.f, 3720.f });
		ring[25]->GetComponent<Transform>()->SetPos(Vector2{ 9465.f, 3870.f });


		ring[26]->GetComponent<Transform>()->SetPos(Vector2{ 10930.f, 4280.f });
		ring[27]->GetComponent<Transform>()->SetPos(Vector2{ 11030.f, 4330.f });
		ring[28]->GetComponent<Transform>()->SetPos(Vector2{ 11130.f, 4380.f });
		ring[29]->GetComponent<Transform>()->SetPos(Vector2{ 11305.f, 2955.f });
		ring[30]->GetComponent<Transform>()->SetPos(Vector2{ 11405.f, 2955.f });
		ring[31]->GetComponent<Transform>()->SetPos(Vector2{ 11505.f, 2955.f });
		ring[32]->GetComponent<Transform>()->SetPos(Vector2{ 12105.f, 3120.f });
		ring[33]->GetComponent<Transform>()->SetPos(Vector2{ 12205.f, 3170.f });
		ring[34]->GetComponent<Transform>()->SetPos(Vector2{ 12305.f, 3220.f });


		ring[35]->GetComponent<Transform>()->SetPos(Vector2{ 7785.f, 5070.f });
		ring[36]->GetComponent<Transform>()->SetPos(Vector2{ 7885.f, 5070.f });
		ring[37]->GetComponent<Transform>()->SetPos(Vector2{ 7985.f, 5070.f });
		

		ring[38]->GetComponent<Transform>()->SetPos(Vector2{ 9000.f, 5415.f });
		ring[39]->GetComponent<Transform>()->SetPos(Vector2{ 9100.f, 5465.f });
		ring[40]->GetComponent<Transform>()->SetPos(Vector2{ 9200.f, 5515.f });

		Scene::Initialize();
	}

	void PlayScene2::Update()
	{
		playgr->Set_map_check(check_map);
		playgr->Set_Circle_Center(Vector2{ 9600.f, 3705.f });


		if (Input::GetKeyDown(eKeyCode::M))
		{
			mSonic->GetComponent<Transform>()->SetPos(Vector2(8712.f, 3396.f));
			mSonic->GetComponent<Rigidbody>()->SetGravity(Vector2{ 0.f,1000.f });
			mSonic->GetComponent<Rigidbody>()->SetFiction(100.f);
			playgr->SetLotation(0);
			Sonic::eSonicState::Idle;
		}


		Vector2 sonic_pos = mSonic->GetComponent<Transform>()->GetPos();

		if (sonic_pos.x >= 2160.f)
		{
			Camera::SetCamera(0);
		}

		if (sonic_pos.x >= 13370.f)
		{
			Camera_Switch = 1;
		}
		if (Camera_Switch == 1)
		{
			Camera::SetCamera(1);
			Camera::SetTarget(nullptr);
			if (check_minibos == 0)
			{
				if (check_minibos != 0)
					return;
				Act2_music->Stop(true);
				Miniboss2->Play(true);

				Create_Miniboss();
				check_minibos = 1;
			}
		}

		//Camera::SetTarget(nullptr);nnn
		Scene::Update();
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(jk_SceneType::GamePlay3);
			//CreateBlending();
			check_map = 2;
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
		CollisionManager::SetLayer(jk_LayerType::BG_props, jk_LayerType::BG_props, true);

		mSnake->SetLife(false);
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