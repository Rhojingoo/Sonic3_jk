#pragma once
#include "jk_Monster.h"
#include "jk_SONIC.h"
#include "jk_Tails.h"


namespace jk
{
	class Rino : public Monster
	{
	public:
		enum class eRinoState
		{		
			Move,	
			Run,
			Turn,
			Death,
			Release_animal,
		};
				Rino();
		~Rino();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }
		void SetCenterpos(Vector2 pos) {mCenterpos = pos;}

		Vector2 Getmonster_pos() {return mCurpos; }
		void release_animal();
		void GroundCheck();

	private:	
		void move();
		void run();
		void turn();
		void death();

	private:	
		class Sound* mDeath;
		class Pixel_Ground* mPixel_Ground;
		class Rigidbody* mRigidbody;
		class Animator* mAnimator;
		class Image* mImage;
		class Image* mImage1;
		class Image* mGroundImage;
		class Image* mGroundImage2;
		
	private:
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		int mDeath_Point;
		int mCheck_Map;

	private:
		eRinoState mState;	
		Sonic::eSonicState sonicState;		
		Tails::eTailsState tailsState;
	};
}
