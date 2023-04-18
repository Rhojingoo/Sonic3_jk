#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class Rock_Pice : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Up,
			Down,
		};

		Rock_Pice();
		~Rock_Pice();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }

	private:
		void idle();
		void up();
		void down();


	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Gameobject* mOwner;
		eState Rock_State;
		Ground* check;
		int mDir;
		int Itemcheck;
		Rigidbody* mRigidbody;
	};

}