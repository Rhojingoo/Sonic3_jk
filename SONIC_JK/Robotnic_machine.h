#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Robotnic_machine : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Death,
		};

		Robotnic_machine();
		~Robotnic_machine();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		void idle();
		void move();
		void death();


	private:
		Gameobject* mOwner;
		eState mState;
		Image* mImage;
		float mSpeed;


		Animator* mAnimator;
		Vector2 pos;
		Vector2 mSonic;
	};
}