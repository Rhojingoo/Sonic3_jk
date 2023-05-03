#include "Jeepline_play.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"
#include "jk_Clean_wall.h"

float slope(Vector2 start, Vector2 final)
{
	float value = (final.y - start.y) / (final.x - start.x);
	return value;
}

namespace jk
{
	Jeepline_play::Jeepline_play()
		:jeepline_Speed(500)
		, Start_jeepline(Vector2{0.f,0.f})
		, Final_jeepline(Vector2{ 0.f,0.f })
	{
	}
	Jeepline_play::~Jeepline_play()
	{
	}
	void Jeepline_play::Initialize()
	{//120,362
		//24,72
		mImage = Resources::Load<Image>(L"Jeep_line", L"..\\Resources\\JEEP_LINE.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Jeep_line_play", mImage, Vector2(120, 362), Vector2(24, 72), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);

		//Start_jeepline = Vector2(6580.f, 2940.f);
		//Final_jeepline = Vector2(8715.f, 3460.f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(72.0f, 35.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (3.5f) * size.y });



		mState = eState::Idle; ;
		mAnimator->Play(L"Jeep_line_play", false);

		Gameobject::Initialize();
	}
	void Jeepline_play::Update()
	{
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		switch (mState)
		{
	
		case jk::Jeepline_play::eState::Idle:idle();
			break;

		case jk::Jeepline_play::eState::Move:move();
			break;	
		
		
		default:
			break;
		}

	

		Gameobject::Update();
	}

	void Jeepline_play::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Jeepline_play::Release()
	{
		Gameobject::Release();
	}



	void Jeepline_play::OnCollisionEnter(Collider* other)
	{
		if(Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true); 
		}

		if (Clean_wall* clean_wall = dynamic_cast<Clean_wall*>(other->GetOwner()))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(Final_jeepline);
			mState = eState::Idle;
		}
	}


	void Jeepline_play::OnCollisionStay(Collider* other)
	{

		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_Pos = mSonic_Col->Getpos();
			Collider* Jeep_line_Col = this->GetComponent<Collider>();
			Vector2 Jeep_line_Pos = Jeep_line_Col->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();
			rb->SetVelocity(Vector2{ 0.f,0.f });

			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				mState = eState::Move;
				sonic_Pos = Jeep_line_Pos;				
				sonicTr->SetPos(sonic_Pos);

			}
			//else if (Clean_wall* clean_wall = dynamic_cast<Clean_wall*>(other->GetOwner()))
			//{
			//	Transform* tr = GetComponent<Transform>();
			//	Vector2 pos = tr->GetPos();
			//	tr->SetPos(Final_jeepline);
			//	mState = eState::Idle;
			//}
			else
			{
				rb->SetGround(false);
				Vector2 velocity = rb->GetVelocity();
				velocity.x += 250.f;
				velocity.y -= 250.f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
				sonic_Pos = sonicTr->GetPos();
				sonic_Pos = sonic_Pos + Vector2{ 55.f ,-55.f };
				sonicTr->SetPos(sonic_Pos);
			}
		}
	}

	void Jeepline_play::OnCollisionExit(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		mState = eState::Idle;
	}


	void Jeepline_play::idle()
	{

	}


	void Jeepline_play::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		float m = slope(Start_jeepline, Final_jeepline);
		float b = pos.y - m * pos.x;	

		float newposX = pos.x + jeepline_Speed * Time::DeltaTime();
		float newY = m * newposX + b;
		
		Vector2 newPos = Vector2(newposX, newY);
		pos = newPos;
		

		//ÁÂÇ¥¼³Á¤ ¾ÈµÊ
		//if (newposX >= 8715.f)
		//{
		//	mState = eState::Idle;
		//}

		tr->SetPos(pos);
	}
}


