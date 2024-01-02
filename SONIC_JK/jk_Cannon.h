#pragma once
#include "jk_Monster.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"

namespace jk
{
	class Sonic;
	class Tails;
	class Cannon : public Monster
	{
	public:
		enum class eCannon
		{
			Idle,
			Right,
			Left,			
			Death
		};

		Cannon(Gameobject* owner);
		~Cannon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }


		Vector2 Getmonster() { return mPos; }
		int GetDir() {	return mDir	;}


	private:
		
		void idle();
		void right();
		void left();
		void death();

		void throw_CompleteEvent();
		void release_animal();
		void Ground_check();

	private:
		Gameobject* mOwner;
		class Sound* mDeath_Sound;
		class Image* mImage;
		class Image * mImage1;
		class Image* mGroundImage;
		class Image* mGroundImage2;
		class Image* bullet_groundImage;
		class Animator* mAnimator;
		class Pixel_Ground* mPixel_Ground;
		class Rigidbody* mRigidbody;

		class Cannon_Bullet* mBullet;
		class Rigidbody* mBullet_rg;
		Transform* mBullet_tr;

	private:
		eCannon mState;
		Vector2 mPos;
		int mDir;
		int mCheck_Map;
		bool mDeath;

		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;
	}; 
}