#pragma once
#include "jk_Boss.h"

namespace jk
{
	class Sound;
	class Image;
	class Rigidbody;
	class Animator;
	class Third_Boss : public Boss
	{
	public:
		enum class eBossState
		{
			Start,
			Left_Cross,
			Right_Cross,
			Left,
			Right,
			Grap_R,
			Grap_L,
			Death,
			Ending
		};

		Third_Boss();
		~Third_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;	

		int Get_mDir() { return mDir; }
		int Get_Hurt() { return mHurt_check; }
		void Set_Grap(int grap) { mGrap_pattern = grap; }

		int GetEnding_point() { return mEnding_point; }
		void SetEnding_point(int end) { mEnding_point = end; }


	private:
		void start();
		void L_cross();
		void R_cross();
		void left();
		void right();
		void grap_R();
		void grap_L();
		void Hurt();
		void death();
		void ending();

	
	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Sound* mBoss_Hit;
		Sound* mBoss_Bomb;

	private:	
		Vector2 mPos;
		float mSpeed;
		float mTime;
		int mDir;


		Sonic::eSonicState mSonicState;
		eBossState mState;


	private:
		int mBoss_cross_change;
		int mDamege_check;
		int mBoomb_point;
		int mGrap_pattern;
		int mHurt_check;
		int mEnding_point;

	};
}
