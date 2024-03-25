#pragma once
#include "jk_Boss.h"
#include "jk_SONIC.h"

namespace jk
{
	class Image;
	class Sound;
	class boss1_object;
	class Rigidbody;
	class Animator;
	class First_Boss : public Boss
	{
	public:
		enum class eBossState
		{
			Idle,
			Move,
			Hurt,
			Death,
			Attack_Up,
			Attack_Down,
		};

		First_Boss();
		~First_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int Get_BossDeath() { return  mDeath_point; }
		void Set__BossDeath(int point) { mDeath_point = point; }

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixelGround = ground; }


	private:
		void idle();
		void move();
		void hurt();
		void death();
		void attack_up();
		void attack_down();

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;

	private:
		Sound* mBoss_Hit;
		Sound* mBoss_Bomb;
		Sound* mBoss_Start;
		Sound* mAct6_music;

	private:
		eBossState mState;
		Sonic::eSonicState sonicState;
		boss1_object* mBoss_Object;
		Pixel_Ground* mPixelGround;

	private:
		Vector2 mPos;
		float mTime;
		int mDeath_point;
		int mDamege_check;
		int mCheck_Map;
	};
}
