#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class Cylinder : public BackGround
	{
	public:
		enum class eState
		{
			Idle,		
			Death,
		};

		Cylinder();
		~Cylinder();

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
		Image* mImage;
		Animator* mAnimator;
		eState mState;
		Rigidbody* mRigidbody;
	};

}
