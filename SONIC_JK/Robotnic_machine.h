#pragma once
#include "jk_Gameobject.h"
#include "Item.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Robotnic_machine : public Item
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
		eState mState;
		Image* mImage;
		Animator* mAnimator;

		float mSpeed;
		Vector2 pos;
	};
}