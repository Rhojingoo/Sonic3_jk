#pragma once
#include "jk_Gameobject.h"


namespace jk
{
	class Sonic;
	class Pixel_Ground;
	class Rigidbody;
	class Image;
	class Animator;
	class Tails : public Gameobject
	{
	public:
		enum class eTailsState
		{
			Idle,
			Move,
			Run,
			Dash,
			Brake,
			Jump,
			Movejump,
			Spring_Jump,
			Jumpfalling,
			Hurt,
			Lookup,
			Sit,
			Spin,
			Twojump,
			Shield,
			Fly,
			Fly_Ready,
			Fly_Pursue,
			Fly_Waiting,

			EMDING,
			End,


		};

		Tails(Gameobject* owner);
		~Tails();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eTailsState GetTails_state() { return mState; }
		int GetTailsDir() { return mDir; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }
		void Set_Pursue_boss(int pursue) { mPursue_boss = pursue; }

		void Set_Fly(int fly) { mFly_check = fly; }
		int Get_Fly() { return mFly_check; }
		void Set_Ending(int final) { mEnd = final; }


	private:
		void idle();
		void move();	
		void run();
		void dash();
		void brake();
		void jump();
		void movejump();
		void jumpfalling();
		void spring_jump();
		void hurt();
		void lookup();
		void sit();
		void spin();
		void twojump();
		void shield();
		void fly();
		void fly_Ready();
		void fly_pursue();
		void fly_waiting();
		void ending();
		void endgame();


	private:		
		Gameobject* mOwner;
		Sonic* mSonic;
		Pixel_Ground* mPixel_Ground;
		eTailsState mState;
		Animator* mAnimator;	
		Rigidbody* mRigidbody;
		Vector2 mSonic_Velocity;		
		Vector2 mTailsVelocity;
		Vector2 mFalling_Check_pos;
		

	private:
		int mDir;
		int mFalling;
		int mFly_check;
		int mPursue_boss;
		int mHurtcheck;
		int mEnd;
	};

}
