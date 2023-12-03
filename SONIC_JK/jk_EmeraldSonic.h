#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class EmeraldSonic : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Jump,		
		};

		EmeraldSonic();
		~EmeraldSonic();


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
		void jump();


	private:		
		eState mState;
		Animator* mAnimator;
	};
}
