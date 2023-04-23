#pragma once
#include "jk_Gameobject.h"
#include "jk_tails_tail.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class Ground;
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
			Jumpfalling,
			Lookup,
			Sit,
			Spin,
			Twojump,
			Shield,
			Fly,		


			Circle_Rturn_R,
			Circle_Rturn_1,
			Circle_Rturn_2,
			Circle_Rturn_3,
			Circle_Rturn_4,
			Circle_Rturn_5,
			Circle_Rturn_6,
			Circle_Rturn_7,

			Circle_Lturn_1,
			Circle_Lturn_2,
			Circle_Lturn_3,
			Circle_Lturn_4,
			Circle_Lturn_5,
			Circle_Lturn_6,
			Circle_Lturn_7,
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
		int GetTailsDir() { return TailsmDir; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }

	private:
		void idle();
		void move();	
		void run();
		void dash();
		void brake();
		void jump();
		void movejump();
		void jumpfalling();
		void lookup();
		void sit();
		void spin();
		void twojump();
		void shield();
		void fly();
	

		void circle_Rturn_1();
		void circle_Rturn_2();
		void circle_Rturn_3();
		void circle_Rturn_4();
		void circle_Rturn_5();
		void circle_Rturn_6();
		void circle_Rturn_7();


		void circle_Lturn_1();
		void circle_Lturn_2();
		void circle_Lturn_3();
		void circle_Lturn_4();
		void circle_Lturn_5();
		void circle_Lturn_6();
		void circle_Lturn_7();



	private:		
		int TailsmDir;
		eTailsState mState;
		Animator* mAnimator;	
		Vector2 sonicV;		
		Gameobject* mOwner;
		Vector2 TailsVelocity;
		Vector2 SonicBrake;
		Vector2 fallingcheck;
		Sonic* mSonic;
		

	private:
		Rigidbody* mRigidbody;
		int falling;
		int circlecheck;
		Ground* check;
		int Circle_piece;		
		int fly_check;
	};

}
