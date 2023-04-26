#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Animator;
	class Boss_Arm : public Gameobject
	{
	public:
		enum class eBossState
		{
			Idle,
			Grap,
			//Hurt,
			Death
		};

		Boss_Arm(Gameobject* owner);
		~Boss_Arm();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_mDir(int dir) { mDir = dir; }
		void Set_Hurt(int hurt) { Damege_check= hurt; }
		int Get_grap() { return grap; }

	private:
		void Idle();
		void Grap();
		void Hurt();
		void Death();

	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Gameobject* mOwner;

		Vector2 pos;
		Vector2 Boss_pos;
		float mSpeed;
		int mDir;

		Sonic::eSonicState sonicState;
		eBossState mState;

		int moving_lotation;
		float time;
		int Boss_cross_change;
		int Damege_check;
		int grap;
	};
}