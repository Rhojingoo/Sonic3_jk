#pragma once
#include "jk_Gameobject.h"


namespace jk
{
	class WaterSonic;
	class FireSonic;
	class Electsonic;
	class Tails;
	class Pixel_Ground;
	class Rigidbody;
	class Image;
	class Sound;
	class Animator;
	class Sonic : public Gameobject
	{
	public:
		enum class eSonicState
		{
			Idle,
			Move,
			Run,
			Jump,
			Sit,
			Spin,
			Dash,
			Brake,
			Circle,
			Lookup,
			Push,
			Attack,
			HitWaiting,
			Hurt,
			Spring_Jump,
			Cylinder_move,
			Twojump,
			Jeep_line,
			Tails_Hanging,	
			Fire_Shield,
			Electricity_Shield,
			Water_Shield,
			Death,
			GameOver,
			EMDING,
			End,
		};

		enum class eCircle
		{
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
			End,
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
		int GetRingCheck() {return mRingcheck;}
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }
		
		
		int Elect_Shield() { return mElect_effect; }
		int Water_Shield() { return mWater_bounce; }
		int Fire_Shield() { return mFire_effect; }
		void Fire_Shield_End(int check) { mFire_effect = check; }
	
		void Set_Fly(int fly) { mFly_check = fly; }
		void Set_Ending(int final) { mEnd = final; }

		int Get_Ring_Point() { return mRingcheck; }
		int Get_Life_Point() { return mLife; }

	private:
		void idle();
		void attack();
		void hitwaiting();
		void hurt();
		void move() ;	
		void run() ;
		void circle();
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
		void tails_hanging();
		void death();
		void gameover();		
		void ending();
		void endgame();

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
		
		void ring_drop_Small();
		void ring_drop_Midium();
		void ring_drop_Large();


	private:
		Sound* mEnding_song;
		Sound* mSonic_Jump;
		Sound* mRing_Have;
		Sound* mRing_Lose;
		Sound* mBrake;
		Sound* mSpin;
		Sound* mLast_Boss_f;
		Sound* mSpike_mc;

	private:
		Animator* mAnimator;
		Image* mImage;
		Image* mGroundImage;
		Rigidbody* mRigidbody;
		Pixel_Ground* mPixel_Ground;

	private:
		Vector2 mSonicVelocity;
		Vector2 mSonicBrake;
		Electsonic* mElect;
		FireSonic* mFire;
		WaterSonic* mWater;
		int mWater_bounce;
		int mFire_effect;
		int mElect_effect;
		
	private:
		eSonicState mState;
		eCircle mCircle_state;
		Tails* mTails_call;
		Vector2 mTails_call_Pos;
		int mDir;		
		int mCheck_map;
		int mCirclecheck;
		int mCircle_piece;
		int mRingcheck;
		int mHurtcheck;
		int mJeepline;
		int mFly_check;
		int mLife;
		int mEnd;
		float mAngle;
		float mTime;	
		bool mLoopenter;
	};
}
