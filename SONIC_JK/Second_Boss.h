#pragma once
#include "jk_Boss.h"

namespace jk
{
	class Sound;
	class Image;
	class Boss_Run;
	class Rigidbody;
	class Animator;
	class Second_Boss : public Boss
	{
	public:
		enum class eBossState
		{
			R_up,
			R_down,
			L_up,
			L_down,
			Attack_L,
			Attack_R,	
			Death
		};

		Second_Boss();
		~Second_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void Create_RunBoss();

		int Get_last_BOSS() {return mBoomb_point	;}
		void Set_last_BOSS(int check) { mBoomb_point = check; }

	

	private:
		void R_up();
		void R_down();
		void L_down();
		void L_up();
		void death();

		void Hurt();
		void L_Attack();
		void R_Attack();


	private:
		Sound* mBoss_Hit;
		Sound* mBoss_Bomb;
		Sound* mBoss_Start;
		Sound* mAct6_music;

	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Boss_Run* mBoss_Run;
		
	private:
		Vector2 mCenterpos;
		Vector2 mPos;
		float mSpeed;
		float Up_Down;
		int mDir;
		Sonic::eSonicState sonicState;
		eBossState mState;

	private:
		float mTime;
		float mTime2;
		int mBoss_change_point;
		int mDamege_check;
		int mBoomb_point;	
	};
}
