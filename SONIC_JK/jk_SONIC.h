#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Tails;
	class Ground;
	class Rigidbody;
	class Animator;
	class Sonic : public Gameobject
	{
	public:
		enum class eSonicState
		{
			Idle,
			Attack,
			Hurt,
			Move,			
			Run,
			Dash,
			Brake,
			Push,
			Jump,
			Spring_Jump,
			Cylinder_move,
			Lookup,
			Sit,
			Spin,
			Twojump,
			Fire_Shield,			
			Electricity_Shield,
			Water_Shield,
			Jeep_line,

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

		Sonic();
		~Sonic();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSonicState Getsonicstate() {return mState;}
		int GetSonicDir() { return mDir; }
		int GetRingCheck() {return Ringcheck;}
		void SetCheckTargetGround(Ground* ground) { check = ground; }

	private:
		void idle();
		void attack();
		void hurt();
		void move() ;	
		void run() ;
		void dash();
		void brake();
		void push();
		void jump();
		void spring_jump();
		void cylinder_move();
		void lookup();
		void sit();
		void spin();
		void twojump();				
		void fire_Shield();
		void electricity_Shield();
		void water_Shield();
		void jeep_line();

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
		int mDir;		
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 SonicVelocity;
		Vector2 SonicBrake;
		eSonicState mState;
		class Image* mImage;
		class Image* mGroundImage;
		int circlecheck;
		Ground* check;
		int Circle_piece;
		int Ringcheck;
		int hurtcheck;
		Tails* Tails_call;
		Vector2 tails_call;

		int jeepline;
		int check_map;
	};

}
