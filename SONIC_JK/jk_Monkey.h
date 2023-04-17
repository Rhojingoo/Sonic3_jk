#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Ground;
	class Animator;
	class Monkey : public Gameobject
	{
	public:
		enum class eMonkey
		{
			L_Move_UP,
			L_Move_DOWN,
			R_Move_UP,
			R_Move_DOWN,
			L_Throw,
			R_Throw,	
			Turn,
			Deth,		
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
		void SetCheckTargetGround(Ground* ground) { check = ground; }
		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }

		Vector2 Getmonster() { return mCurpos; }


	private:
		void Lmove_up();
		void Lmove_down();
		void Rmove_up();
		void Rmove_down();
		void Lthrows();
		void Rthrows();
		void turn();
		void deth();

		void throw_CompleteEvent();
		void release_animal();

	private:
		Gameobject* mOwner;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Ground* check;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		eMonkey mState;
		Vector2 pos;
		float fDist;
		Vector2 mSonic;

		Sonic::eSonicState sonicState;
		int sonicpattern;
	};
}