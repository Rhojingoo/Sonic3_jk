#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class StageSave : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
		};

		StageSave();
		~StageSave();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCheckTargetGround(Ground* ground) { check = ground; }


	private:
		void idle();
		void move();

	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;
		int mDir;
		Ground* check;
		Rigidbody* mRigidbody;

	};

}
