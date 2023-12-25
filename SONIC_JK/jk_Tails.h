#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class Pixel_Ground;
	class Rigidbody;
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
		void SetCheckTargetGround(Pixel_Ground* ground) { check = ground; }
		void Set_Pursue_boss(int pursue) { pursue_boss = pursue; }

		void Set_Fly(int fly) { fly_check = fly; }
		int Get_Fly() { return fly_check; }
		void Set_Ending(int final) { end = final; }


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
		Pixel_Ground* check;
		eTailsState mState;
		Animator* mAnimator;	
		Rigidbody* mRigidbody;
		Vector2 sonicV;		
		Vector2 TailsVelocity;
		Vector2 fallingcheck;
		

	private:
		int mDir;
		int falling;
		int circlecheck;
		int Circle_piece;		
		int fly_check;
		int pursue_boss;
		int hurtcheck;
		int end;
	};

}
