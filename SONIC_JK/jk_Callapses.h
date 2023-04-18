#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Callapses : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Callapses();
		~Callapses();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void death();


	private:
		Gameobject* mOwner;
		eState mState;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Rigidbody* mRigidbody;	
		Animator* mAnimator;
		Vector2 pos;



	};

}