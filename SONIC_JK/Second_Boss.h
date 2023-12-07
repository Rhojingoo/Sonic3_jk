#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"



namespace jk
{
	class Third_Boss;
	class Boss_Arm;
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

		int Get_last_BOSS() {return Boomb_point	;}
		void Set_last_BOSS(int check) { Boomb_point = check; }

	

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
		Sound* Boss_Hit;
		Sound* Boss_Bomb;
		Sound* Boss_Start;
		Sound* Act6_music;

	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Boss_Run* boss_run2;
		
	private:
		Vector2 mCenterpos;
		Vector2 pos;
		float mSpeed;
		float Up_Down;
		int mDir;
		Sonic::eSonicState sonicState;
		eBossState mState;

	private:
		float time;
		float secondtime;
		int Boss_change_point;
		int Damege_check;
		int Boomb_point;	
	};
}
