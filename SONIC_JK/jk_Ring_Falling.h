#pragma once
#include "jk_Gameobject.h"
#include "Item.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	class Rigidbody;
	class Animator;
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
		void SetGroundImage(Image* image) { mGroundImage = image; }


	private:
		void idle();
		void eat();
		void death();

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Gameobject* mOwner;
		eState Ring_State;


	private:
		float timer; 
		float bounceForce;
		int check_ground;

	};
}
