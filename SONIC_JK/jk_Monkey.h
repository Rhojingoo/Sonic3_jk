#pragma once
#include "jk_Monster.h"
#include "jk_SONIC.h"
#include "jk_Tails.h"

namespace jk
{
	class Monkey : public Monster
	{
	public:
		enum class eMonkey
		{
			L_Move_UP,
			L_Move_DOWN,
			L_Throw,
			R_Throw,	
			Turn,
			Death,		
		};

		Monkey(Gameobject* owner);
		~Monkey();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }
		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }

		Vector2 Getmonster_pos() { return mPos; }

	private:
		void Lmove_up();
		void Lmove_down();
		void Lthrows();
		void Rthrows();
		void turn();
		void death();

		void throw_CompleteEvent();
		void release_animal();


	private:
		Gameobject* mOwner;
		class Pixel_Ground* mPixel_Ground;
		class Sound* mDeath;
		class Image* mImage;
		class Image* mImage1;
		class Image* mGroundImage;
		class Animator* mAnimator;	
		Transform* mTr;
		class Monkey_Bullet* mBullet;
		Transform* mBullet_tr;
		class Rigidbody* mBullet_rb;

		eMonkey mState;
		Vector2 mCenterpos;	
		Vector2 mPos;
		float mMonspeed;
		float mMonmaxdistance;
		float fDist;
		int mDir;
		int mDeath_point;
		int mAnimal_point;

		Vector2 mSonic_Pos;
		int mSonicPattern;
		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;


	};
}