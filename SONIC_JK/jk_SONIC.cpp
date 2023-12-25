#include "jk_Sonic.h"
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
#include "jk_Pixel_Ground.h"


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
#include "Dead_line.h"
#include "Deatht_line_act6.h"


#include "jk_Item_Elect.h"
#include "jk_Item_water.h"
#include "jk_Item_Fire.h"
#include "jk_Ring.h"
#include "jk_Ring_Falling.h"

#include "jk_Miniboss.h"
#include "mBoss_Bl_L.h"
#include "mBoss_BL_R.h"
#include "jk_Boss.h"
#include "Bullet_Act1_Down.h"
#include "Bullet_Act1_L_DIA.h"
#include "Bullet_Act1_L_Side.h"
#include "Bullet_Act1_R_DIA.h"
#include "Bullet_Act1_R_Side.h"
#include "boss1_object.h"
#include "act6_bullet1.h"
#include "boss1_body.h"
#include "Second_Boss.h"
#include "Second_boss_bullet.h"
#include "Boss_Arm.h"
#include "Third_Boss.h"


#include "jk_Rino.h"
#include "jk_Monkey.h"
#include "jk_Monkey_Bullet.h"
#include "jk_Cannon.h"
#include "jk_Cannon_Bullet.h"
#include "jk_Snake.h"





