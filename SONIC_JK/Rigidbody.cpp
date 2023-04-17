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
		mGravity = Vector2(0.0f, 500.0f);
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
			//�߷½� ���͸� ����1�� 
			Vector2 gravity = mGravity;
			gravity.Normalize() ;

			//���鿡���� ����� ������� �̵� �� �Ʒ��� �̵�
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * static_cast<float>(Time::DeltaTime());
		}

		//�߷°��ӵ� �ִ� �ӵ�����
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

		//����������(����� ���� ����, �ӵ��� 0�̾ƴ�)
		if (!(mVelocity == Vector2::Zero))
		{
			//�ӵ��� �ݴ�������� �������� ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * static_cast<float>(Time::DeltaTime());

			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū���
			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}		
			else
			{
				mVelocity += friction;
			}
		}

		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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