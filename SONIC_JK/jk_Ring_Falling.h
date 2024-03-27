#pragma once
#include "Item.h"

namespace jk
{
	class Ring_Falling : public Item
	{
	public:
		enum class eState
		{
			Idle,
			Eat,
			Death,
		};

		Ring_Falling(Gameobject* owner);
		~Ring_Falling();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void CreateBlending();
		void SetGroundImage(class Image* image) { mGroundImage = image; }


	private:
		void idle();
		void eat();
		void death();

	private:
		class Image* mImage;
		class Image* mGroundImage;
		class Animator* mAnimator;
		class Rigidbody* mRigidbody;
		Gameobject* mOwner;
		eState Ring_State;


	private:
		float mTime; 
		float mBounceForce;
		int mCheck_Ground;
	};
}
