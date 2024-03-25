#pragma once
#include "jk_Boss.h"
#include "jk_SONIC.h"

namespace jk
{
	class Sound;
	class Image;
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

		int Boss_Death() { return mDeath_check; }


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
		Vector2 mPos;
		float mMonspeed;
		float mMonmaxdistance;
		float fDist;
		float mTime;
		int mDir;

	private:
		eBossState mState;
		Gameobject* mOwner;
		Sonic::eSonicState sonicState;

	private:
		class Boss_Run* boss_run;
		class BaseBullet* _Down_bullet[2] = {};
		class Bullet_Act1_R_Side* _R_side_bullet[2] = {};
		class Bullet_Act1_R_DIA* _R_dia_bullet[2] = {};
		class Bullet_Act1_L_Side* _L_side_bullet[2] = {};
		class Bullet_Act1_L_DIA* _L_dia_bullet[2] = {};

	private:
		int mStarscene;
		int mAttack_motion;
		int mDir_change;
		int mAttack_check;
		int mHurt_state;
		int mDamege_check;
		int mDeath_check;
	};
}

