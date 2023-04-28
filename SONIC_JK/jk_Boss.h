#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Boss_Run;
	class Rigidbody;
	class Animator;
	class Boss : public Gameobject
	{
	public:
		enum class eBossState
		{
			Idle,
			Move,
			Right,
			Left,
			Up,
			Down,


			Side_Dianogol,
			Dianogol_Down,
			Down_Dianogol,
			Dianogol_Side,
			Side_Down,

		
			Attack_Side_Waiting,		
			Attack_Dianogol_Waiting,		
			Attack_Down_Waiting,

			Death,
			Death_throw
		};


		Boss(Gameobject* owner);
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int Boss_Death() { return Death_check; }


	private:

		void idle();
		void move();
		void right();
		void left();
		void up();
		void down();


		void side_down();
		void side_dianogol();
		void dianogol_side();
		void dianogol_down();
		void down_dianogol();		

		void attack_side();
		void attack_side_waiting();

		void attack_dianogol();
		void attack_dianogol_waition();

		void attack_down();
		void attack_down_waition();



		void hurt_down();
		void hurt_side();
		void hurt_dianogol();

		void death();
		void death_throw();

	private:
		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		Vector2 pos;
		Boss_Run* boss_run;


		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		float fDist;
		eBossState mState;
		Gameobject* mOwner;

		float time;
		Sonic::eSonicState sonicState;
		int starscene;
		int attack_motion;
		int Dir_change;
		int attack_check;

		int hurt_state;
		int Damege_sheck;
		int Death_check;


	};
}
