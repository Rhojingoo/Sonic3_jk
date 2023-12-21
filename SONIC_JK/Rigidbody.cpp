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

	void Rigidbody::Speed_Manegement()
	{
		mAccelation = mForce / mMass;
		
		if (mVelocity.x < 1200.f)
		{
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
		}
		else if (mVelocity.x >= 1200.f)
		{
			mVelocity += mAccelation * static_cast<float>(Time::DeltaTime());
			mVelocity.x = 1200.f;
		}
		if (mVelocity.x <= -1200.f)
		{
			mVelocity.x = -1200.f;
		}
	}

	void Rigidbody::Gravity_management()
	{
		if (mbGround)
		{			
			Vector2 gravity = mGravity;						//�߷½� ���͸� ����1�� 
			gravity.Normalize();			
			float dot = math::Dot(mVelocity, gravity);		//���鿡���� �Ʒ��� �̵�
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * static_cast<float>(Time::DeltaTime());
		}


		//�߷°��ӵ� �ӵ�����1
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
		
		//�߷°��ӵ� �ִ� �ӵ�����2
		//Vector2 gravity = mGravity;							
		//gravity.Normalize();
		//float dot = math::Dot(mVelocity, gravity);
		//gravity = gravity * dot;
		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitedVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.x;
		//}
	}

	void Rigidbody::Friction_management()
	{	
		if (!(mVelocity == Vector2::Zero))						//����������(����� ���� ����, �ӵ��� 0�̾ƴ�)
		{			
			Vector2 friction = -mVelocity;						//�ӵ��� �ݴ�������� �������� ����
			friction = friction.Normalize() * mFriction * mMass * static_cast<float>(Time::DeltaTime());			
			if (mVelocity.Length() < friction.Length())			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū���
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