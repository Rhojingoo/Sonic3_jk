#include "jk_Tails.h"
#include "jk_Time.h"
#include "jk_SONIC.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
//#include "yaBaseBullet.h"
#include "jk_Scene.h"
#include "jk_BaseBullet.h"
#include "jk_Ground.h"
#include "Rigidbody.h"
#include "jk_Monster.h"
#include "jk_BaseBullet.h"
#include "jk_Scene.h"

#include "jk_Object.h"
#include "jk_tail_jump.h"
#include "finall_stage.h"

namespace jk
{
	Tails::Tails(Gameobject* owner)
		:TailsmDir(1)
		, TailsVelocity(0.f, 0.f)
		, fallingcheck(0.f, 0.f)
		, falling(0)
		, circlecheck(0)
		, Circle_piece(0)
		, fly_check(0)
		, pursue_boss(0)
		,end(0)
	{
		mOwner = owner;
	
		Transform* tr = GetComponent<Transform>();
		
		tr->SetPos(Vector2{ 2790.0f * 3, 3200.f });

		
	}

	Tails::~Tails()
	{
	}

	void Tails::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2{ 19718.f, 3450.f });
		//tr->SetPos(Vector2{ 2790.0f * 3, 3200.f });
		//tr->SetPos(Vector2{ 2790.0f * 3, 3200.f });

		Image* mImage = Resources::Load<Image>(L"RTails", L"..\\Resources\\RTails.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RTailsWalk", mImage, Vector2(24, 647), Vector2(58, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsStand", mImage, Vector2(25, 24), Vector2(54, 48), Vector2(5, 0), 20, 1, 20, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsSit", mImage, Vector2(294, 87), Vector2(54, 48), Vector2(5, 0), 5, 1, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsLookUp", mImage, Vector2(25, 87), Vector2(54, 48), Vector2(5, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsDeath", mImage, Vector2(968, 647), Vector2(52, 48), Vector2(4, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsBrake", mImage, Vector2(403, 144), Vector2(54, 48), Vector2(5, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsRun", mImage, Vector2(504, 647), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsJump", mImage, Vector2(35, 341), Vector2(64, 60), Vector2(17, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsJumpDw", mImage, Vector2(35, 267), Vector2(64, 60), Vector2(17, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsMJ", mImage, Vector2(35, 424), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsMJDW", mImage, Vector2(35, 496), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsSpin", mImage, Vector2(590, 337), Vector2(62, 48), Vector2(4, 0), 7, 1, 7, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsDash", mImage, Vector2(29, 207), Vector2(64, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailsFly", mImage, Vector2(834, 87), Vector2(54, 48), Vector2(5, 0), 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Endgind_pose", mImage, Vector2(820, 802), Vector2(52, 48), Vector2(4, 0), 2, 1, 2, Vector2::Zero, 0.1);





		Image* mImage1 = Resources::Load<Image>(L"LTails", L"..\\Resources\\LTails.bmp");
		//Animator* animator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"LTailsWalk", mImage1, Vector2(24, 647), Vector2(58, 48), Vector2(4, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsStand", mImage1, Vector2(25, 24), Vector2(54, 48), Vector2(5, 0), 20, 1, 20, Vector2::Zero, 0.3);
		mAnimator->CreateAnimation(L"LTailsSit", mImage1, Vector2(294, 87), Vector2(54, 48), Vector2(5, 0), 5, 1, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsLookUp", mImage1, Vector2(25, 87), Vector2(54, 48), Vector2(5, 0), 5, 1, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsBrake", mImage1, Vector2(403, 144), Vector2(54, 48), Vector2(5, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsRun", mImage1, Vector2(504, 647), Vector2(52, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsJump", mImage1, Vector2(35, 341), Vector2(64, 60), Vector2(17, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsJumpDw", mImage1, Vector2(35, 267), Vector2(64, 60), Vector2(17, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsMJ", mImage1, Vector2(35, 424), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsMJDW", mImage1, Vector2(35, 496), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsSpin", mImage1, Vector2(590, 337), Vector2(62, 48), Vector2(4, 0), 7, 1, 7, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsDash", mImage1, Vector2(29, 207), Vector2(64, 48), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailsFly", mImage1, Vector2(834, 87), Vector2(54, 48), Vector2(4, 0), 2, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LEndgind_pose", mImage1, Vector2(820, 802), Vector2(52, 48), Vector2(4, 0), 2, 1, 2, Vector2::Zero, 0.1);



		Image* mImage_end = Resources::Load<Image>(L"End_tails", L"..\\Resources\\END_BG.bmp");
		mAnimator->CreateAnimation(L"End_tails", mImage_end, Vector2(1264, 243), Vector2(94, 96), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);



		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(80.0f, 100.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.0f) * size.x, (0.0f) * size.y });

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		mAnimator->Play(L"RTailsStand", true);

		Gameobject::Initialize();
	}


	void Tails::Update()
	{
		sonicV = mOwner->GetComponent<Transform>()->GetPos();
		if (pursue_boss == 1)
		{
			mState = eTailsState::Jump;
			mAnimator->Play(L"RTailsJump", true);
			TailsmDir = 1;

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 550.f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			pursue_boss = 2;
		}

		if (fly_check == 1)
		{
			mState = eTailsState::Fly_Waiting;
			mAnimator->Play(L"RTailsFly", true);
			fly_check = 2;
		}
		if (fly_check == 3)
		{
			mState = eTailsState::Fly_Ready;
			mAnimator->Play(L"RTailsFly", true);			
		}
		if (fly_check == 4)
		{
			mState = eTailsState::Fly;
			mAnimator->Play(L"RTailsFly", true);
			fly_check = 2;
		}
		if (fly_check == 4)
		{
			mState = eTailsState::Fly;
			mAnimator->Play(L"RTailsFly", true);
		
		}
		if (fly_check == 5)
		{
			mState = eTailsState::Idle;
			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsStand", true);
			}
			fly_check = 0;
		}


		if (end == 1)
		{
			mState = eTailsState::EMDING;
	 		if (TailsmDir ==  1)
				mAnimator ->Play(L"Endgind_pose", false);//엔딩포즈
			else
				mAnimator->Play(L"LEndgind_pose", false);//엔딩포즈

		}


		switch (mState)
		{
		case jk::Tails::eTailsState::Idle:idle();
			break;

		case jk::Tails::eTailsState::Move:move();
			break;

		case jk::Tails::eTailsState::Run:run();
			break;

		case jk::Tails::eTailsState::Dash:dash();
			break;

		case jk::Tails::eTailsState::Brake:brake();
			break;

		case jk::Tails::eTailsState::Jump:jump();
			break;

		case jk::Tails::eTailsState::Movejump:movejump();
			break;

		case jk::Tails::eTailsState::Jumpfalling:jumpfalling();
			break;

		case jk::Tails::eTailsState::Sit:sit();
			break;

		case jk::Tails::eTailsState::Spin:spin();
			break;

		case jk::Tails::eTailsState::Lookup:lookup();
			break;

		case jk::Tails::eTailsState::Twojump:twojump();
			break;

		case jk::Tails::eTailsState::Shield:shield();
			break;

		case jk::Tails::eTailsState::Fly:fly();
			break;

		case jk::Tails::eTailsState::Fly_Ready:fly_Ready();
			break;

		case jk::Tails::eTailsState::Fly_Pursue:fly_pursue();
			break;

		case jk::Tails::eTailsState::Fly_Waiting:fly_waiting();
			break;			

		case jk::Tails::eTailsState::EMDING:ending();
			break;

		case jk::Tails::eTailsState::End:endgame();
			break;





		case jk::Tails::eTailsState::Circle_Rturn_1:circle_Rturn_1();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_2:circle_Rturn_2();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_3:circle_Rturn_3();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_4:circle_Rturn_4();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_5:circle_Rturn_5();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_6:circle_Rturn_6();
			break;

		case jk::Tails::eTailsState::Circle_Rturn_7:circle_Rturn_7();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_1:circle_Lturn_1();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_2:circle_Lturn_2();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_3:circle_Lturn_3();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_4:circle_Lturn_4();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_5:circle_Lturn_5();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_6:circle_Lturn_6();
			break;

		case jk::Tails::eTailsState::Circle_Lturn_7:circle_Lturn_7();
			break;
		

		default:
			break;
		}

		Gameobject::Update();

	}

	void Tails::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Tails::Release()
	{
		Gameobject::Release();
	}

	void Tails::OnCollisionEnter(Collider* other)
	{
		if (Monster* rino = dynamic_cast<Monster*>(other->GetOwner()))
		{
			mAnimator->Play(L"RTailsDeath", true);
		}

		if (BaseBullet* bullet = dynamic_cast<BaseBullet*>(other->GetOwner()))
		{
			mAnimator->Play(L"RTailsDeath", true);
		}

		if (Ground* playgr = dynamic_cast<Ground*>(other->GetOwner()))
		{
			mState = eTailsState::Idle;
			if (TailsmDir = 1)
			{
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (TailsmDir = -1)
			{
				mAnimator->Play(L"LTailsStand", true);
			}
			/*else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState = eTailsState::Move;
				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RTailsWalk", true);
					TailsmDir = 1;
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LTailsWalk", true);
					TailsmDir = -1;
				}
			}*/
		}

		if (finall_stage* stage = dynamic_cast<finall_stage*>(other->GetOwner()))
		{
			Vector2 fly_machine_pos = stage->GetComponent<Transform>()->GetPos();
			Transform* tr = GetComponent<Transform>();						
			mRigidbody->SetGround(true);

			if (TailsmDir == 1)
			{
				mState = eTailsState::Idle;
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (TailsmDir == -1)
			{
				mState = eTailsState::Idle;
				mAnimator->Play(L"LTailsStand", true);
			}
		}
	}

	void Tails::OnCollisionStay(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 tails_pos = tr->GetPos();

		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{		
			Sonic::eSonicState sonicState = sonic->Getsonicstate();
			if (sonicState == Sonic::eSonicState::Tails_Hanging) 
			{			
				sonicV = Vector2{ tails_pos.x,tails_pos.y + 90 };	

				if (sonicV.y > tails_pos.y + 90)
				{
					sonicV.y = tails_pos.y + 90;
				}

				sonic->GetComponent<Transform>()->SetPos(sonicV);
				mState = eTailsState::Fly_Pursue;
			}
		}
	}

	void Tails::OnCollisionExit(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			if (sonic->Getsonicstate() == Sonic::eSonicState::Idle)
			{
				//fly_check = -1;
				//mState = eTailsState::Fly;
				//mAnimator->Play(L"RTailsFly", true);
			}
		}		
	}

	void Tails::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mRigidbody->SetFiction(100);


		if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			
			mState = eTailsState::Move;
			if (Input::GetKeyDown(eKeyCode::RIGHT))
				mAnimator->Play(L"RTailsWalk", true);
			else if (Input::GetKeyDown(eKeyCode::LEFT))
				mAnimator->Play(L"LTailsWalk", true);
		}

		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			mState = eTailsState::Lookup;
			if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == 1)
				mAnimator->Play(L"RTailsLookUp", true);
			else if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == -1)
				mAnimator->Play(L"LTailsLookUp", true);
		}

		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eTailsState::Sit;
			if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == 1)
				mAnimator->Play(L"RTailsSit", true);
			else if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == -1)
				mAnimator->Play(L"LTailsSit", true);
		}

		else if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			mState = eTailsState::Jump;
			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsJump", true);
				TailsmDir = 1;
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsJump", true);
				TailsmDir = -1;
			}
		}
		 
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			float fDist = abs(sonicV.x - pos.x);

			if (sonicV.x < pos.x)
			{
				if (fDist > 80.f)
				{
					mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
					TailsVelocity = mRigidbody->Velocity();
					mState = eTailsState::Move;
					mAnimator->Play(L"LTailsWalk", true);
					TailsmDir = -1;
				}

			}
			else if (sonicV.x > pos.x)
			{
				if (fDist > 80.f)
				{
					mRigidbody->AddForce(Vector2(+500.0f, 0.0f));
					TailsVelocity = mRigidbody->Velocity();
					mState = eTailsState::Move;
					mAnimator->Play(L"RTailsWalk", true);
					TailsmDir = 1;
				}
			}

			float fDistX = abs(sonicV.x - pos.x);
			float fDistY = abs(sonicV.y - pos.y);
			 if ((fDistX > 2000.f) || (fDistY > 2000.f))
			{
				pos.x = sonicV.x;
				pos.y = sonicV.y - 550.f;
				mState = eTailsState::Fly;

				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsFly", true);
				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsFly", true);
				}
			}
			tr->SetPos(pos);
		}
	}


	void Tails::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			mState = eTailsState::Idle;
			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsStand", true);
			}
		}

		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			mState = eTailsState::Lookup;
			if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsLookUp", true);
			}
			else if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsLookUp", true);
			}
		}

		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eTailsState::Sit;
			if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsSit", true);

			}
			else if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsSit", true);

			}
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		float fDist = abs(sonicV.x - pos.x);

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = eTailsState::Movejump;
			if (TailsmDir == 1)
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsMJ", true);
					TailsmDir = 1;
				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsMJ", true);
					TailsmDir = -1;
				}
		}


		if (sonicV.x < pos.x)
		{
			if (fDist > 81.f)
			{				
				mRigidbody->AddForce(Vector2(-590.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				if (TailsVelocity.x <= -400)
				{
					mState = eTailsState::Run;
					mAnimator->Play(L"LTailsRun", true);
				};
				TailsmDir = -1;
			}
			else if (fDist <= 30.0f)
			{
				pos.x;
				TailsmDir = -1;				
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Idle;
				if (TailsmDir == 1)
					mAnimator->Play(L"RTailsStand", true);
				else
					mAnimator->Play(L"LTailsStand", true);
			}
		}
		else if (sonicV.x > pos.x)
		{
			if (fDist > 81.f)
			{				
				mRigidbody->AddForce(Vector2(+580.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				if (TailsVelocity.x >= 400)
				{
					mState = eTailsState::Run;
					mAnimator->Play(L"RTailsRun", true);
				};
				TailsmDir = 1;
			}
			else if (fDist <= 30.0f)
			{
				pos.x;
				TailsmDir = 1;				
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Idle;
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsStand", true);
				}
				else
				{
					mAnimator->Play(L"LTailsStand", true);
				}
			}

			else if (fDist > 2000.f)
			{
				pos.x = sonicV.x;
				pos.y = sonicV.y - 800.f;
				mState = eTailsState::Fly;
			}

			tr->SetPos(pos);
		}
	}

	void Tails::run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();	

		float fDistX = abs(sonicV.x - pos.x);
		float fDistY = abs(sonicV.y - pos.y);

		if (sonicV.x < pos.x)
		{
			if (fDistX > 151.f)
			{				
				mRigidbody->AddForce(Vector2(-580.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				TailsmDir = -1;
				if ((fDistX > 2000.f) ||(fDistY>2000.f))
				{
					pos.x = sonicV.x;
					pos.y = sonicV.y - 550.f;
					mState = eTailsState::Fly;

					if (TailsmDir == 1)
					{
						mAnimator->Play(L"RTailsFly", true);
					}
					else if (TailsmDir == -1)
					{
						mAnimator->Play(L"LTailsFly", true);
					}
				}


			}
			else if (fDistX <= 50.0f)
			{
				pos.x;
				TailsmDir = -1;				
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Brake;
				if (TailsmDir == 1)
					mAnimator->Play(L"RTailsBrake", true);
				else
					mAnimator->Play(L"LTailsBrake", true);
			}
		}
		else if (sonicV.x > pos.x)
		{
			if (fDistX > 151.f)
			{				
				mRigidbody->AddForce(Vector2(+580.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				TailsmDir = 1;
				if ((fDistX > 2000.f) || (fDistY > 2000.f))
				{
					pos.x = sonicV.x;
					pos.y = sonicV.y - 550.f;
					mState = eTailsState::Fly;				
					if (TailsmDir == 1)
					{
						mAnimator->Play(L"RTailsFly", true);
					}
					else if (TailsmDir == -1)
					{
						mAnimator->Play(L"LTailsFly", true);
					}
				}
			}
			else if (fDistX <= 50.0f)
			{
				pos.x;
				TailsmDir = -1;				
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Brake;
				if (TailsmDir == 1)
					mAnimator->Play(L"RTailsBrake", true);
				else
					mAnimator->Play(L"LTailsBrake", true);
			}
		}
		else if (Input::GetKeyDown(eKeyCode::SPACE))
		{			
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = eTailsState::Movejump;
			if (TailsmDir == 1)
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsMJ", true);
					TailsmDir = 1;
				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsMJ", true);
					TailsmDir = -1;
				}
			mRigidbody->SetVelocity(velocity);
		}

		tr->SetPos(pos);
	}

	void Tails::dash()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		Vector2 velocity = mRigidbody->GetVelocity();


		float fDist = abs(sonicV.x - pos.x);

		if (sonicV.x < pos.x)
		{
			if (fDist > 151.f)
			{				
				mRigidbody->AddForce(Vector2(-580.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				TailsmDir = -1;
			}
			else if (fDist <= 50.0f)
			{
				pos.x;
				TailsmDir = -1;				
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Brake;
				if (TailsmDir == 1)
					mAnimator->Play(L"RTailsBrake", true);
				else
					mAnimator->Play(L"LTailsBrake", true);
			}
		}
		else if (sonicV.x > pos.x)
		{
			if (fDist > 151.f)
			{				
				mRigidbody->AddForce(Vector2(+580.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();
				TailsmDir = 1;
			}
			else if (fDist <= 50.0f)
			{
				pos.x;
				TailsmDir = -1;			
				mRigidbody->SetFiction(15000);
				mState = eTailsState::Brake;
				if (TailsmDir == 1)
					mAnimator->Play(L"RTailsBrake", true);
				else
					mAnimator->Play(L"LTailsBrake", true);
			}
		}
		else if (Input::GetKeyDown(eKeyCode::SPACE))
		{			
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 650.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = eTailsState::Movejump;
			if (TailsmDir == 1)
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsMJ", true);
					TailsmDir = 1;
				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsMJ", true);
					TailsmDir = -1;
				}
			mRigidbody->SetVelocity(velocity);
		}
	
		tr->SetPos(pos);
		mRigidbody->SetVelocity(velocity);
	}	
	
	void Tails::brake()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		
		if (mRigidbody->Velocity() == Vector2{ 0.0f,0.0f })
		{
			mRigidbody->SetFiction(100);
			if (Input::GetKeyDown(eKeyCode::RIGHT)
				|| Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState = eTailsState::Move;
				if (Input::GetKeyDown(eKeyCode::RIGHT))
				{
					mAnimator->Play(L"RTailsWalk", true);
					TailsmDir = 1;
				}
				else if (Input::GetKeyDown(eKeyCode::LEFT))
				{
					mAnimator->Play(L"LTailsWalk", true);
					TailsmDir = -1;
				}
			}

			else if (mRigidbody->Velocity() == Vector2::Zero)
			{
				mState = eTailsState::Idle;
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsStand", true);

				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsStand", true);
				}
			}

			else if (Input::GetKeyDown(eKeyCode::UP))
			{
				mState = eTailsState::Lookup;
				if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == 1)
					mAnimator->Play(L"RTailsLookUp", true);
				else if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == -1)
					mAnimator->Play(L"LTailsLookUp", true);
			}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState = eTailsState::Sit;
				if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == 1)
					mAnimator->Play(L"RTailsSit", false);
				else if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == -1)
					mAnimator->Play(L"lTailsSit", false);
			}

			else if (Input::GetKeyDown(eKeyCode::SPACE))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 600.0f;

				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mState = eTailsState::Jump;
				if (TailsmDir == 1)
				{
					mAnimator->Play(L"RTailsJump", true);
					TailsmDir = 1;
				}
				else if (TailsmDir == -1)
				{
					mAnimator->Play(L"LTailsJump", true);
					TailsmDir = -1;
				}
			}
		}
	}

	void Tails::jump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		Vector2 velocity = mRigidbody->GetVelocity();

		if (velocity.y >= 0.0f)
		{						
			if ((pursue_boss == 0)&&(TailsmDir == 1))
			{
				mRigidbody->AddForce(Vector2{ 0.f ,1000.f });
				mState = eTailsState::Jumpfalling;
				mAnimator->Play(L"RTailsJumpDw", true);
				TailsmDir = 1;
			}
			else if ((pursue_boss == 0) && (TailsmDir == -1))
			{
				mRigidbody->AddForce(Vector2{ 0.f ,1000.f });
				mState = eTailsState::Jumpfalling;
				mAnimator->Play(L"LTailsJumpDw", true);
				TailsmDir = -1;
			}
			else if (pursue_boss == 2)
			{
				mState = eTailsState::Fly_Ready;
				mAnimator->Play(L"RTailsFly", true);
				mRigidbody->SetGround(true);
				TailsmDir = 1;								
				Vector2 pos = tr->GetPos();
				tr->SetPos(pos);
			}
		}
	}

	void Tails::movejump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		Vector2 velocity = mRigidbody->GetVelocity();


		if (velocity.y >= 0.0f)
		{
			mRigidbody->AddForce(Vector2{ 0.f ,1000.f });
			mState = eTailsState::Jumpfalling;

			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsMJDW", true);
				TailsmDir = 1;
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsMJDW", true);
				TailsmDir = -1;
			}
		}

	}

	void Tails::jumpfalling()
	{
		if (mRigidbody->GetGround())
		{
			mState = eTailsState::Idle;
			if (TailsmDir = 1)
			{
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (TailsmDir = -1)
			{
				mAnimator->Play(L"LTailsStand", true);
			}
			//else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
			//{
			//	mState = eTailsState::Move;
			//	if (Input::GetKeyDown(eKeyCode::RIGHT))
			//	{
			//		mAnimator->Play(L"RTailsWalk", true);
			//		TailsmDir = 1;
			//	}
			//	else if (Input::GetKeyDown(eKeyCode::LEFT))
			//	{
			//		mAnimator->Play(L"LTailsWalk", true);
			//		TailsmDir = -1;
			//	}
			//}
		}
	}

	void Tails::lookup()
	{
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mState = eTailsState::Idle;
			if (Input::GetKeyUp(eKeyCode::UP) && TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsStand", true);
			}
			else if (Input::GetKeyUp(eKeyCode::UP) && TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsStand", true);
			}
		}

		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eTailsState::Sit;
			if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == 1)
				mAnimator->Play(L"RTailsSit", true);
			else if (Input::GetKeyDown(eKeyCode::DOWN) && TailsmDir == -1)
				mAnimator->Play(L"LTailsSit", true);
		}


		else if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = eTailsState::Move;
			if (Input::GetKeyDown(eKeyCode::RIGHT))
				mAnimator->Play(L"RTailsWalk", true);
			else if (Input::GetKeyDown(eKeyCode::LEFT))
				mAnimator->Play(L"LTailsWalk", true);
		}

	}

	void Tails::sit()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eTailsState::Idle;
			if (Input::GetKeyUp(eKeyCode::DOWN) && TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsStand", true);			
			}
			else if (Input::GetKeyUp(eKeyCode::DOWN) && TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsStand", true);	
			}
		}

		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			mState = eTailsState::Lookup;
			if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == 1)
				mAnimator->Play(L"RTailsLookUp", true);
			else if (Input::GetKeyDown(eKeyCode::UP) && TailsmDir == -1)
				mAnimator->Play(L"LTailsLookUp", true);
		}

		else if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = eTailsState::Move;
			if (Input::GetKeyDown(eKeyCode::RIGHT))
				mAnimator->Play(L"RTailsWalk", true);
			if (Input::GetKeyDown(eKeyCode::LEFT))
				mAnimator->Play(L"LTailsWalk", true);
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mState = eTailsState::Spin;
			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsSpin", true);
				TailsmDir = 1;
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsSpin", true);
				TailsmDir = -1;
			}
		}

	}

	void Tails::spin()
	{		
		Vector2 velocity = mRigidbody->GetVelocity();
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if (TailsmDir == 1)
			{
				mAnimator->Play(L"RTailsSpin", true);
				TailsmDir = 1;
			}
			else if (TailsmDir == -1)
			{
				mAnimator->Play(L"LTailsSpin", true);
				TailsmDir = -1;
			}
		}

		//RSonicRollandJunp
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eTailsState::Dash;			
			Vector2 velocity = mRigidbody->GetVelocity();
			if (TailsmDir == 1)
			{
				velocity.x += 1000.0f;
				TailsVelocity = mRigidbody->Velocity();
				mAnimator->Play(L"RTailsDash", true);
				TailsmDir = 1;
			}
			else if (TailsmDir == -1)
			{
				velocity.x -= 1000.0f;
				TailsVelocity = mRigidbody->Velocity();
				mAnimator->Play(L"LTailsDash", true);
				TailsmDir = -1;
			}
			mRigidbody->SetVelocity(velocity);
		}
	}

	void Tails::twojump()
	{
	}

	void Tails::shield()
	{
	}

	void Tails::fly()
	{		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		float fDist = abs(sonicV.x - pos.x);		

	 if ((pursue_boss == 0)&& (sonicV.x < pos.x))
		{
			if (fDist > 80.f)
			{
				mRigidbody->AddForce(Vector2(-500.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();					
				mAnimator->Play(L"LTailsFly", true);
				TailsmDir = -1;
			}
			if (mRigidbody->GetGround())
			{
				mState = eTailsState::Idle;
				if (TailsmDir = 1)
				{
					mAnimator->Play(L"RTailsStand", true);
					fly_check = 0;
				}
				else if (TailsmDir = -1)
				{
					mAnimator->Play(L"LTailsStand", true);
					fly_check = 0;
				}
			}
		}
		else if ((pursue_boss == 0) && (sonicV.x > pos.x))
		{
			if (fDist > 80.f)
			{
				mRigidbody->AddForce(Vector2(+500.0f, 0.0f));
				TailsVelocity = mRigidbody->Velocity();					
				mAnimator->Play(L"RTailsFly", true);
				TailsmDir = 1;
			}

			if (mRigidbody->GetGround())
			{
				mState = eTailsState::Idle;
				if (TailsmDir = 1)
				{
					mAnimator->Play(L"RTailsStand", true);
					fly_check = 0;
				}
				else if (TailsmDir = -1)
				{
					mAnimator->Play(L"LTailsStand", true);
					fly_check = 0;
				}
			}
		}

	 if (mRigidbody->GetGround())
	 {
		 mState = eTailsState::Idle;
		 if (TailsmDir = 1)
		 {
			 mAnimator->Play(L"RTailsStand", true);
			 fly_check = 0;
		 }
		 else if (TailsmDir = -1)
		 {
			 mAnimator->Play(L"LTailsStand", true);
			 fly_check = 0;
		 }
	 }
		tr->SetPos(pos);		
	}

	void Tails::fly_Ready()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		sonicV = mOwner->GetComponent<Transform>()->GetPos();
		mRigidbody->SetGround(true);
		tr->SetPos(Vector2{ sonicV.x,sonicV.y - 300.f });
		mState = eTailsState::Fly_Waiting;
	}

	void Tails::fly_pursue()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 250 * Time::DeltaTime();
		mRigidbody->SetGround(true);
		tr->SetPos(pos);

		sonicV = Vector2{ pos.x,pos.y + 90 };

		if (sonicV.y > pos.y + 90)
		{
			sonicV.y = pos.y + 90;
		}
		mOwner->GetComponent<Transform>()->SetPos(sonicV);

		if (fly_check == 2)
		{
			mState = eTailsState::Fly;
			mAnimator->Play(L"RTailsFly", true);
		}


	}

	void Tails::fly_waiting()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		sonicV = mOwner->GetComponent<Transform>()->GetPos();
		mRigidbody->SetGround(true);
		tr->SetPos(pos);

		if (fly_check == 2)
		{
			mState = eTailsState::Fly;
			mAnimator->Play(L"RTailsFly", true);
		}

	}

	void Tails::ending()
	{
	}

	void Tails::endgame()
	{
	}




	void Tails::circle_Rturn_1()
	{
	}
	void Tails::circle_Rturn_2()
	{
	}
	void Tails::circle_Rturn_3()
	{
	}
	void Tails::circle_Rturn_4()
	{
	}
	void Tails::circle_Rturn_5()
	{
	}
	void Tails::circle_Rturn_6()
	{
	}
	void Tails::circle_Rturn_7()
	{
	}


	void Tails::circle_Lturn_1()
	{
	}
	void Tails::circle_Lturn_2()
	{
	}
	void Tails::circle_Lturn_3()
	{
	}
	void Tails::circle_Lturn_4()
	{
	}
	void Tails::circle_Lturn_5()
	{
	}
	void Tails::circle_Lturn_6()
	{
	}
	void Tails::circle_Lturn_7()
	{
	}
}