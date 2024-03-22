#include "Rigidbody.h"
#include "jk_Time.h"
#include "jk_Gameobject.h"
#include "jk_Transform.h"

namespace jk
{
	Rigidbody::Rigidbody()
		:Component(jk_ComponentType::Rigidbody)
		,mMass(0.0f)
		,mForce(Vector2::Zero)
		,mAccelation(Vector2::Zero)
		,mVelocity(Vector2::Zero)
		,MaxSpeed(1200.f)
	{
		mLimitedVelocity.x = 505.0f;
		mLimitedVelocity.y = 505.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 1000.0f);
		mFriction = 100.0f;
	}

	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}

	//1200
	void Rigidbody::Update()
	{

		Speed_Manegement();
		Gravity_management();
		Friction_management();		

		// 속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = pos + mVelocity * static_cast<float>(Time::DeltaTime());
		tr->SetPos(pos);
		mForce.Clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
	void Rigidbody::Release()
	{
	}
	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}

	void Rigidbody::Speed_Manegement()
	{
		//mAccelation = mForce / mMass;
		
		if (mVelocity.x < MaxSpeed)
		{
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
		}
		else if (mVelocity.x >= MaxSpeed)
		{
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
			mVelocity.x = MaxSpeed;
		}
		if (mVelocity.x <= -MaxSpeed)
		{
			mVelocity.x = -MaxSpeed;
		}
	}

	void Rigidbody::Gravity_management()
	{
		if (mbGround)
		{			
			Vector2 gravity = mGravity;						//중력시 벡터를 단위1로 
			gravity.Normalize();			
			float dot = math::Dot(mVelocity, gravity);		//경사면에서의 아래로 이동
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * static_cast<float>(Time::DeltaTime());
		}

		//중력가속도 속도제한
		if (mVelocity.y < MaxSpeed)
		{
		}
		else if (mVelocity.y >= MaxSpeed)
		{
			mVelocity.y = MaxSpeed;
		}
		if (mVelocity.y <= -MaxSpeed)
		{
			mVelocity.y = -MaxSpeed;
		}
	}

	void Rigidbody::Friction_management()
	{	
		if (!(mVelocity == Vector2::Zero))	//마찰력조건(적용된 힘이 없고, 속도가 0이아님)					
		{			
			//속도에 반대방향으로 마찰력이 적용
			Vector2 friction = -mVelocity;						
			friction = friction.Normalize() * mFriction * mMass * static_cast<float>(Time::DeltaTime());			
			
			//마찰력으로 인한 속도 감소는 현재 속도보다 큰경우
			if (mVelocity.Length() < friction.Length())			
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}
	}

}