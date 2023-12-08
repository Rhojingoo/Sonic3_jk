#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"


#include "jk_BaseBullet.h"
#include "Bullet_Act1_R_Side.h"
#include "Bullet_Act1_R_DIA.h"
#include "Bullet_Act1_L_Side.h"
#include "Bullet_Act1_L_DIA.h"


namespace jk
{
	class Boss_Run;
	class Rigidbody;
	class Animator;
	class Act1_Boss : public Boss
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


		Act1_Boss(Gameobject* owner);
		~Act1_Boss();

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
		Sound* Boss_Hit;
		Sound* Boss_Bomb;
		Sound* Boss_Start;
		Sound* Act2_music;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 mCenterpos;

	private:
		Vector2 pos;
		float mMonspeed;
		float mMonmaxdistance;
		float fDist;
		float time;
		int mDir;

	private:
		Boss_Run* boss_run;
		eBossState mState;
		Gameobject* mOwner;
		Sonic::eSonicState sonicState;

	private:
		BaseBullet*				_Down_bullet[2]		= {};
		Bullet_Act1_R_Side*		_R_side_bullet[2]	= {};
		Bullet_Act1_R_DIA*		_R_dia_bullet[2]	= {};
		Bullet_Act1_L_Side*		_L_side_bullet[2]	= {};
		Bullet_Act1_L_DIA*		_L_dia_bullet[2]	= {};

	private:
		int starscene;
		int attack_motion;
		int Dir_change;
		int attack_check;
		int hurt_state;
		int Damege_sheck;
		int Death_check;
	};
}

