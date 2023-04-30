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
	{
		mLimitedVelocity.x = 505.0f;
		mLimitedVelocity.y = 505.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 700.0f);
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
		mAccelation = mForce / mMass;

		if (mVelocity.x < 1200.f)
		{
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
		}
		else if(mVelocity.x>=1200.f)
		{			
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
			mVelocity.x = 1200.f;
		}
		if (mVelocity.x <= -1200.f)
		{
			mVelocity.x = -1200.f;
		}

		if (mVelocity.y < 1200.f)
		{
			//mVelocity += mAccelation * Time::DeltaTime();
		}
		else if (mVelocity.y >= 1200.f)
		{
			mVelocity.y = 1200.f;
		}
		if (mVelocity.y <= -1200.f)
		{
			mVelocity.y = -1200.f;
		}


		if (mbGround)
		{
			//중력시 벡터를 단위1로 
			Vector2 gravity = mGravity;
			gravity.Normalize() ;

			//경사면에서의 적용시 진행방향 이동 및 아래로 이동
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * static_cast<float>(Time::DeltaTime());
		}

		//중력가속도 최대 속도제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		/*if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
			mVelocity.y = gravity.y;
		}*/
		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		//마찰력조건(적용된 힘이 없고, 속도가 0이아님)
		if (!(mVelocity == Vector2::Zero))
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
}