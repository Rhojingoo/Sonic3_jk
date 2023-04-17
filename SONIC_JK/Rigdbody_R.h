#pragma once
#include "jk_Component.h"

namespace jk
{
	class Rigdbody_R : public Component
	{
	public:
		Rigdbody_R();
		~Rigdbody_R();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		Vector2 Velocity() { return mVelocity; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		bool GetGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetFiction(float PlayerFriction) { mFriction = PlayerFriction; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;

		/*	float mStaticFriction;
			float mKineticFriction;
			float mCoefficientFriction;
			float mNormalForce;*/
	};
}

