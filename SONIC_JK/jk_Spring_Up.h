#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Spring_Up : public Gameobject
	{
	public:
		enum class eState
		{
			Up,
			Down,
		};

		Spring_Up();
		~Spring_Up();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		void up();
		void down();


	private:
		Gameobject* mOwner;
		eState mState;
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
		Vector2 pos;
		float fDist;
		Vector2 mSonic;

		Sonic::eSonicState sonicState;
		int sonicpattern;

	};

}