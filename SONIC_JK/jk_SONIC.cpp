#include "jk_Sonic.h"
#include "jk_Tails.h"
#include "Electsonic.h"
#include "FireSonic.h"
#include "WaterSonic.h"

#include <random>
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
#include "jk_Spring_Up.h"
#include "jk_Spring_Left.h"
#include "jk_Spike_Up.h"
#include "jk_Rock_small.h"
#include "jk_Rock_middle.h"
#include "jk_Rock_big.h"
#include "jk_Jeep_line_Handle.h"
#include "jk_Collapses_Ground.h"
#include "jk_Collapses_GR_left.h"
#include "jk_Move_GR.h"
#include "jk_Cylinder.h"
#include "jk_Last_Bridge.h"
#include "Jeepline_play.h"
#include "jk_Act1_Water.h"
#include "jk_Water_effect.h"
#include "Robotnic_machine.h"
#include "finall_stage.h"


#include "jk_Item.h"
#include "jk_Item_water.h"
#include "jk_Item_Fire.h"
#include "jk_Ring.h"
#include "jk_Ring_Falling.h"


#include "Boss_Arm.h"

#include "jk_Monster.h"
#include "jk_BaseBullet.h"



int ringpoint = 0;
int Elect = 0;
int Water = 0;
int Fire = 0;


float RandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

