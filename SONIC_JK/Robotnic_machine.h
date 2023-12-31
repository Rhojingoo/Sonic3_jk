#pragma once
#include "Item.h"

namespace jk
{
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
		class Image* mImage;
		class Animator* mAnimator;
		float mSpeed;
		Vector2 mPos;
	};
}