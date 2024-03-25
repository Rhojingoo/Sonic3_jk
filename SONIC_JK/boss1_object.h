#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Rigidbody;
	class Image;
	class Sound;
	class Pixel_Ground;
	class boss1_body;
	class Animator;
	class boss1_object : public BackGround
	{
	public:
		enum class eBossState
		{
			Idle,
			Up,
			Down,
		};

		boss1_object(Gameobject* onwer);
		~boss1_object();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_Deathpoint(int point) { mDeath_point = point; }
		void SetGroundImage(Image* image) { mGroundImage = image; }
		int Get_Deathpoint() { return mDeath_point; }

	private:
		void idle();
		void up();
		void down();
		void attack_up();
		void attack_down();

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;
		Sound* mBullet1;

	private:
		class First_Boss* mBoss;
		class act6_bullet1* mBullet;
		eBossState mState;
		Vector2 mPos;
		int mDir;
		float mTime;
		int mAttack_check;
		int mAttack_lotation;
		int mDeath_point;
		int mBullet_check;
	};
}