int ringpoint = 0;
int Elect = 0;
int Water = 0;
int Fire = 0;
int LIFE_Point = 0;


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
		: Ending_song(nullptr)
		, Sonic_Jump(nullptr)
		, Ring_Have(nullptr)
		, Ring_Lose(nullptr)
		, Brake(nullptr)
		, Spin(nullptr)
		, Last_Boss_f(nullptr)
		, Spike_mc(nullptr)

		, mAnimator(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mRigidbody(nullptr)
		, check(nullptr)

		, SonicVelocity(0.f, 0.f)
		, SonicBrake(0.f, 0.f)
		, elect(nullptr)
		, fire(nullptr)
		, water(nullptr)
		, water_bounce(0)
		, fire_effect(0)
		, elect_effect(0)

		, mState(eSonicState::Idle)
		, mCircle_state(eCircle::Circle_Lturn_1)
		, Tails_call(nullptr)
		, tails_call(0.f, 0.f)
		, mDir(1)
		, check_map(0)
		, circlecheck(0)
		, Circle_piece(0)
		, Ringcheck(0)
		, hurtcheck(0)
		, jeepline(0)
		, fly_check(0)
		, Life(3)
		, end(0)
		, angle(90.f)
		, time(0.f)
		, loopenter(false)
	{
	}
	Sonic::~Sonic()
	{
	}

	void Sonic::Initialize()
	{
		Spin = Resources::Load<Sound>(L"Spin", L"..\\Resources\\Sound\\Sonic\\Spin.wav");
		Brake = Resources::Load<Sound>(L"Brake", L"..\\Resources\\Sound\\Sonic\\Brake.wav");
		Ring_Lose = Resources::Load<Sound>(L"Ring_Lose", L"..\\Resources\\Sound\\Sonic\\Ring_Lose.wav");
		Ring_Have = Resources::Load<Sound>(L"Ring_Have", L"..\\Resources\\Sound\\Sonic\\Ring_Have.wav");
		Sonic_Jump = Resources::Load<Sound>(L"Sonic_Jump", L"..\\Resources\\Sound\\Sonic\\Sonic_Jump.wav");
		Last_Boss_f = Resources::Load<Sound>(L"Last_Boss_f", L"..\\Resources\\Sound\\Last_Boss_f.wav");
		Ending_song = Resources::Load<Sound>(L"Ending_song", L"..\\Resources\\Sound\\Sonic\\Ending_song.wav");
		Spike_mc = Resources::Load<Sound>(L"Spike", L"..\\Resources\\Sound\\Sonic\\Spike.wav");


		Image* mImage = Resources::Load<Image>(L"SONIC", L"..\\Resources\\sonic.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSonicWalk", mImage, Vector2::RSonicWalkLTC, Vector2::RSonicWalksize, Vector2::RSonicWalkSpace, 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicStand", mImage, Vector2::RSonicStandLTC, Vector2::RSonicStandsize, Vector2::RSonicStandSpace, 9, 1, 9, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"RSonicLookUp", mImage, Vector2::RSonicLookUpLTC, Vector2::RSonicLookUpsize, Vector2::RSonicLookUpSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicSit", mImage, Vector2::RSonicSitLTC, Vector2::RSonicSitsize, Vector2::RSonicSitSpace, 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicShock", mImage, Vector2(740, 750), Vector2(52, 52), Vector2(4, 4), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicRun", mImage, Vector2(24, 397), Vector2(52, 52), Vector2(4, 4), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicRollandJunp", mImage, Vector2(248, 397), Vector2(52, 52), Vector2(4, 4), 5, 1, 5, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"RSonicBrake", mImage, Vector2(412, 478), Vector2(52, 52), Vector2(4, 4), 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonicSpin", mImage, Vector2(24, 534), Vector2(62, 52), Vector2(4, 4), 6, 2, 12, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonichurt", mImage, Vector2(956, 530), Vector2(56, 48), Vector2(8, 0), 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonic_Spring_up", mImage, Vector2(412, 912), Vector2(52, 50), Vector2(4, 0), 12, 1, 12, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonic_Push", mImage, Vector2(736, 644), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSonic_Jeep", mImage, Vector2(412, 1451), Vector2(52, 52), Vector2(4, 0), 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Endgind_pose", mImage, Vector2(24, 1492), Vector2(52, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1f);



		Image* mImage1 = Resources::Load<Image>(L"LSONIC", L"..\\Resources\\Lsonic.bmp");
		mAnimator->CreateAnimation(L"LSonicWalk", mImage1, Vector2::LSonicWalkLTC, Vector2::LSonicWalksize, Vector2::LSonicWalkSpace, 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonicStand", mImage1, Vector2::LSonicStandLTC, Vector2::LSonicStandsize, Vector2::LSonicStandSpace, 9, 1, 9, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"LSonicLookUp", mImage1, Vector2::LSonicLookUpLTC, Vector2::LSonicLookUpsize, Vector2::LSonicLookUpSpace, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonicSit", mImage1, Vector2::LSonicSitLTC, Vector2::LSonicSitsize, Vector2::LSonicSitSpace, 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonicRun", mImage1, Vector2(24, 397), Vector2(52, 52), Vector2(4, 4), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonicRollandJunp", mImage1, Vector2(248, 397), Vector2(52, 52), Vector2(4, 4), 5, 1, 5, Vector2::Zero, 0.05f);
		mAnimator->CreateAnimation(L"LSonicBrake", mImage1, Vector2(412, 478), Vector2(52, 52), Vector2(4, 4), 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonicSpin", mImage1, Vector2(24, 534), Vector2(62, 52), Vector2(4, 4), 6, 2, 12, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonichurt", mImage1, Vector2(956, 530), Vector2(56, 48), Vector2(8, 0), 2, 1, 2, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonic_Spring_up", mImage1, Vector2(412, 912), Vector2(52, 50), Vector2(4, 0), 12, 1, 12, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonic_Push", mImage1, Vector2(736, 644), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSonic_Jeep", mImage1, Vector2(412, 1451), Vector2(52, 52), Vector2(4, 0), 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LEndgind_pose", mImage1, Vector2(24, 1492), Vector2(52, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1f);

		Image* mImage_end = Resources::Load<Image>(L"End_sonic", L"..\\Resources\\END_BG.bmp");
		mAnimator->CreateAnimation(L"End_sonic", mImage_end, Vector2(1136, 243), Vector2(72, 96), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);


		//소닉 원회전(오른쪽)
		Image* mImage_RSN = Resources::Load<Image>(L"Rsonic_circle", L"..\\Resources\\Rsonic_circle.bmp");
		//회전달리기
		mAnimator->CreateAnimation(L"RSN_RT1", mImage_RSN, Vector2(262, 175), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT2", mImage_RSN, Vector2(473, 174), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT3", mImage_RSN, Vector2(681, 174), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT4", mImage_RSN, Vector2(50, 244), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT5", mImage_RSN, Vector2(262, 240), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT6", mImage_RSN, Vector2(474, 240), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_RT7", mImage_RSN, Vector2(682, 240), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		//회전걷기
		mAnimator->CreateAnimation(L"RSN_WT1", mImage_RSN, Vector2(466, 298), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT2", mImage_RSN, Vector2(50, 362), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT3", mImage_RSN, Vector2(466, 362), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT4", mImage_RSN, Vector2(49, 423), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT5", mImage_RSN, Vector2(466, 422), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT6", mImage_RSN, Vector2(50, 486), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"RSN_WT7", mImage_RSN, Vector2(466, 486), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);

		//소닉 원회전(왼쪽)
		Image* mImage_LSN = Resources::Load<Image>(L"Lsonic_circle", L"..\\Resources\\Lsonic_circle.bmp");
		//회전달리기
		mAnimator->CreateAnimation(L"LSN_RT7", mImage_LSN, Vector2(262, 175), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT6", mImage_LSN, Vector2(473, 174), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT5", mImage_LSN, Vector2(681, 174), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT4", mImage_LSN, Vector2(50, 244), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT3", mImage_LSN, Vector2(262, 240), Vector2(52, 51), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT2", mImage_LSN, Vector2(474, 240), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_RT1", mImage_LSN, Vector2(682, 240), Vector2(55, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		//회전걷기							
		mAnimator->CreateAnimation(L"LSN_WT7", mImage_LSN, Vector2(466, 298), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT6", mImage_LSN, Vector2(50, 362), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT5", mImage_LSN, Vector2(466, 362), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT4", mImage_LSN, Vector2(49, 423), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT3", mImage_LSN, Vector2(466, 422), Vector2(53, 55), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT2", mImage_LSN, Vector2(50, 486), Vector2(52, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"LSN_WT1", mImage_LSN, Vector2(466, 486), Vector2(59, 49), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1f);

		mAnimator->Play(L"RSonicStand", true);



		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(80.0f, 120.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.15f) * size.y });


		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}

	void Sonic::Update()
	{
		circlecheck = check->GetgroundCh();
		Circle_piece = check->GetCicle_piece();
		check_map = check->Get_map_check();

		ringpoint = Ringcheck;
		LIFE_Point = Life;
		int a = 0;

		if (check_map >= 1)
		{
			Ringcheck = ringpoint;
			Life = LIFE_Point;
		}

		Transform* tr = GetComponent<Transform>();




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
		}


		if (Input::GetKeyDown(eKeyCode::M))
		{
			mState = eSonicState::Idle;
		}



		switch (mState)
		{
		case jk::Sonic::eSonicState::Idle:
			idle();
			break;

		case jk::Sonic::eSonicState::Move:
			move();
			break;

		case jk::Sonic::eSonicState::Run:
			run();
			break;

		case jk::Sonic::eSonicState::Jump:
			jump();
			break;

		case jk::Sonic::eSonicState::Sit:
			sit();
			break;

		case jk::Sonic::eSonicState::Spin:
			spin();
			break;

		case jk::Sonic::eSonicState::Dash:
			dash();
			break;

		case jk::Sonic::eSonicState::Brake:
			brake();
			break;

		case jk::Sonic::eSonicState::Circle:
			circle();
			break;

		case jk::Sonic::eSonicState::Lookup:
			lookup();
			break;

		case jk::Sonic::eSonicState::Push:
			push();
			break;

		case jk::Sonic::eSonicState::Attack:
			attack();
			break;

		case jk::Sonic::eSonicState::Hurt:
			hurt();
			break;

		case jk::Sonic::eSonicState::HitWaiting:
			hitwaiting();
			break;

		case jk::Sonic::eSonicState::Spring_Jump:
			spring_jump();
			break;

		case jk::Sonic::eSonicState::Cylinder_move:
			cylinder_move();
			break;


		case jk::Sonic::eSonicState::Twojump:
			twojump();
			break;

		case jk::Sonic::eSonicState::Jeep_line:
			jeep_line();
			break;

		case jk::Sonic::eSonicState::Tails_Hanging:
			tails_hanging();
			break;

		case jk::Sonic::eSonicState::Fire_Shield:
			fire_Shield();
			break;

		case jk::Sonic::eSonicState::Electricity_Shield:
			electricity_Shield();
			break;

		case jk::Sonic::eSonicState::Water_Shield:
			water_Shield();
			break;

		case jk::Sonic::eSonicState::Death:
			death();
			break;

		case jk::Sonic::eSonicState::GameOver:
			gameover();
			break;

		case jk::Sonic::eSonicState::EMDING:
			ending();
			break;

		case jk::Sonic::eSonicState::End:
			endgame();
			break;

		default:
			break;
		}

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
			if ((tailsState == Tails::eTailsState::Fly_Waiting) || (tailsState == Tails::eTailsState::Fly_Pursue))
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

			mState = eSonicState::Idle;
			if (mDir == 1)
				mAnimator->Play(L"RSonicStand", true);
			else
				mAnimator->Play(L"LSonicStand", true);
		}

		//Spring Up 충돌처리
		if (Spring_Up* spring_up = dynamic_cast<Spring_Up*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = 0.0f;
			velocity.y -= 1350.0f;
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


			if (sonic_pos.y < Spring_L.y)
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
					Spike_mc->Play(false);
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
					Spike_mc->Play(false);
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
			if (mState == eSonicState::Run)
			{
				mState = eSonicState::Run;

			}
			else
			{
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
		}

		//Cylinder 충돌처리
		if (Cylinder* cylinder = dynamic_cast<Cylinder*>(other->GetOwner()))
		{
			if (mDir == 1)
			{
				mState = eSonicState::Cylinder_move;
				mAnimator->Play(L"LSonic_Spring_up", true);
			}
			else if (mDir == -1)
			{
				mState = eSonicState::Cylinder_move;
				mAnimator->Play(L"LSonic_Spring_up", true);
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
				if (mSonic_colpos.x < mRockSmall_colpos.x)
				{
					mRigidbody->SetVelocity(Vector2{ 0.f,0.f });

					sonic_pos.x = mRockSmall_colpos.x - mRockSmall_Col->GetSize().x * 0.6f;

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

					sonic_Pos.x = mRockMiddle_Pos.x - mRockMiddle_Col->GetSize().x * 0.6f;

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

					sonic_Pos.x = mRockBig_colPos.x - mRockBig_Col->GetSize().x * 0.6f;

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

		if (Dead_line* dead_line = dynamic_cast<Dead_line*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 sonic_pos = tr->GetPos();

			sonic_pos = Vector2{ 19920.f, 3756.f };
			tr->SetPos(sonic_pos);
		}

		if (Deatht_line_act6* dead_line = dynamic_cast<Deatht_line_act6*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 sonic_pos = tr->GetPos();

			sonic_pos = Vector2{ 14250.f,5550.f };
			tr->SetPos(sonic_pos);
		}


		//아이템 충돌★
			//ITEM(ELECT) 충돌처리
		if (Item_Elect* electitem = dynamic_cast<Item_Elect*>(other->GetOwner()))
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
			Ring_Have->Play(false);
			Ringcheck += 1;
			ringpoint += 1;
		}

		if (Ring_Falling* ring = dynamic_cast<Ring_Falling*>(other->GetOwner()))
		{
			Ring_Have->Play(false);
			Ringcheck += 1;
			ringpoint += 1;
		}


		//Monster collision★				
		if (Monster* Mon = dynamic_cast<Monster*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 Monpos = Mon->Getpos_monster();
			//Vector2 rinopos = rino->Getmonster_pos();


			if (!((mState == eSonicState::Spin) || (mState == eSonicState::Jump) || (mState == eSonicState::Dash) || (mState == eSonicState::Hurt) || (Elect == 1) || (Water == 1) || (Fire == 1)))
			{
				if (Ringcheck == 0)
				{
					mState = eSonicState::Death;
					mAnimator->Play(L"RSonicShock", true);

					mRigidbody->SetVelocity(Vector2(0.f, -550.f));
					mRigidbody->SetGround(false);
					Life = Life - 1;
				}
				else if (Ringcheck >= 1)
				{
					Ring_Lose->Play(false);
					if (Monpos.x > pos.x)
					{
						hurtcheck = 1;
						mAnimator->Play(L"RSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity -= (300.0f, 500.0f);
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;


						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
					else if (Monpos.x < pos.x)
					{
						hurtcheck = -1;
						mAnimator->Play(L"LSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity.x += 300.0f;
						velocity.y -= 500.0f;
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;

						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
				}
			}
			else
			{
				pos.y = pos.y + 120;
				if (pos.y < Monpos.y)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = 0.0f;
					velocity.y = -350.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
			}

		}

		//Bullet collision★	
		if (Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 bullet_pos = bullet->GetComponent<Transform>()->GetPos();

			if (!(mState == eSonicState::Hurt) || (Elect == 1) || (Water == 1) || (Fire == 1))
			{
				if (Ringcheck == 0)
				{
					mState = eSonicState::Death;
					mAnimator->Play(L"RSonicShock", true);

					mRigidbody->SetVelocity(Vector2(0.f, -550.f));
					mRigidbody->SetGround(false);
					Life = Life - 1;
				}
				else if (Ringcheck >= 1)
				{
					Ring_Lose->Play(false);
					if (bullet_pos.x > pos.x)
					{
						hurtcheck = 1;
						mAnimator->Play(L"RSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity -= (300.0f, 500.0f);
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;


						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;

					}
					else if (bullet_pos.x < pos.x)
					{
						hurtcheck = -1;
						mAnimator->Play(L"LSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity.x += 300.0f;
						velocity.y -= 500.0f;
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;

						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}

				}
			}
		}

		// Boss & MiniBoss 
		if (Minibos* minibos = dynamic_cast<Minibos*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 minibos_pos = minibos->GetComponent<Transform>()->GetPos();


			if (!((mState == eSonicState::Spin) || (mState == eSonicState::Jump) || (mState == eSonicState::Dash) || (mState == eSonicState::Hurt) || (Elect == 1) || (Water == 1) || (Fire == 1)))
			{
				if (Ringcheck == 0)
				{
					mState = eSonicState::Death;
					mAnimator->Play(L"RSonicShock", true);

					mRigidbody->SetVelocity(Vector2(0.f, -550.f));
					mRigidbody->SetGround(false);
					Life = Life - 1;
				}
				else if (Ringcheck >= 1)
				{
					Ring_Lose->Play(false);
					if (minibos_pos.x > pos.x)
					{
						hurtcheck = 1;
						mAnimator->Play(L"RSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity -= (300.0f, 500.0f);
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;


						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
					else if (minibos_pos.x < pos.x)
					{
						hurtcheck = -1;
						mAnimator->Play(L"LSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(0.0f, 0.0f);
						velocity.x += 300.0f;
						velocity.y -= 500.0f;
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;

						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
				}
			}
			else
			{
				pos.y = pos.y + 120;
				if (pos.y < minibos_pos.y)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = 0.0f;
					velocity.y = -350.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
				else if (pos.x < minibos_pos.x + minibos->GetComponent<Transform>()->GetScale().x / 2)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.x = 0.0f;
					velocity.x = -100.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
				else if (pos.x > minibos_pos.x)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.x = 0.0f;
					velocity.x = 100.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
			}
		}

		if (Boss* boss = dynamic_cast<Boss*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 boss_pos = boss->GetComponent<Transform>()->GetPos();

			if (!((mState == eSonicState::Spin) || (mState == eSonicState::Jump) || (mState == eSonicState::Dash) || (mState == eSonicState::Hurt) || (Elect == 1) || (Water == 1) || (Fire == 1)))
			{
				if (Ringcheck == 0)
				{
					mState = eSonicState::Death;
					mAnimator->Play(L"RSonicShock", true);

					mRigidbody->SetVelocity(Vector2(0.f, -550.f));
					mRigidbody->SetGround(false);
					Life = Life - 1;
				}
				else if (Ringcheck >= 1)
				{
					Ring_Lose->Play(false);
					if (boss_pos.x > pos.x)
					{
						hurtcheck = 1;
						mAnimator->Play(L"RSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(-100.0f, -500.0f);
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;


						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
					else if (boss_pos.x < pos.x)
					{
						hurtcheck = -1;
						mAnimator->Play(L"LSonichurt", true);
						Vector2 velocity = mRigidbody->GetVelocity();
						velocity = Vector2(100.0f, -500.0f);		
						mRigidbody->SetGround(false);
						mRigidbody->SetVelocity(velocity);
						mState = eSonicState::Hurt;


						if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
						{
							ring_drop_Small();
						}
						else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
						{
							ring_drop_Midium();
						}
						else
						{
							ring_drop_Large();
						}
						Ringcheck = 0;
					}
				}
			}
			else
			{
				Vector2 upattack = pos;
				upattack.y = upattack.y + 120;
				if (upattack.y < boss_pos.y)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = -350.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
				else if ((upattack.y < boss_pos.y) && (pos.x < boss_pos.x))
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.x = 0.0f;
					velocity.y = 0.0f;
					velocity.y = -350.f;
					velocity.x = -250.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}
				else if ((upattack.y < boss_pos.y) && (pos.x > boss_pos.x))
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.x = 0.0f;
					velocity.y = 0.0f;
					velocity.y = -350.f;
					velocity.x = 250.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}

				else if (pos.y > boss_pos.y)
				{
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = 0.0f;
					velocity.y = 350.f;
					mRigidbody->SetGround(false);
					mRigidbody->SetVelocity(velocity);
				}

			}
		}

		// 액트6 1번보스 오브젝트
		if (boss1_object* object = dynamic_cast<boss1_object*>(other->GetOwner()))
		{
			Vector2 object_GR_pos = object->GetComponent<Transform>()->GetPos();
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

		//LASTBOSS_Arm
		if (Boss_Arm* last_boss_arm = dynamic_cast<Boss_Arm*>(other->GetOwner()))
		{
			Vector2 boss_arm_pos = last_boss_arm->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			Vector2 msonic = tr->GetPos();

			if (mState == eSonicState::HitWaiting)
			{
			}
			else
			{
				last_boss_arm->Set_Grap(0);

				if (mDir == 1)
				{
					mState = eSonicState::HitWaiting;
					mAnimator->Play(L"RSonicRollandJunp", true);
				}
				else if (mDir == -1)
				{
					mState = eSonicState::HitWaiting;
					mAnimator->Play(L"LSonicRollandJunp", true);
				}
			}
		}


		//finall_stage 충돌처리
		if (finall_stage* stage = dynamic_cast<finall_stage*>(other->GetOwner()))
		{
			Vector2 fly_machine_pos = stage->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();
			Vector2 msonic = tr->GetPos();

			if (mState == eSonicState::HitWaiting)
			{		
				if (Ringcheck == 0)
				{
					mState = eSonicState::Death;
					mAnimator->Play(L"RSonicShock", true);

					Vector2 velocity = mRigidbody->GetVelocity();
					velocity = Vector2(0.0f, -1000.0f);
					mRigidbody->SetVelocity(velocity);
					mRigidbody->SetGround(false);
					Life = Life - 1;
				}
				else if (Ringcheck >= 1)
				{
					Ring_Lose->Play(false);					
					hurtcheck = 1;
					mAnimator->Play(L"RSonichurt", true);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity = Vector2(0.0f, -1000.0f);
					mRigidbody->SetVelocity(velocity);			
					mRigidbody->SetGround(false);
					mState = eSonicState::Hurt;


					if (mState == Sonic::eSonicState::Hurt && Ringcheck < 10)
					{
						ring_drop_Small();
					}
					else if (mState == Sonic::eSonicState::Hurt && Ringcheck < 50)
					{
						ring_drop_Midium();
					}
					else
					{
						ring_drop_Large();
					}
					Ringcheck = 0;	
				}
			}
			else
			{
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
		}
	}

	void Sonic::OnCollisionStay(Collider* other)
	{
	}

	void Sonic::OnCollisionExit(Collider* other)
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
			Sonic_Jump->Play(false);
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 750.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->AddForce(velocity);
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

	void Sonic::hitwaiting()
	{
	}

	void Sonic::hurt()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mRigidbody->SetFiction(100);


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

	void Sonic::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		mRigidbody->SetFiction(100);
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



		if (Input::GetKey(eKeyCode::LEFT))
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

		if (Input::GetKey(eKeyCode::RIGHT))
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

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Sonic_Jump->Play(false);
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 750.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->AddForce(velocity);
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

				mState = eSonicState::Circle;
				mCircle_state = eCircle::Circle_Rturn_1;
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
			loopenter = true;
			mCircle_state = eCircle::Circle_Rturn_1;
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
				mState = eSonicState::Circle;
				mCircle_state = eCircle::Circle_Lturn_7;
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
			mCircle_state = eCircle::Circle_Lturn_7;
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
			Sonic_Jump->Play(false);
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 750.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->AddForce(velocity);
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
			mState = eSonicState::Circle;
			mCircle_state = eCircle::Circle_Rturn_1;
			loopenter = true;
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
				mState = eSonicState::Circle;
				mCircle_state = eCircle::Circle_Lturn_7;
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
			//mState = Circle::Circle_Lturn_7;
		}

		tr->SetPos(pos);
	}

	void Sonic::circle()
	{

		switch (mCircle_state)
		{
		case jk::Sonic::eCircle::Circle_Rturn_1:circle_Rturn_1();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_2:circle_Rturn_2();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_3:circle_Rturn_3();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_4:circle_Rturn_4();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_5:circle_Rturn_5();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_6:circle_Rturn_6();
			break;

		case jk::Sonic::eCircle::Circle_Rturn_7:circle_Rturn_7();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_1:circle_Lturn_1();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_2:circle_Lturn_2();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_3:circle_Lturn_3();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_4:circle_Lturn_4();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_5:circle_Lturn_5();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_6:circle_Lturn_6();
			break;

		case jk::Sonic::eCircle::Circle_Lturn_7:circle_Lturn_7();
			break;

		default:
			break;
		}


		//if (loopenter == true)
		//{
		//#pragma region 원돌기 공식
		//{
		//	//Vector2 mCenterpos = Vector2(2790.0f * 3, 2700.f);
		//	Vector2 mCenterpos = Vector2(20229.f, 3346.f);

		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 pos = tr->GetPos();

		//	float centerX = mCenterpos.x;
		//	float centerY = mCenterpos.y;
		//	float radius = 220.0f;

		//	SonicVelocity = mRigidbody->Velocity();

		//	if (Input::GetKey(eKeyCode::LEFT))
		//	{
		//		angle += 200.f * static_cast<float>(Time::DeltaTime());
		//		//여기부분을-로바꾸면앞으로+는뒤로
		//		float radian = angle * 3.14f / 180.0f;


		//		float x = centerX + radius * cos(radian);
		//		float y = centerY + radius * sin(radian);
		//		pos.x = x;
		//		pos.y = y;

		//		tr->SetPos(pos);
		//	}
		//	if (Input::GetKey(eKeyCode::RIGHT))
		//	{
		//		angle -= 200.f * static_cast<float>(Time::DeltaTime());
		//		//여기부분을-로바꾸면앞으로+는뒤로
		//		float radian = angle * 3.14f / 180.0f;


		//		float x = centerX + radius * cos(radian);
		//		float y = centerY + radius * sin(radian);
		//		mRigidbody->SetVelocity(Vector2(x, y));

		//		pos.x = x;
		//		pos.y = y;

		//		tr->SetPos(pos);
		//	}
		//}
		//#pragma endregion 
		//}
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
			Sonic_Jump->Play(false);
			Vector2 velocity = mRigidbody->GetVelocity();
			mState = eSonicState::Jump;
			if (mDir == 1)
			{
				velocity.y -= 750.0f;
				velocity.x = velocity.x;
				mDir = 1;
			}
			else if (mDir == -1)
			{
				velocity.y -= 650.0f;
				velocity.x = velocity.x;
				mDir = -1;
			}
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(true);
		}

		if (circlecheck == 1)
		{
			mRigidbody = GetComponent<Rigidbody>();
			mRigidbody->SetMass(1.0f);
			Vector2 TempVel;
			TempVel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity(Vector2{ 0.0f ,fabs(TempVel.x) * -1 });
			mRigidbody->AddForce(Vector2(300.0f, -1000.0f));
			if (Circle_piece == 1)
			{
				mCircle_state = eCircle::Circle_Rturn_1;
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
			loopenter = true;
			//mState = eSonicState::Circle_Rturn_1;
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
				mCircle_state = eCircle::Circle_Lturn_7;
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
			//mState = eSonicState::Circle_Lturn_7;



			tr->SetPos(pos);
			mRigidbody->SetVelocity(velocity);
		}

	}

	void Sonic::brake()
	{
		Brake->Play(false);
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
					mRigidbody->SetFiction(100);
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LSonicWalk", true);
					mDir = -1;
					mRigidbody->SetFiction(100);
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
		if (mDir == 1)
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
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if (mRigidbody->GetVelocity().y >= 0)
		{
			mRigidbody->AddForce(Vector2{ 0.f ,1000.f });
		}



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

		if ((Elect == 1) && (Input::GetKeyDown(eKeyCode::SPACE)))
		{
			mState = eSonicState::Electricity_Shield;
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = -650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			elect_effect = 1;
		}

		if ((Fire == 1) && (Input::GetKeyDown(eKeyCode::SPACE)))
		{
			mState = eSonicState::Fire_Shield;
			Vector2 velocity = mRigidbody->GetVelocity();
			if (mDir == 1)
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

		tr->SetPos(pos);
	}

	void Sonic::spring_jump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mRigidbody->GetVelocity().y >= 0)
		{
			mRigidbody->AddForce(Vector2{ 0.f ,1000.f });
		}

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
				mDir = -1;
				mRigidbody->AddForce(Vector2(-1050.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
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
				//mAnimator->Play(L"LSonic_Spring_up", true);
				mDir = -1;
				mRigidbody->AddForce(Vector2(-1050.0f, 0.0f));
				SonicVelocity = mRigidbody->Velocity();
			}
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				//mAnimator->Play(L"RSonic_Spring_up", true);
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
			Spin->Play(false);
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
			Spin->Play(false);
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
			velocity.y = -850.0f;
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
				mState = eSonicState::Idle;
				mAnimator->Play(L"RSonicStand", true);
			}
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
			velocity.y -= 650.0f;
			velocity.x += 550.0f;
			mRigidbody->SetGravity(Vector2{ 0.f,1000.f });
			mRigidbody->SetFiction(100.f);
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
				mState = eSonicState::Idle;
				mAnimator->Play(L"RSonicStand", true);
			}
		}
	}

	void Sonic::death()
	{
		if (Life <= 0)
		{
			Life;
			mState = eSonicState::GameOver;
		}
		else if (Life >= 0)
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

	}

	void Sonic::gameover()
	{
		Life;
		int  a = 0;
	}

	void Sonic::ending()
	{
		Last_Boss_f->Stop(true);
		Ending_song->Play(true);

		time += static_cast<float>(Time::DeltaTime());
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
		if (Circle_piece == 0)
		{
			SonicVelocity = mRigidbody->Velocity();
			if (SonicVelocity.x <= -400)
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
			mCircle_state = eCircle::Circle_Rturn_2;
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
	}

	void Sonic::circle_Rturn_2()
	{
		if (Circle_piece == 1)
		{
			mCircle_state = eCircle::Circle_Rturn_1;
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
			mCircle_state = eCircle::Circle_Rturn_3;
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
			mCircle_state = eCircle::Circle_Rturn_2;
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
			mCircle_state = eCircle::Circle_Rturn_4;
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
			mCircle_state = eCircle::Circle_Rturn_3;
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
			mCircle_state = eCircle::Circle_Rturn_5;
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
			mCircle_state = eCircle::Circle_Rturn_4;
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
			mCircle_state = eCircle::Circle_Rturn_6;
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
			mCircle_state = eCircle::Circle_Rturn_5;
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
			mCircle_state = eCircle::Circle_Rturn_7;
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
			mCircle_state = eCircle::Circle_Rturn_6;
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
			loopenter = false;
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
			mCircle_state = eCircle::Circle_Lturn_2;
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
			mCircle_state = eCircle::Circle_Lturn_1;
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
			mCircle_state = eCircle::Circle_Lturn_3;
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
			mCircle_state = eCircle::Circle_Lturn_2;
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
			mCircle_state = eCircle::Circle_Lturn_4;
			mRigidbody = GetComponent<Rigidbody>();
			mRigidbody->SetMass(1.0f);
			Vector2 TempVel;
			TempVel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity(Vector2{ fabs(TempVel.y) ,fabs(TempVel.y) });
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
			mCircle_state = eCircle::Circle_Lturn_3;
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
			mCircle_state = eCircle::Circle_Lturn_5;
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
			mCircle_state = eCircle::Circle_Lturn_4;
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
			mCircle_state = eCircle::Circle_Lturn_6;
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
			mCircle_state = eCircle::Circle_Lturn_5;
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
			mCircle_state = eCircle::Circle_Lturn_7;
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
			mCircle_state = eCircle::Circle_Lturn_6;
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



	void Sonic::ring_drop_Small()
	{

		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();

		//const int numRings = 10; // 생성할 링의 개수
		const float minAngle = -45.0f; // 링이 떨어지는 최소 각도
		const float maxAngle = 45.0f; // 링이 떨어지는 최대 각도
		const float distance = 250.0f; // 링이 떨어지는 거리


		for (int i = 0; i < Ringcheck; ++i)
		{
			float angle = RandomFloat(minAngle, maxAngle);
			Vector2 dropDirection = math::Rotate(Vector2{ 0.f,-1.f }, angle);

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
			Vector2 dropPos = tr->GetPos() + (dropDirection * distance);
			ring->GetComponent<Transform>()->SetPos(dropPos);
		}
	}

	void Sonic::ring_drop_Midium()
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

	void Sonic::ring_drop_Large()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();

		const int numRings = 30; // 생성할 링의 개수
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
