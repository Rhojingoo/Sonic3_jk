#pragma once
#include "jk_Component.h"

namespace jk 
{
	class Rigidbody : public Component
	{
		public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void SetForce(Vector2 force) { mForce = force; }
		void AddForce(Vector2 force);

		void SetGravity(Vector2	gravity) { mGravity = gravity; }
		Vector2 Getgravity() { return mGravity; }

		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 Velocity() { return mVelocity; }		
		
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() {return mbGround;}
	
		void SetFiction(float PlayerFriction) { mFriction = PlayerFriction; }
		void Speed_Manegement();
		void Gravity_management();
		void Friction_management();

		private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;
		float MaxSpeed;
	};
}

