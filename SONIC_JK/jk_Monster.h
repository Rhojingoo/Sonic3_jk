#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Sonic.h"
#include "jk_Time.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class Monster : public Gameobject
	{
	public:
		enum class eMonsterState
		{		
			Move,	
			Run,
			Turn,
			Deth,
			Release_animal,
		};


		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }
		void SetCenterpos(Vector2 pos) {mCenterpos = pos;}

		Vector2 Getmonster() {return mCurpos; }
		void release_animal();

	private:	
		void move();
		void run();
		void turn();
		void deth();

	private:	
		Gameobject* mOwner;
		Rigidbody* mRigidbody;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Ground* check;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		eMonsterState mState;	
		Sonic::eSonicState sonicState;		
	};
}
