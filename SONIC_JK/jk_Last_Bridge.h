#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Rigidbody;
	class Animator;
	class Last_Bridge : public BackGround
	{
	public:
		enum class eState
		{	
			Idle,
			Death,
		};

		Last_Bridge();
		~Last_Bridge();

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
	};
}