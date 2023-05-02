#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"
#include "jk_Time.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class Cannon : public Gameobject
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
		void SetCheckTargetGround(Ground* ground) { check = ground; }


		Vector2 Getmonster() { return mCurpos; }
		int GetDir() {	return mDir	;}


	private:
		
		void idle();
		void right();
		void left();
		void death();

		void throw_CompleteEvent();
		void release_animal();

	private:
		Gameobject* mOwner;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Image* mGroundImage2;
		Animator* mAnimator;
		Ground* check;
		Rigidbody* mRigidbody;

	private:
		Vector2 mCurpos;	
		int mDir;
		eCannon mState;
		Vector2 pos;
		float fDist;
		Vector2 mSonic;
		int sonicpattern;
		int check_map;

	private:
		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;

	};
}