namespace jk
{
		Sonic::Sonic()
		: mDir(1)
		, SonicVelocity(0.f,0.f)
		, mState(eSonicState::Idle)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)		
		, SonicBrake(0.0f,0.0f)
		, circlecheck(0)	
		, Circle_piece(0)
		, Ringcheck(0)	
		, water_bounce(0)
		, fire_effect(0)
		, elect_effect(0)
		, fly_check(0)
		, end(0)
		, time(0)
		, Life(3)

	{
		Transform* tr = GetComponent<Transform>();
		
		//tr->SetPos(Vector2{ 24132.0f, 2417.0f });//원두번쨰 전
		//tr->SetPos(Vector2{ 21579.f,72.f });//두번째 폭포
		//tr->SetPos(Vector2{ 28821.f, 1363.f });//마지막폭포
		
		//tr->SetPos(Vector2{ 19924.0f, 2625.0f });//돌3

		//tr->SetPos(Vector2{ 18785.0f, 1495.0f });//상부원숭이
		//tr->SetPos(Vector2{ 16350.0f, 2847.0f });//jeepline
		//tr->SetPos(Vector2{ 13218.0f, 3174.0f });//캐논
	
		//tr->SetPos(Vector2{ 2790.0f * 3, 3200.f }); //시작
		//tr->SetPos(Vector2{ 15424.0f , 2921.f });
		//tr->SetPos(Vector2{ 12310.0f, 3211.0f });
		//tr->SetPos(Vector2(21480.f, 3450.f));//폭포
		//tr->SetPos(Vector2(19718.f, 3450.f));//원돌기
		//tr->SetPos(Vector2{ 26201.f, 3333.f });//밑에 원돌기
		//tr->SetPos(Vector2{ 27760.0f, 2792.0f });//원통
		//tr->SetPos(Vector2{ 29043.0f, 2499.0f });
	}		

		Sonic::~Sonic()
	{
			
	}

		void Sonic::Initialize()
	{			
		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2{ 2790.0f * 3, 3200.f });
		//tr->SetPos(Vector2(19718.f, 3450.f));

		Image* mImage = Resources::Load<Image>(L"SONIC", L"..\\Resources\\sonic.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSonicWalk", mImage, Vector2::RSonicWalkLTC, Vector2::RSonicWalksize, Vector2::RSonicWalkSpace, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicStand", mImage, Vector2::RSonicStandLTC, Vector2::RSonicStandsize, Vector2::RSonicStandSpace, 9, 1, 9, Vector2::Zero, 0.3);
		mAnimator->CreateAnimation(L"RSonicLookUp", mImage, Vector2::RSonicLookUpLTC, Vector2::RSonicLookUpsize, Vector2::RSonicLookUpSpace, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicSit", mImage, Vector2::RSonicSitLTC, Vector2::RSonicSitsize, Vector2::RSonicSitSpace, 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicShock", mImage, Vector2(740,750), Vector2(52,52), Vector2(4,4), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicRun", mImage, Vector2(24, 397), Vector2(52, 52), Vector2(4, 4), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicRollandJunp", mImage, Vector2(248, 397), Vector2(52, 52), Vector2(4, 4), 5, 1, 5, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RSonicBrake", mImage, Vector2(412, 478), Vector2(52, 52), Vector2(4, 4), 3, 1, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonicSpin", mImage, Vector2(24, 534), Vector2(62, 52), Vector2(4, 4), 6, 2, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonichurt", mImage, Vector2(956, 530), Vector2(56, 48), Vector2(8, 0), 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonic_Spring_up", mImage, Vector2(412, 912), Vector2(52, 50), Vector2(4, 0), 12, 1, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonic_Push", mImage, Vector2(736, 644), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSonic_Jeep", mImage, Vector2(412, 1451), Vector2(52, 52), Vector2(4, 0), 3, 1, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Endgind_pose", mImage, Vector2(24, 1492), Vector2(52, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1);



		Image* mImage1 = Resources::Load<Image>(L"LSONIC", L"..\\Resources\\Lsonic.bmp");
		mAnimator->CreateAnimation(L"LSonicWalk", mImage1, Vector2::LSonicWalkLTC, Vector2::LSonicWalksize, Vector2::LSonicWalkSpace, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonicStand", mImage1, Vector2::LSonicStandLTC, Vector2::LSonicStandsize, Vector2::LSonicStandSpace, 9, 1, 9, Vector2::Zero, 0.3);
		mAnimator->CreateAnimation(L"LSonicLookUp", mImage1, Vector2::LSonicLookUpLTC, Vector2::LSonicLookUpsize, Vector2::LSonicLookUpSpace, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonicSit", mImage1, Vector2::LSonicSitLTC, Vector2::LSonicSitsize, Vector2::LSonicSitSpace, 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonicRun", mImage1, Vector2(24, 397), Vector2(52, 52), Vector2(4, 4), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonicRollandJunp", mImage1, Vector2(248, 397), Vector2(52, 52), Vector2(4, 4), 5, 1, 5, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"LSonicBrake", mImage1, Vector2(412, 478), Vector2(52, 52), Vector2(4, 4), 3, 1, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonicSpin", mImage1, Vector2(24, 534), Vector2(62, 52), Vector2(4, 4), 6, 2, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonichurt", mImage1, Vector2(956, 530), Vector2(56, 48), Vector2(8, 0), 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonic_Spring_up", mImage1, Vector2(412, 912), Vector2(52, 50), Vector2(4, 0), 12, 1, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonic_Push", mImage1, Vector2(736, 644), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSonic_Jeep", mImage1, Vector2(412, 1451), Vector2(52, 52), Vector2(4, 0), 3, 1, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LEndgind_pose", mImage1, Vector2(24, 1492), Vector2(52, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1);

	

		Image* mImage_end = Resources::Load<Image>(L"End_sonic", L"..\\Resources\\END_BG.bmp");
		mAnimator->CreateAnimation(L"End_sonic", mImage_end, Vector2(1136, 243), Vector2(72, 96), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);




		//소닉 원회전(오른쪽)
		Image* mImage_RSN = Resources::Load<Image>(L"Rsonic_circle", L"..\\Resources\\Rsonic_circle.bmp");
		//회전달리기
		mAnimator->CreateAnimation(L"RSN_RT1", mImage_RSN, Vector2(262, 175), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT2", mImage_RSN, Vector2(473, 174), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT3", mImage_RSN, Vector2(681, 174), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT4", mImage_RSN, Vector2(50, 244), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT5", mImage_RSN, Vector2(262, 240), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT6", mImage_RSN, Vector2(474, 240), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_RT7", mImage_RSN, Vector2(682, 240), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		//회전걷기
		mAnimator->CreateAnimation(L"RSN_WT1", mImage_RSN, Vector2(466, 298), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT2", mImage_RSN, Vector2(50, 362), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT3", mImage_RSN, Vector2(466, 362), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT4", mImage_RSN, Vector2(49,  423), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT5", mImage_RSN, Vector2(466, 422), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT6", mImage_RSN, Vector2(50, 486), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RSN_WT7", mImage_RSN, Vector2(466, 486), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);

		//소닉 원회전(왼쪽)
		Image* mImage_LSN = Resources::Load<Image>(L"Lsonic_circle", L"..\\Resources\\Lsonic_circle.bmp");
		//회전달리기
		mAnimator->CreateAnimation(L"LSN_RT7", mImage_LSN, Vector2(262, 175), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT6", mImage_LSN, Vector2(473, 174), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT5", mImage_LSN, Vector2(681, 174), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT4", mImage_LSN, Vector2(50, 244), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT3", mImage_LSN, Vector2(262, 240), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT2", mImage_LSN, Vector2(474, 240), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_RT1", mImage_LSN, Vector2(682, 240), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		//회전걷기							
		mAnimator->CreateAnimation(L"LSN_WT7", mImage_LSN, Vector2(466, 298), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT6", mImage_LSN, Vector2(50, 362), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT5", mImage_LSN, Vector2(466, 362), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT4", mImage_LSN, Vector2(49, 423), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT3", mImage_LSN, Vector2(466, 422), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT2", mImage_LSN, Vector2(50, 486), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LSN_WT1", mImage_LSN, Vector2(466, 486), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);



		Collider* collider = AddComponent<Collider>();		
		collider->SetSize(Vector2(80.0f, 120.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.15f) * size.y });
				
		 
 		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mAnimator->Play(L"RSonicStand", true);
		Gameobject::Initialize();
	}    

		void Sonic::Update()
		{
			circlecheck = check->GetgroundCh();
			Circle_piece = check->GetCicle_piece();
			Ringcheck;
			ringpoint;
			int a = 0;

			if(ringpoint ==0)


			Transform* tr = GetComponent<Transform>();
			//Vector2 check_sonic = tr->GetPos();
			//check_sonic.x;
			//check_sonic.y;		
			//if (check_sonic.x > 30300.f)
			//{
			//	int a = 0;
			//}



			if (fly_check == 1)
			{
				mState = eSonicState::Tails_Hanging;
				mAnimator->Play(L"RSonic_Jeep", true);				
			}

			if (end == 1)
			{
				mState = eSonicState::EMDING;
				if (mDir == 1)
					mAnimator->Play(L"Endgind_pose", true);//엔딩포즈
				else
					mAnimator->Play(L"LEndgind_pose", true);//엔딩포즈

				//Vector2 velocity = mRigidbody->GetVelocity();
				//velocity.y = -350.0f;

				//mRigidbody->SetVelocity(velocity);
				//mRigidbody->SetGround(false);
				//mState = eSonicState::Jump;
				//if (mDir == 1)
				//{
				//	mAnimator->Play(L"RSonicRollandJunp", true);
				//	mDir = 1;
				//}
				//else if (mDir == -1)
				//{
				//	mAnimator->Play(L"LSonicRollandJunp", true);
				//	mDir = -1;
				//}
				//end = 2;
			}


			if (Input::GetKeyDown(eKeyCode::P))
			{
				object::Destory(elect);
				Elect = 0;
			}	
			

 			switch (mState)
			{
			case jk::Sonic::eSonicState::Idle:idle();
				break;

			case jk::Sonic::eSonicState::Attack:attack();
				break;

			case jk::Sonic::eSonicState::Hurt:hurt();
				break;

			case jk::Sonic::eSonicState::Move:move();
				break;

			case jk::Sonic::eSonicState::Run:run();
				break;

			case jk::Sonic::eSonicState::Dash:dash();
				break;

			case jk::Sonic::eSonicState::Brake:brake();
				break;

			case jk::Sonic::eSonicState::Push:push();
				break;

			case jk::Sonic::eSonicState::Jump:jump();
				break;

			case jk::Sonic::eSonicState::Spring_Jump:spring_jump();
				break;

			case jk::Sonic::eSonicState::Cylinder_move:cylinder_move();
				break;

			case jk::Sonic::eSonicState::Sit:sit();
				break;

			case jk::Sonic::eSonicState::Spin:spin();
				break;

			case jk::Sonic::eSonicState::Lookup:lookup();
				break;

			case jk::Sonic::eSonicState::Twojump:twojump();
				break;

			case jk::Sonic::eSonicState::Jeep_line:jeep_line();
				break;



			case jk::Sonic::eSonicState::Tails_Hanging:tails_hanging();
				break;				

			case jk::Sonic::eSonicState::Death:death();
				break;



			case jk::Sonic::eSonicState::EMDING:ending();
				break;

			case jk::Sonic::eSonicState::End:endgame();
				break;

			case jk::Sonic::eSonicState::Fire_Shield:fire_Shield();
				break;

			case jk::Sonic::eSonicState::Electricity_Shield:electricity_Shield();
				break;

			case jk::Sonic::eSonicState::Water_Shield:water_Shield();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_1:circle_Rturn_1();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_2:circle_Rturn_2();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_3:circle_Rturn_3();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_4:circle_Rturn_4();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_5:circle_Rturn_5();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_6:circle_Rturn_6();
				break;

			case jk::Sonic::eSonicState::Circle_Rturn_7:circle_Rturn_7();
				break;



			case jk::Sonic::eSonicState::Circle_Lturn_1:circle_Lturn_1();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_2:circle_Lturn_2();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_3:circle_Lturn_3();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_4:circle_Lturn_4();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_5:circle_Lturn_5();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_6:circle_Lturn_6();
				break;

			case jk::Sonic::eSonicState::Circle_Lturn_7:circle_Lturn_7();
				break;

			default:
				break;
			}

			check_map = check->Get_map_check();


			Gameobject::Update();
		}

		void Sonic::Render(HDC hdc)
		{
			Gameobject::Render(hdc);
		}

		void Sonic::Release()
	{
		Gameobject::Release();
	}



		void Sonic::OnCollisionEnter(Collider* other)
		{
			//tials 충돌
			if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
			{
				Tails::eTailsState tailsState = tails->GetTails_state();
				if ((tailsState == Tails::eTailsState::Fly_Waiting)|| (tailsState == Tails::eTailsState::Fly_Pursue))
				{
					mState = eSonicState::Tails_Hanging;
					mAnimator->Play(L"RSonic_Jeep", true);
				}
			}

			//배경소품 충돌★
	
				//Act1_Water 물충돌
				if (Act1_Water* act1_water = dynamic_cast<Act1_Water*>(other->GetOwner()))
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPos();

					Vector2 water_pos = act1_water->GetComponent<Transform>()->GetPos();
					Scene* curScene = SceneManager::GetActiveScene();
					Water_effect* water_effect = new Water_effect();
					water_effect->GetComponent<Transform>()->SetPos(Vector2{ pos.x, water_pos.y-100 });
					curScene->AddGameobeject(water_effect, jk_LayerType::BG_props);
				}


				//Spring Up 충돌처리
				if (Spring_Up* spring_up = dynamic_cast<Spring_Up*>(other->GetOwner()))
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPos();
														
					Vector2 velocity = mRigidbody->GetVelocity();	
					velocity.y = 0.0f;
					velocity.y -= 1050.0f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
					if (mDir == 1)
					{
						mAnimator->Play(L"RSonic_Spring_up", true);
					}
					else if (mDir == -1)
					{
						mAnimator->Play(L"LSonic_Spring_up", true);
					}
					mState = eSonicState::Spring_Jump;
				}				

				//Spring Left 충돌처리
				if (Spring_Left* spring_Left = dynamic_cast<Spring_Left*>(other->GetOwner()))
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 sonic_pos = tr->GetPos();
					Vector2 velocity = mRigidbody->GetVelocity();
					sonic_pos.y = sonic_pos.y + 120;
					
					Vector2 Spring_L = spring_Left->GetComponent<Transform>()->GetPos();
			
				
					if(sonic_pos.y< Spring_L.y)
					{
						mState = eSonicState::Idle;
						mRigidbody->SetGround(true);
						if (mDir == 1)
							mAnimator->Play(L"RSonicStand", true);
						else
							mAnimator->Play(L"LSonicStand", true);					
					}
					else
					{
						velocity.x = 0.0f;
						velocity.x -= 1050.0f;
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						if (mDir == 1)
						{
							mAnimator->Play(L"LSonicRun", true);
						}
						mState = eSonicState::Run;
					}
				}

				//Spike up 충돌처리
				if (Spike_Up* spike_Up = dynamic_cast<Spike_Up*>(other->GetOwner()))
				{

					Vector2 Spike = spike_Up->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();								
					Vector2 Sonic = tr->GetPos();
					Sonic.y = Sonic.y + 120;

					if (Sonic.y < Spike.y)
					{
						if (mDir == 1)
						{
							hurtcheck = 1;
							mAnimator->Play(L"RSonichurt", true);
							Vector2 velocity = mRigidbody->GetVelocity();
							velocity = Vector2(0.0f, 0.0f);
							velocity -= (300.0f, 300.0f);
							mRigidbody->SetGround(false);
							mRigidbody->SetVelocity(velocity);
							mState = eSonicState::Hurt;
						}
						else if (mDir == -1)
						{
							hurtcheck = -1;
							mAnimator->Play(L"LSonichurt", true);
							Vector2 velocity = mRigidbody->GetVelocity();
							velocity = Vector2(0.0f, 0.0f);
							velocity.x += 300.0f;
							velocity.y -= 300.0f;
							mRigidbody->SetGround(false);
							mRigidbody->SetVelocity(velocity);
							mState = eSonicState::Hurt;
						}
					}
					else
					{
						Transform* tr = GetComponent<Transform>();
						Vector2 sonic_Pos = tr->GetPos();

						//소닉 콜라이더 및 좌표
						Collider* mSonic_Col = this->GetComponent<Collider>();
						Vector2 mSonic_Pos = mSonic_Col->Getpos();
						
						//스파이크 콜라이더 및 좌표
						Collider* mSpike_Col = spike_Up->GetComponent<Collider>();
						Vector2 mSpike_Pos = mSpike_Col->Getpos();
						Transform* grTr = this->GetComponent<Transform>();					

						float fLen = fabs(mSonic_Pos.x - mSpike_Pos.x);
						float fSize = mSpike_Col->GetSize().x;

						if ((mSonic_Pos.x < mSpike_Pos.x))
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });	

							sonic_Pos.x = mSpike_Pos.x - mSpike_Col->GetSize().x;

							mAnimator->Play(L"RSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);					
						}
						else if ((mSonic_Pos.x > mSpike_Pos.x))
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_Pos.x = mSpike_Pos.x + mSpike_Col->GetSize().x;

							mAnimator->Play(L"LSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);
						}					
					}	
				}

				//Jeep_line Handle 충돌처리(포물선)
				if (Jeep_line_Handle* jeep_line = dynamic_cast<Jeep_line_Handle*>(other->GetOwner()))
				{

					Vector2 jeep_handle = jeep_line->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();
				
					jeepline = jeep_line->GetDir();
					
						if (mDir == 1)
						{
							mState = eSonicState::Jeep_line;
							mAnimator->Play(L"RSonic_Jeep", true);
						}
						else if (mDir == -1)
						{
							mState = eSonicState::Jeep_line;
							mAnimator->Play(L"LSonic_Jeep", true);
						}			
				}

				//Jeep_line_play 충돌처리(대각선)
				if (Jeepline_play* jeep_line = dynamic_cast<Jeepline_play*>(other->GetOwner()))
				{

					Vector2 jeep_handle = jeep_line->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 jeep_line_pos = tr->GetPos();
								
					mState = eSonicState::Jeep_line;
					mAnimator->Play(L"RSonic_Jeep", true);
		
				}
				   
				//Collapses_Ground 없어지는땅
				if (Collapses_Ground* collapses_Ground = dynamic_cast<Collapses_Ground*>(other->GetOwner()))
				{
					Vector2 Collapses_Gr = collapses_Ground->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();

					if (mDir == 1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"LSonicStand", true);
					}
				}

				//Collapses_Ground(left) 없어지는땅
				if (Collapses_GR_left* collapses_Ground = dynamic_cast<Collapses_GR_left*>(other->GetOwner()))
				{
					Vector2 Collapses_Gr = collapses_Ground->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();


					if (mDir == 1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"LSonicStand", true);
					}
				}

				//Move_GR 충돌처리
				if (Move_GR* move_GR = dynamic_cast<Move_GR*>(other->GetOwner()))
				{
					Vector2 move_GR_pos = move_GR->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();


					if (mDir == 1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"LSonicStand", true);
					}
				}				

				//finall_stage 충돌처리
				if (finall_stage* stage = dynamic_cast<finall_stage*>(other->GetOwner()))
				{
					Vector2 fly_machine_pos = stage->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();


					if (mDir == 1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"LSonicStand", true);
					}
				}

				//Robotnic_machine 충돌처리
				if (Robotnic_machine* fly_machine = dynamic_cast<Robotnic_machine*>(other->GetOwner()))
				{
					Vector2 fly_machine_pos = fly_machine->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();


					if (mDir == 1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Idle;
						mAnimator->Play(L"LSonicStand", true);
					}
				}

				//last_Bridge 충돌처리
				if (Last_Bridge* last_Bridge = dynamic_cast<Last_Bridge*>(other->GetOwner()))
					{
						Vector2 mlast_Bridge_pos = last_Bridge->GetComponent<Transform>()->GetPos();
						Transform* tr = GetComponent<Transform>();
						Vector2 msonic = tr->GetPos();


						if (mDir == 1)
						{
							mState = eSonicState::Idle;
							mAnimator->Play(L"RSonicStand", true);
						}
						else if (mDir == -1)
						{
							mState = eSonicState::Idle;
							mAnimator->Play(L"LSonicStand", true);
						}
					}

				//Cylinder 충돌처리
				if (Cylinder* cylinder = dynamic_cast<Cylinder*>(other->GetOwner()))
				{
					if (mDir == 1)
					{
						mState = eSonicState::Cylinder_move;
						//mAnimator->Play(L"LSonic_Spring_up", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Cylinder_move;
						//mAnimator->Play(L"LSonic_Spring_up", true);
					}
				}	
		
				//Rock 충돌처리(푸쉬)
				if (Rock_small* rock_small = dynamic_cast<Rock_small*>(other->GetOwner()))
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 sonic_pos = tr->GetPos();
					Vector2 rock_small_pos = rock_small->GetComponent<Transform>()->GetPos();
							

					//소닉 콜라이더 및 좌표
					Collider* mSonic_Col = this->GetComponent<Collider>();
					Vector2 mSonic_colpos = mSonic_Col->Getpos();
					//스몰락 콜라이더 및 좌표
					Collider* mRockSmall_Col = rock_small->GetComponent<Collider>();
					Vector2 mRockSmall_colpos = mRockSmall_Col->Getpos();


					if (!(mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash))
					{
						if (mSonic_colpos.x< mRockSmall_colpos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_pos.x = mRockSmall_colpos.x - mRockSmall_Col->GetSize().x*0.6;

							mAnimator->Play(L"RSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_pos);
						}
						else if (mSonic_colpos.x > mRockSmall_colpos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_pos.x = mRockSmall_colpos.x + mRockSmall_Col->GetSize().x;

							mAnimator->Play(L"LSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_pos);
						}
					}
					else
					{
						sonic_pos.y = sonic_pos.y + 120;
						if (sonic_pos.y < rock_small_pos.y)
						{
							Vector2 velocity = mRigidbody->GetVelocity();
							velocity.y = 0.0f;
							velocity.y = -350.f;
							mRigidbody->SetGround(false);
							mRigidbody->SetVelocity(velocity);
						}
					}
				}
				
				if (Rock_middle* rock_middle = dynamic_cast<Rock_middle*>(other->GetOwner()))
				{

					Vector2 Spike = rock_middle->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 sonic_Pos = tr->GetPos();

					//소닉 콜라이더 및 좌표
					Collider* mSonic_Col = this->GetComponent<Collider>();
					Vector2 mSonic_colos = mSonic_Col->Getpos();		

					//스파이크 콜라이더 및 좌표
					Collider* mRockMiddle_Col = rock_middle->GetComponent<Collider>();
					Vector2 mRockMiddle_Pos = mRockMiddle_Col->Getpos();

					if (!(mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash))
					{
						if (mSonic_colos.x < mRockMiddle_Pos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_Pos.x = mRockMiddle_Pos.x - mRockMiddle_Col->GetSize().x*0.6;

							mAnimator->Play(L"RSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);
						}
						else if (mSonic_colos.x > mRockMiddle_Pos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_Pos.x = mRockMiddle_Pos.x + mRockMiddle_Col->GetSize().x;

							mAnimator->Play(L"LSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);
						}
					}
				}

				if (Rock_big* rock_big = dynamic_cast<Rock_big*>(other->GetOwner()))
				{
					Vector2 rock_big_pos = rock_big->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 sonic_Pos = tr->GetPos();

					//소닉 콜라이더 및 좌표
					Collider* mSonic_Col = this->GetComponent<Collider>();
					Vector2 mSonic_colPos = mSonic_Col->Getpos();
			

					//스파이크 콜라이더 및 좌표
					Collider* mRockBig_Col = rock_big->GetComponent<Collider>();
					Vector2 mRockBig_colPos = mRockBig_Col->Getpos();

					if (!(mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash))
					{
						if (mSonic_colPos.x < mRockBig_colPos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_Pos.x = mRockBig_colPos.x - mRockBig_Col->GetSize().x*0.6;

							mAnimator->Play(L"RSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);
						}
						else if (mSonic_colPos.x > mRockBig_colPos.x)
						{
							mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

							sonic_Pos.x = mRockBig_colPos.x + mRockBig_Col->GetSize().x;

							mAnimator->Play(L"LSonic_Push", true);
							mState = eSonicState::Push;
							tr->SetPos(sonic_Pos);
						}
					}
				}




			//아이템 충돌★
				//ITEM(ELECT) 충돌처리
				if (Item* electitem = dynamic_cast<Item*>(other->GetOwner()))
				{
					if (mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash)
					{
						int itemcheck = electitem->GetItemcheck();
						if (itemcheck != 1)
						{
							return;
						}

						if (itemcheck == 1)
						{
				
							if (Water != 0)
							{
								object::Destory(water);
								Water = 0;
							}
							if (Fire != 0)
							{
								object::Destory(fire);
								Fire = 0;
							}

							Transform* tr = GetComponent<Transform>();
							Scene* curScene = SceneManager::GetActiveScene();
							elect = new Electsonic(this);
							elect->GetComponent<Transform>()->SetPos(tr->GetPos());
							curScene->AddGameobeject(elect, jk_LayerType::Player_smoke);
							Elect = 1;
						}
						else
						{ 
							return;
						}
					}
				}
				if (Item_water* water_shield = dynamic_cast<Item_water*>(other->GetOwner()))
				{
					if (mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash)
					{
						int itemcheck = water_shield->GetItemcheck();
						if (itemcheck != 1)
						{
							return;
						}


						if (Elect != 0)
						{
							object::Destory(elect);
							Elect = 0;
						}
						if (Fire != 0)
						{
							object::Destory(fire);
							Fire = 0;
						}

						if (itemcheck == 1)
						{
			
							Transform* tr = GetComponent<Transform>();
							Scene* curScene = SceneManager::GetActiveScene();
							water = new WaterSonic(this);
							water->GetComponent<Transform>()->SetPos(tr->GetPos());
							curScene->AddGameobeject(water, jk_LayerType::Player_smoke);
							Water = 1;
						}
						else
						{
							return;
						}
					}
				}
				if (Item_Fire* Fire_shield = dynamic_cast<Item_Fire*>(other->GetOwner()))
				{
					if (mState == eSonicState::Jump || mState == eSonicState::Spin || mState == eSonicState::Dash)
					{
						int itemcheck = Fire_shield->GetItemcheck();
						if (itemcheck != 1)
						{
							return;
						}

						if (Water != 0)
						{
							object::Destory(water);
							Water = 0;
						}							
						if (Elect != 0)
						{
							object::Destory(elect);
							Elect = 0;
						}

			
						if (itemcheck == 1)
						{
							Transform* tr = GetComponent<Transform>();
							Scene* curScene = SceneManager::GetActiveScene();
							fire = new FireSonic(this);
							fire->GetComponent<Transform>()->SetPos(tr->GetPos());
							curScene->AddGameobeject(fire, jk_LayerType::Player_smoke);
							Fire = 1;
						}
						else
						{
							return;
						}
					}
				}

				//RING 충돌처리
				if (Ring* ring = dynamic_cast<Ring*>(other->GetOwner()))
				{
					Ringcheck += 1;
					ringpoint += 1;
				}





								 
			//몬스터 충돌★
				//Rino 충돌처리		
				if (Monster* rino = dynamic_cast<Monster*>(other->GetOwner()))
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPos();
					Vector2 rinopos = rino->Getmonster();
					if (!((mState == eSonicState::Spin) || (mState == eSonicState::Jump) || (mState == eSonicState::Dash)))
					{
						if (rinopos.x > pos.x)
						{
							hurtcheck = 1;
							mAnimator->Play(L"RSonichurt", true);
							Vector2 velocity = mRigidbody->GetVelocity();
							velocity = Vector2(0.0f, 0.0f);
							velocity -= (300.0f, 300.0f);
							mRigidbody->SetGround(false);
							mRigidbody->SetVelocity(velocity);
							mState = eSonicState::Hurt;


							Ring_Falling* ring;
							if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
							{
								Transform* tr = GetComponent<Transform>();
								Scene* curScene = SceneManager::GetActiveScene();

								const int numRings = 10; // 생성할 링의 개수
								const float minAngle = -45.0f; // 링이 떨어지는 최소 각도
								const float maxAngle = 45.0f; // 링이 떨어지는 최대 각도
								const float distance = 250.0f; // 링이 떨어지는 거리

								for (int i = 0; i < numRings; ++i)
								{
									float angle = RandomFloat(minAngle, maxAngle); // 떨어지는 각도를 랜덤하게 결정							
									Vector2 dropDirection = math::Rotate(Vector2{ 0.f,-1.f }, angle); // 떨어지는 방향 벡터를 구함

									Ring_Falling* ring = new Ring_Falling(this);
									curScene->AddGameobeject(ring, jk_LayerType::Rings);

									if (check)
									{
										if (check_map == 0)
										{
											ring->SetGroundImage(check->GetGroundImage());
										}
										else if (check_map == 1)
										{
											ring->SetGroundImage(check->GetGroundImage2());
										}
									}

									Vector2 dropPos = tr->GetPos() + (dropDirection * distance); // 떨어지는 위치 계산
									ring->GetComponent<Transform>()->SetPos(dropPos); // 링의 위치 설정
								}
							}
						}

						else if (rinopos.x < pos.x)
						{
							hurtcheck = -1;
							mAnimator->Play(L"LSonichurt", true);
							Vector2 velocity = mRigidbody->GetVelocity();
							velocity = Vector2(0.0f, 0.0f);
							velocity.x += 300.0f;
							velocity.y -= 300.0f;
							mRigidbody->SetGround(false);
							mRigidbody->SetVelocity(velocity);
							mState = eSonicState::Hurt;

							Ring_Falling* ring;
							if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
							{

								Transform* tr = GetComponent<Transform>();
								Scene* curScene = SceneManager::GetActiveScene();

								const int numRings = 10; // 생성할 링의 개수
								const float minAngle = -45.0f; // 링이 떨어지는 최소 각도
								const float maxAngle = 45.0f; // 링이 떨어지는 최대 각도
								const float distance = 250.0f; // 링이 떨어지는 거리


								for (int i = 0; i < numRings; ++i)
								{
									float angle = RandomFloat(minAngle, maxAngle) ;
									Vector2 dropDirection = math::Rotate(Vector2{ 0.f,-1.f }, angle);

									Ring_Falling* ring = new Ring_Falling(this);
									curScene->AddGameobeject(ring, jk_LayerType::Rings);
									if (check)
									{
										//Image* groundImage = check->GetGroundImage();
								
										if (check_map == 0)
										{
											ring->SetGroundImage(check->GetGroundImage());
										}
										else if (check_map == 1)
										{
											ring->SetGroundImage(check->GetGroundImage2());
										}										
									}
									Vector2 dropPos = tr->GetPos() + (dropDirection * distance);
									ring->GetComponent<Transform>()->SetPos(dropPos);
								}
							}
						}
					}
				}			

				//BOSS_BULLET 충돌처리
				if (BaseBullet* bullet = dynamic_cast<BaseBullet*>(other->GetOwner()))
				{
					mAnimator->Play(L"RSonichurt", true);
					/*	Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity -= (300.0f, 300.0f);
						mRigidbody->SetVelocity(velocity);
						mRigidbody->SetGround(false);*/
				}


				//보스충돌
				//LASTBOSS
				if (Boss_Arm* last_boss_arm = dynamic_cast<Boss_Arm*>(other->GetOwner()))
				{

					Vector2 boss_arm_pos = last_boss_arm->GetComponent<Transform>()->GetPos();
					Transform* tr = GetComponent<Transform>();
					Vector2 msonic = tr->GetPos();

				
					if (mDir == 1)
					{
						mState = eSonicState::Jump;
						mAnimator->Play(L"RSonicRollandJunp", true);
					}
					else if (mDir == -1)
					{
						mState = eSonicState::Jeep_line;
						mAnimator->Play(L"LSonicRollandJunp", true);
					}
				}	
		}

		void Sonic::OnCollisionStay(Collider * other)
	{
		Transform* tr = GetComponent<Transform>();
		tr->GetPos();


	}

		void Sonic::OnCollisionExit(Collider * other)
	{
			if (Cylinder* cylinder = dynamic_cast<Cylinder*>(other->GetOwner()))
			{
				if (mDir == 1)
				{
					mState = eSonicState::Idle;
					mAnimator->Play(L"RSonicStand", true);
				}
				else if (mDir == -1)
				{
					mState = eSonicState::Spring_Jump;
					mAnimator->Play(L"LSonicStand", true);
				}
			}
	}



		void Sonic::idle()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();


			if (Input::GetKeyDown(eKeyCode::RIGHT)
				|| Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState = eSonicState::Move;
				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RSonicWalk", true);
					mDir = 1;
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonicWalk", true);
					mDir = -1;
				}
			}

			else if (Input::GetKeyDown(eKeyCode::UP))
			{
				mState = eSonicState::Lookup;
				if (Input::GetKeyDown(eKeyCode::UP) && mDir == 1)
					mAnimator->Play(L"RSonicLookUp", true);
				else if (Input::GetKeyDown(eKeyCode::UP) && mDir == -1)
					mAnimator->Play(L"LSonicLookUp", true);
			}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState = eSonicState::Sit;
				if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == 1)
					mAnimator->Play(L"RSonicSit", false);
				else if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == -1)
					mAnimator->Play(L"LSonicSit", false);
			}

			else if (Input::GetKeyDown(eKeyCode::K))
			{
				Ringcheck = 100;
			}



			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 550.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mState = eSonicState::Jump;
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicRollandJunp", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					mAnimator->Play(L"LSonicRollandJunp", true);
					mDir = -1;
				}
			}


		}

		void Sonic::attack()
		{
		}

		void Sonic::hurt()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			


			if (mRigidbody->GetGround())
			{
				mState = eSonicState::Idle;
				if (mDir = 1)
				{
					mAnimator->Play(L"RSonicStand", true);
				}
				else if (mDir = -1)
				{
					mAnimator->Play(L"LSonicStand", true);
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eSonicState::Move;
					if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						mAnimator->Play(L"RSonicWalk", true);
						mDir = 1;
					}
					else if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						mAnimator->Play(L"LSonicWalk", true);
						mDir = -1;
					}
				}
			}				
	
				//else
				//{
				//	for (int a = 0; a < Ringcheck; a++)
				//	{
				//		Transform* tr = GetComponent<Transform>();
				//		Scene* curScene = SceneManager::GetActiveScene();
				//		ring[a] = new Ring(this);
				//		curScene->AddGameobeject(ring[a], jk_LayerType::Rings);						
				//		int L = -300;
				//		int R = 300;
				//		for (int i = 0; i < 2; i++)
				//		{
				//			if (i == 0)
				//				ring[a]->GetComponent<Transform>()->SetPos(Vector2{ pos.x + L, pos.y + L });
				//			else
				//				ring[a]->GetComponent<Transform>()->SetPos(Vector2{ pos.x + R, pos.y + R });
				//		}
				//	}
				//}	

		}

		void Sonic::move()
		{
			if (Input::GetKeyUp(eKeyCode::RIGHT)
				|| Input::GetKeyUp(eKeyCode::LEFT))
			{
				mState = eSonicState::Idle;
				if (mDir == 1)
					mAnimator->Play(L"RSonicStand", true);
				else
					mAnimator->Play(L"LSonicStand", true);
			}

			else if (Input::GetKeyDown(eKeyCode::UP))
			{
				mState = eSonicState::Lookup;
				if (Input::GetKeyDown(eKeyCode::UP) && mDir == 1)
					mAnimator->Play(L"RSonicLookUp", true);
				else if (Input::GetKeyDown(eKeyCode::UP) && mDir == -1)
					mAnimator->Play(L"LSonicLookUp", true);
			}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState = eSonicState::Sit;
				if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == 1)
					mAnimator->Play(L"RSonicSit", false);
				else if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == -1)
					mAnimator->Play(L"LSonicSit", false);
			}

			//Vector2 velocity = mRigidbody->GetVelocity();
			//if (velocity.x == 0)
			//{
			//	if (mDir = -1)
			//	{
			//		mState = eSonicState::Idle;
			//		mAnimator->Play(L"LSonicStand", true);
			//		mDir = -1;
			//	}
			//	if (mDir = 1)
			//	{
			//		mState = eSonicState::Idle;
			//		mAnimator->Play(L"RSonicStand", true);
			//		mDir = 1;
			//	}
			//}

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
				//mRigidbody->SetVelocity(Vector2{ -300.0f, mRigidbody->GetVelocity().y });
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x <= -400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"LSonicRun", true);
				}
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(+500.0f, 0.0f));
				//mRigidbody->SetVelocity(Vector2{ 300.0f,  mRigidbody->GetVelocity().y});

				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x >= 400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"RSonicRun", true);
				}
			}

			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 550.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mState = eSonicState::Jump;
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicRollandJunp", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					mAnimator->Play(L"LSonicRollandJunp", true);
					mDir = -1;
				}
			}
		
			if (circlecheck == 1)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.x) ,fabs(TempVel.x) * -0.5f });
				mRigidbody->AddForce(Vector2(500.0f, 0.0f));
				if (Circle_piece == 1)
				{
					mState = eSonicState::Circle_Rturn_1;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"RSN_RT1", true);
					}
					else
					{
						mAnimator->Play(L"RSN_WT1", true);
					}
				}
				mState = eSonicState::Circle_Rturn_1;
			}

			if (circlecheck == 2)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.x) * -1,fabs(TempVel.x) * -0.5f });
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
				if (Circle_piece == 7)
				{
					mState = eSonicState::Circle_Lturn_7;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"LSN_RT7", true);
					}
					else
					{
						mAnimator->Play(L"LSN_WT7", true);
					}
				}
				mState = eSonicState::Circle_Lturn_7;
			}

			tr->SetPos(pos);
		}

		void Sonic::run()
		{

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if ((SonicVelocity.x <= -400) && (Input::GetKeyUp(eKeyCode::RIGHT)))
			{
				mRigidbody->Velocity() = Vector2{ 0.0f,0.0f };
				mRigidbody->SetFiction(1000);
				mState = eSonicState::Brake;
				mAnimator->Play(L"LSonicBrake", false);
				mDir = -1;
			}


			if ((SonicVelocity.x >= 400) && (Input::GetKeyUp(eKeyCode::LEFT)))
			{
				mRigidbody->Velocity() = Vector2{ 0.0f,0.0f };
				mRigidbody->SetFiction(1000);
				mState = eSonicState::Brake;
				mAnimator->Play(L"RSonicBrake", false);
				mDir = 1;
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			if (velocity.x >= -300 && velocity.x <= 0)
			{
				if (mDir = -1)
				{
					mState = eSonicState::Move;
					mAnimator->Play(L"LSonicWalk", true);
					mDir = -1;
				}

			}
			if (velocity.x <= 300 && velocity.x >= 0)
			{
				if (mDir = 1)
				{
					mState = eSonicState::Move;
					mAnimator->Play(L"RSonicWalk", true);
					mDir = 1;
				}
			}

			if ((SonicVelocity.x >= 400) && (Input::GetKeyUp(eKeyCode::LEFT)))
			{
				mRigidbody->Velocity() = Vector2{ 0.0f,0.0f };
				mRigidbody->SetFiction(1000);
				mState = eSonicState::Brake;
				mAnimator->Play(L"RSonicBrake", false);
				mDir = 1;
			}

			//else if (Input::GetKeyDown(eKeyCode::UP))
			//{
			//	mState = eSonicState::Lookup;
			//	if (Input::GetKeyDown(eKeyCode::UP) && mDir == 1)
			//		mAnimator->Play(L"RSonicLookUp", true);
			//	else if (Input::GetKeyDown(eKeyCode::UP) && mDir == -1)
			//		mAnimator->Play(L"LSonicLookUp", true);
			//}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState = eSonicState::Dash;
				if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == 1)
					mAnimator->Play(L"RSonicRollandJunp", true);
				else if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == -1)
					mAnimator->Play(L"LSonicRollandJunp", true);
			}
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(+500.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 550.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mState = eSonicState::Jump;
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicRollandJunp", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					mAnimator->Play(L"LSonicRollandJunp", true);
					mDir = -1;
				}
			}

			if (circlecheck == 1)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.x) ,fabs(TempVel.x) * -0.5f });
				mRigidbody->AddForce(Vector2(500.0f, 0.0f));
				if (Circle_piece == 1)
				{
					mState = eSonicState::Circle_Rturn_1;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"RSN_RT1", true);
					}
					else
					{
						mAnimator->Play(L"RSN_WT1", true);
					}
				}
				mState = eSonicState::Circle_Rturn_1;
			}


			if (circlecheck == 2)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.x) * -1.0f,fabs(TempVel.x) * -0.5f });
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
				if (Circle_piece == 7)
				{
					mState = eSonicState::Circle_Lturn_7;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"LSN_RT7", true);
					}
					else
					{
						mAnimator->Play(L"LSN_WT7", true);
					}
				}
				mState = eSonicState::Circle_Lturn_7;
			}

			tr->SetPos(pos);
		}

		void Sonic::dash()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 velocity = mRigidbody->GetVelocity();

			if ((SonicVelocity.x <= -400) && (Input::GetKeyUp(eKeyCode::RIGHT)))
			{
				mRigidbody->Velocity() = Vector2{ 0.0f,0.0f };
				mRigidbody->SetFiction(1000);
				mState = eSonicState::Brake;
				mAnimator->Play(L"LSonicBrake", true);
				mDir = -1;
			}

			else if ((SonicVelocity.x >= 400) && (Input::GetKeyUp(eKeyCode::LEFT)))
			{
				mRigidbody->Velocity() = Vector2{ 0.0f,0.0f };
				mRigidbody->SetFiction(1000);
				mState = eSonicState::Brake;
				mAnimator->Play(L"RSonicBrake", true);
				mDir = 1;
			}

			else if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));

				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x <= -400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"LSonicRun", true);
				}
			}

			else if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(+500.0f, 0.0f));


				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x >= 400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"RSonicRun", true);
				}
			}


			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(true);
				mState = eSonicState::Jump;
				if (mDir == 1)
				{
					velocity.y -= 550.0f;
					velocity.x = velocity.x;
					mDir = 1;
				}
				else if (mDir == -1)
				{
					velocity.y -= 550.0f;
					velocity.x = velocity.x;
					mDir = -1;
				}
			}



			if (circlecheck == 1)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ 0.0f ,fabs(TempVel.x)*-1});
				mRigidbody->AddForce(Vector2(300.0f, -1000.0f));
				if (Circle_piece == 1)
				{
					mState = eSonicState::Circle_Rturn_1;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"RSN_RT1", true);
					}
					else
					{
						mAnimator->Play(L"RSN_WT1", true);
					}
				}
				mState = eSonicState::Circle_Rturn_1;
			}


			if (circlecheck == 2)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ 0.0f,fabs(TempVel.x) * -1.f });
				mRigidbody->AddForce(Vector2(-300.0f, -1000.0f));
				if (Circle_piece == 7)
				{
					mState = eSonicState::Circle_Lturn_7;
					SonicVelocity = mRigidbody->Velocity();
					if (SonicVelocity.y <= -400)
					{
						mAnimator->Play(L"LSN_RT7", true);
					}
					else
					{
						mAnimator->Play(L"LSN_WT7", true);
					}
				}
				mState = eSonicState::Circle_Lturn_7;
			}



			tr->SetPos(pos);
			mRigidbody->SetVelocity(velocity);
		}

		void Sonic::brake()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if (mRigidbody->Velocity() == Vector2{ 0.0f,0.0f })
			{
				mRigidbody->SetFiction(100);
				if (Input::GetKeyDown(eKeyCode::RIGHT)
					|| Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eSonicState::Move;
					if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						mAnimator->Play(L"RSonicWalk", true);
						mDir = 1;
					}
					else if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						mAnimator->Play(L"LSonicWalk", true);
						mDir = -1;
					}
				}

				else if (mRigidbody->Velocity() == Vector2::Zero)
				{
					mState = eSonicState::Idle;
					if (mDir == 1)
					{
						mAnimator->Play(L"RSonicStand", true);
					}
					else if (mDir == -1)
					{
						mAnimator->Play(L"LSonicStand", true);
					}

				}

				else if (Input::GetKeyDown(eKeyCode::UP))
				{
					mState = eSonicState::Lookup;
					if (Input::GetKeyDown(eKeyCode::UP) && mDir == 1)
						mAnimator->Play(L"RSonicLookUp", true);
					else if (Input::GetKeyDown(eKeyCode::UP) && mDir == -1)
						mAnimator->Play(L"LSonicLookUp", true);
				}

				else if (Input::GetKeyDown(eKeyCode::DOWN))
				{
					mState = eSonicState::Sit;
					if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == 1)
						mAnimator->Play(L"RSonicSit", false);
					else if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == -1)
						mAnimator->Play(L"LSonicSit", false);
				}

				else if (Input::GetKeyDown(eKeyCode::SPACE))
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 700.0f;

					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mState = eSonicState::Jump;
					if (mDir == 1)
					{
						mAnimator->Play(L"RSonicRollandJunp", true);
						mDir = 1;
					}
					else if (mDir == -1)
					{
						mAnimator->Play(L"LSonicRollandJunp", true);
						mDir = -1;
					}
				}
			}
		}

		void Sonic::push()
		{
			if(mDir == 1)
			{			
				if (Input::GetKeyUp(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RSonicStand", true);
					mDir = 1;
					mState = eSonicState::Idle;
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonicWalk", true);
					mDir = -1;
					mState = eSonicState::Move;
				}			
			}
			if (mDir == -1)
			{
				if (Input::GetKeyUp(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonicStand", true);
					mDir = 1;
					mState = eSonicState::Idle;
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RSonicWalk", true);
					mDir = -1;
					mState = eSonicState::Move;
				}
			}
		}

		void Sonic::jump()
		{
			//mState = eSonicState::Attack;

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			
			if (mRigidbody->GetGround())
			{
				mState = eSonicState::Idle;
				if (mDir = 1)
				{
					mAnimator->Play(L"RSonicStand", true);
				}
				else if (mDir = -1)
				{
					mAnimator->Play(L"LSonicStand", true);
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eSonicState::Move;
					if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						mAnimator->Play(L"RSonicWalk", true);
						mDir = 1;
					}
					else if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						mAnimator->Play(L"LSonicWalk", true);
						mDir = -1;
					}
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;				
				mRigidbody->AddForce(Vector2(-150.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();	
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;				
				mRigidbody->AddForce(Vector2(+150.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();		
			}
			
			if ((Elect == 1)&& (Input::GetKeyDown(eKeyCode::SPACE)))
			{		
				mState = eSonicState::Electricity_Shield;
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y = -550.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);	
				elect_effect = 1;
			}

			if ((Fire == 1) && (Input::GetKeyDown(eKeyCode::SPACE)))
			{
				mState = eSonicState::Fire_Shield;			
				Vector2 velocity = mRigidbody->GetVelocity();
				if(mDir ==1)
				velocity.x = 550.0f;
				else
				velocity.x = -550.0f;
				fire_effect = 1;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);		
			}	

			water_bounce = 0;
			if ((Water == 1) && (Input::GetKeyDown(eKeyCode::SPACE)))
			{				
				mState = eSonicState::Water_Shield;
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y = 550.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);		
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			
			//if ((end == 2)&& (velocity.y >= 0.0f))
			//{

			//	mState = eSonicState::End;
			//	mAnimator->Play(L"End_sonic", true);
			//	mRigidbody->SetGround(true);
	

			//}

			tr->SetPos(pos);
		}

		void Sonic::spring_jump()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if (mRigidbody->GetGround())
			{
				mState = eSonicState::Idle;
				if (mDir = 1)
				{
					mAnimator->Play(L"RSonicStand", true);
				}
				else if (mDir = -1)
				{
					mAnimator->Play(L"LSonicStand", true);
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eSonicState::Move;
					if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						mAnimator->Play(L"RSonicWalk", true);
						mDir = 1;
					}
					else if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						mAnimator->Play(L"LSonicWalk", true);
						mDir = -1;
					}
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(-550.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(+550.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
			tr->SetPos(pos);
		}

		void Sonic::cylinder_move()
		{
			if (mDir == 1)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				if (Input::GetKey(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonic_Spring_up", true);
					mDir = -1;
					mRigidbody->AddForce(Vector2(-1050.0f, 0.0f));
					SonicVelocity = mRigidbody->Velocity();
				}

				if (Input::GetKey(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RSonic_Spring_up", true);
					mDir = 1;
					mRigidbody->AddForce(Vector2(+1050.0f, 0.0f));
					SonicVelocity = mRigidbody->Velocity();
				}
				tr->SetPos(pos);

			}
			else if (mDir == -1)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				if (Input::GetKey(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonic_Spring_up", true);
					mDir = -1;
					mRigidbody->AddForce(Vector2(-1050.0f, 0.0f));
					SonicVelocity = mRigidbody->Velocity();
				}
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RSonic_Spring_up", true);
					mDir = 1;
					mRigidbody->AddForce(Vector2(+1050.0f, 0.0f));
					SonicVelocity = mRigidbody->Velocity();
				}
				tr->SetPos(pos);
			}
		}

		void Sonic::lookup()
		{
			if (Input::GetKeyUp(eKeyCode::UP))
			{
				mState = eSonicState::Idle;
				if (Input::GetKeyUp(eKeyCode::UP) && mDir == 1)
					mAnimator->Play(L"RSonicStand", true);
				else if (Input::GetKeyUp(eKeyCode::UP) && mDir == -1)
					mAnimator->Play(L"LSonicStand", true);
			}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState = eSonicState::Sit;
				if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == 1)
					mAnimator->Play(L"RSonicSit", true);
				else if (Input::GetKeyDown(eKeyCode::DOWN) && mDir == -1)
					mAnimator->Play(L"LSonicSit", true);
			}


			else if (Input::GetKeyDown(eKeyCode::RIGHT)
				|| Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState = eSonicState::Move;
				if (Input::GetKeyDown(eKeyCode::RIGHT))
					mAnimator->Play(L"RSonicWalk", true);
				else if (Input::GetKeyDown(eKeyCode::LEFT))
					mAnimator->Play(L"LSonicWalk", true);
			}

		}

		void Sonic::sit()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			if (Input::GetKeyUp(eKeyCode::DOWN))
			{
				mState = eSonicState::Idle;
				if (Input::GetKeyUp(eKeyCode::DOWN) && mDir == 1)
					mAnimator->Play(L"RSonicStand", true);
				else if (Input::GetKeyUp(eKeyCode::DOWN) && mDir == -1)
					mAnimator->Play(L"LSonicStand", true);
			}
			else if (Input::GetKeyDown(eKeyCode::UP))
			{
				mState = eSonicState::Lookup;
				if (Input::GetKeyDown(eKeyCode::UP) && mDir == 1)
					mAnimator->Play(L"RSonicLookUp", true);
				else if (Input::GetKeyDown(eKeyCode::UP) && mDir == -1)
					mAnimator->Play(L"LSonicLookUp", true);
			}
			else if (Input::GetKeyDown(eKeyCode::RIGHT)
				|| Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState = eSonicState::Move;
				if (Input::GetKeyDown(eKeyCode::RIGHT))
					mAnimator->Play(L"RSonicWalk", true);
				if (Input::GetKeyDown(eKeyCode::LEFT))
					mAnimator->Play(L"LSonicWalk", true);
			}

			//RSonicSpin
			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				mState = eSonicState::Spin;
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicSpin", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					mAnimator->Play(L"LSonicSpin", true);
					mDir = -1;
				}
			}
		}

		void Sonic::spin()
		{
			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicSpin", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					mAnimator->Play(L"LSonicSpin", true);
					mDir = -1;
				}
			}
			

			if (Input::GetKeyUp(eKeyCode::DOWN))
			{
				mState = eSonicState::Dash;
				Vector2 velocity = mRigidbody->GetVelocity();
				if (mDir == 1)
				{
					velocity.x += 1500.0f;
					SonicVelocity = mRigidbody->Velocity();
					mAnimator->Play(L"RSonicRollandJunp", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					velocity.x -= 1500.0f;
					SonicVelocity = mRigidbody->Velocity();
					mAnimator->Play(L"LSonicRollandJunp", true);
					mDir = -1;
				}
				mRigidbody->SetVelocity(velocity);
			}
		}

		void Sonic::twojump()
		{
			if (mRigidbody->GetGround())
			{
				mState = eSonicState::Idle;
				if (mDir = 1)
				{
					mAnimator->Play(L"RSonicStand", true);
				}
				else if (mDir = -1)
				{
					mAnimator->Play(L"LSonicStand", true);
				}
				else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
				{
					mState = eSonicState::Move;
					if (Input::GetKeyDown(eKeyCode::RIGHT))
					{
						mAnimator->Play(L"RSonicWalk", true);
						mDir = 1;
					}
					else if (Input::GetKeyDown(eKeyCode::LEFT))
					{
						mAnimator->Play(L"LSonicWalk", true);
						mDir = -1;
					}
				}
			}
		}

		void Sonic::fire_Shield()
		{
			mState = eSonicState::Jump;
			fire_effect = 0;
		}

		void Sonic::electricity_Shield()
		{
			mState = eSonicState::Jump;
			elect_effect = 1;
		}

		void Sonic::water_Shield()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			if (mRigidbody->GetGround())
			{
				water_bounce = 1;
				mState = eSonicState::Jump;
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y = -650.0f;			
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
			}
			tr->SetPos(pos);
		}

		void Sonic::jeep_line()
		{
			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
					if (fly_check == 1)
					{
						fly_check = 0;
					}
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y -= 550.0f;
					velocity.x += 550.0f;
					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					mState = eSonicState::Jump;
					if (mDir == 1)
					{
						mAnimator->Play(L"RSonicRollandJunp", true);
						mDir = 1;
					}

					

					if (mRigidbody->GetGround())
					{
						mState = eSonicState::Idle();
						mAnimator->Play(L"RSonicStand", true);
					}
			
				//if (jeepline == -1)
				//{
				//	Vector2 velocity = mRigidbody->GetVelocity();
				//	velocity.y -= 550.0f;
				//	velocity.x -= 550.0f;
				//	mRigidbody->SetVelocity(velocity);
				//	mRigidbody->SetGround(false);
				//	mState = eSonicState::Jump;
				//	 if (mDir == -1)
				//	{
				//		mAnimator->Play(L"LSonicRollandJunp", true);
				//		mDir = -1;
				//	}
				//}
			
			}
		}

		void Sonic::tails_hanging()
		{
			if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				if (fly_check == 1)
				{
					fly_check = 0;
				}

				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 550.0f;
				velocity.x += 550.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mState = eSonicState::Jump;
				if (mDir == 1)
				{
					mAnimator->Play(L"RSonicRollandJunp", true);
					mDir = 1;
				}

				if (mRigidbody->GetGround())
				{
					mState = eSonicState::Idle();
					mAnimator->Play(L"RSonicStand", true);
				}


			}
		}

		void Sonic::death()
		{
		}

		void Sonic::ending()
		{

			//mRigidbody->SetGround(true);
			time += Time::DeltaTime();
			if (time > 3)
			{			
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();			
				tr->SetPos(pos);

				mState = eSonicState::End;
				mAnimator->Play(L"End_sonic", true);
			}
		}

		void Sonic::endgame()
		{
		}






		void Sonic::circle_Rturn_1()
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			//mRigidbody = GetComponent<Rigidbody>();
			//mRigidbody->SetMass(1.0f);
			//Vector2 TempVel;
			//TempVel = mRigidbody->GetVelocity();
			//mRigidbody->SetVelocity(Vector2{ fabs(TempVel.y) * -1,0.0f });
			//mRigidbody->AddForce(Vector2{ -500.f,0.0f });

			mRigidbody->AddForce(Vector2(0.0f, 150.0f));
			if (Circle_piece == 0)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.y)*-1, 0.0f });
				mRigidbody->SetGravity(Vector2{ 0.0f,500.f });

				int a = 0;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x <=-400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"RSonicRun", true);
				}
				else
				{
					mState = eSonicState::Move;
					mAnimator->Play(L"RSonicWalk", true);
				}		
	
			}

			if (Circle_piece == 2)
			{
				mState = eSonicState::Circle_Rturn_2;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT2", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT2", true);
				}				
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, -500.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Rturn_2()
		{
			mRigidbody->AddForce(Vector2(0.0f, 200.0f));
			if (Circle_piece == 1)
			{
				mState = eSonicState::Circle_Rturn_1;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT1", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT1", true);
				}
			}

			if (Circle_piece == 3)
			{
				mState = eSonicState::Circle_Rturn_3;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT3", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT3", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, -500.0f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Rturn_3()
		{
			mRigidbody->AddForce(Vector2(0.0f, 300.0f));
			if (Circle_piece == 2)
			{
				mState = eSonicState::Circle_Rturn_2;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT2", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT2", true);
				}
			}

			if (Circle_piece == 4)
			{
				mState = eSonicState::Circle_Rturn_4;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT4", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT4", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, -500.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Rturn_4()
		{
			mRigidbody->AddForce(Vector2(0.0f, 350.0f));
			mRigidbody = GetComponent<Rigidbody>();
			mRigidbody->SetMass(1.0f);


			if (Circle_piece == 3)
			{
				mState = eSonicState::Circle_Rturn_3;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT3", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT3", true);
				}
			}

			if (Circle_piece == 5)
			{
				mState = eSonicState::Circle_Rturn_5;
				SonicVelocity = mRigidbody->Velocity();
				mRigidbody->AddForce(Vector2(-11000.0f, 1000.0f));
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT5", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT5", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, 300.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Rturn_5()
		{
			mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
			if (Circle_piece == 4)
			{
				mState = eSonicState::Circle_Rturn_4;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x <= -400)
				{
					mAnimator->Play(L"RSN_RT4", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT4", true);
				}
			}

			if (Circle_piece == 6)
			{
				mState = eSonicState::Circle_Rturn_6;
				mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.x <= -400)
				{
					mAnimator->Play(L"RSN_RT6", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT6", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, 300.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Rturn_6()
		{
			mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
			if (Circle_piece == 5)
			{
				mState = eSonicState::Circle_Rturn_5;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT5", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT5", true);
				}
			}

			if (Circle_piece == 7)
			{
				mState = eSonicState::Circle_Rturn_7;
				mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT7", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT7", true);
				}
			}
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, 300.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Rturn_7()
		{
			mRigidbody->AddForce(Vector2(0.0f, -1000.0f));
			if (Circle_piece == 6)
			{
				mState = eSonicState::Circle_Rturn_6;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"RSN_RT6", true);
				}
				else
				{
					mAnimator->Play(L"RSN_WT6", true);
				}
			}

			if (circlecheck == 0)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ 1500.f, 0.0f });			
				if (SonicVelocity.y >= 400)
				{
					mAnimator->Play(L"RSonicRun", true);
					mState = eSonicState::Run;
				}
				else
				{
					mAnimator->Play(L"RSonicWalk", true);
					mState = eSonicState::Move;
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.0f));

				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.f, 300.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}



		void Sonic::circle_Lturn_1()
		{
			mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
			if (circlecheck == 0)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ -1500.f, 0.0f });
				SonicVelocity = mRigidbody->Velocity();
				mState = eSonicState::Run;
				if (SonicVelocity.y >= -400)
				{
					mAnimator->Play(L"LSonicRun", true);
				}
				else
				{
					mAnimator->Play(L"LSonicWalk", true);
				}			
			}

			if (Circle_piece == 2)
			{
				mState = eSonicState::Circle_Lturn_2;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT2", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT2", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Lturn_2()
		{
			mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
			if (Circle_piece == 1)
			{
				mState = eSonicState::Circle_Lturn_1;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT1", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT1", true);
				}
			}
			if (Circle_piece == 3)
			{
				mState = eSonicState::Circle_Lturn_3;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT3", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT3", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}

		void Sonic::circle_Lturn_3()
		{
			mRigidbody->AddForce(Vector2(0.0f, 1000.0f));			
			if (Circle_piece == 2)
			{
				mState = eSonicState::Circle_Lturn_2;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT2", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT2", true);
				}
			}
			if (Circle_piece == 4)
			{
				mState = eSonicState::Circle_Lturn_4;
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.y) ,fabs(TempVel.y)});
				mRigidbody->AddForce(Vector2(500.0f, 0.0f));

				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT4", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT4", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Lturn_4()
		{
			mRigidbody->AddForce(Vector2(0.0f, 350.0f));
			mRigidbody = GetComponent<Rigidbody>();
			mRigidbody->SetMass(1.0f);
			
			if (Circle_piece == 3)
			{
				mRigidbody->AddForce(Vector2(11000.0f, 1000.0f));
				mState = eSonicState::Circle_Lturn_3;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT3", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT3", true);
				}
			}
			if (Circle_piece == 5)
			{
				mState = eSonicState::Circle_Lturn_5;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT5", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT5", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, 300.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, -300.f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Lturn_5()
		{
			mRigidbody->AddForce(Vector2(0.0f, 300.0f));
	
			if (Circle_piece == 4)
			{
				mState = eSonicState::Circle_Lturn_4;
				mRigidbody->AddForce(Vector2(0.0f, 1000.0f));
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT4", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT4", true);
				}
			}
			if (Circle_piece == 6)
			{
				mState = eSonicState::Circle_Lturn_6;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT6", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT6", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Lturn_6()
		{
			mRigidbody->AddForce(Vector2(0.0f, 200.0f));
			if (Circle_piece == 5)
			{
				mState = eSonicState::Circle_Lturn_5;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT5", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT5", true);
				}
			}
			if (Circle_piece == 7)
			{
				mState = eSonicState::Circle_Lturn_7;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT7", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT7", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				SonicVelocity = mRigidbody->Velocity();
			}

		}

		void Sonic::circle_Lturn_7()
		{
			mRigidbody->AddForce(Vector2(0.0f, 150.0f));
			if (Circle_piece == 0)
			{
				mRigidbody = GetComponent<Rigidbody>();
				mRigidbody->SetMass(1.0f);
				Vector2 TempVel;
				TempVel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity(Vector2{ fabs(TempVel.y), 0.0f });
				if (SonicVelocity.x >= 400)
				{
					mState = eSonicState::Run;
					mAnimator->Play(L"LSonicRun", true);
				}
				else
				{
					mState = eSonicState::Move;
					mAnimator->Play(L"LSonicWalk", true);
				}
			}

			if (Circle_piece == 6)
			{
				mState = eSonicState::Circle_Lturn_6;
				SonicVelocity = mRigidbody->Velocity();
				if (SonicVelocity.y <= -400)
				{
					mAnimator->Play(L"LSN_RT6", true);
				}
				else
				{
					mAnimator->Play(L"LSN_WT6", true);
				}
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mRigidbody->AddForce(Vector2(0.0f, -500.f));
				Vector2 SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				mRigidbody->AddForce(Vector2(0.0f, 500.f));
				SonicVelocity = mRigidbody->Velocity();
			}
		}	
	
}
