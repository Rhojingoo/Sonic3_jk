//#include "Rigdbody_R.h"
//#include "jk_Time.h"
//#include "jk_Gameobject.h"
//#include "jk_Transform.h"
//
//namespace jk
//{
//	Rigdbody_R::Rigdbody_R()
//		:Component(jk_ComponentType::Rigdbody_R)
//		, mMass(0.0f)
//		, mForce(Vector2::Zero)
//		, mAccelation(Vector2::Zero)
//		, mVelocity(Vector2::Zero)
//	{
//		mLimitedVelocity.x = 505.0f;
//		mLimitedVelocity.y = 1200.0f;
//		mbGround = false;
//		mGravity = Vector2(500.0f, 0.0f);
//		mFriction = 100.0f;
//	}
//	Rigdbody_R::~Rigdbody_R()
//	{
//	}
//	void Rigdbody_R::Initialize()
//	{
//	}
//	void Rigdbody_R::Update()
//	{
//
//		mAccelation = mForce / mMass;
//
//		if (mVelocity.y > -1200.f)
//		{ 
//			mVelocity += mAccelation * Time::DeltaTime();
//		}
//		else if (mVelocity.y <= -1200.f)
//		{
//			mVelocity.y = -1200.f;
//		}
//		if (mVelocity.y >= 1200.f)
//		{
//			mVelocity.y = 1200.f;
//		}
//
//
//		if (mbGround)
//		{
//			//�߷½� ���͸� ����1�� 
//			Vector2 gravity = mGravity;
//			gravity.Normalize();
//
//			//���鿡���� ����� ������� �̵� �� �Ʒ��� �̵�
//			float dot = math::Dot(mVelocity, gravity);
//			mVelocity -= gravity * dot;
//		}
//		else
//		{
//			mVelocity += mGravity * Time::DeltaTime();
//		}
//
//		//�߷°��ӵ� �ִ� �ӵ�����
//		Vector2 gravity = mGravity;
//		gravity.Normalize();
//		float dot = math::Dot(mVelocity, gravity);
//		gravity = gravity * dot;
//
//		Vector2 sideVelocity = mVelocity - gravity;
//		if (mLimitedVelocity.x < gravity.Length())
//		{
//			gravity.Normalize();
//			gravity *= mLimitedVelocity.x;
//			mVelocity.x = gravity.x;
//		}
//		if (mLimitedVelocity.y < sideVelocity.Length())
//		{
//			sideVelocity.Normalize();
//			sideVelocity *= mLimitedVelocity.y;
//		}
//
//		//����������(����� ���� ����, �ӵ��� 0�̾ƴ�)
//		if (!(mVelocity == Vector2::Zero))
//		{
//			//�ӵ��� �ݴ�������� �������� ����
//			Vector2 friction = -mVelocity;
//			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();
//
//			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū���
//			if (mVelocity.Length() < friction.Length())
//			{
//				mVelocity = Vector2::Zero;
//			}
//			else
//			{
//				mVelocity += friction;
//			}
//		}
//
//		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
//		Transform* tr = GetOwner()->GetComponent<Transform>();
//		Vector2 pos = tr->GetPos();
//		pos = pos + mVelocity * Time::DeltaTime();
//		tr->SetPos(pos);
//		mForce.Clear();
//
//
//	}
//	void Rigdbody_R::Render(HDC hdc)
//	{
//	}
//	void Rigdbody_R::Release()
//	{
//	}
//	void Rigdbody_R::AddForce(Vector2 force)
//	{
//		mForce += force;
//	}
//}