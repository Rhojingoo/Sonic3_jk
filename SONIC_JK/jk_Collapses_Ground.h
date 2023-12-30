#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Sound;
	class Image;
	class Rigidbody;
	class Animator;
	class Collapses_Ground : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Collapses_Ground();
		~Collapses_Ground();

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
		Sound* mCrash;
		eState mState;
		Image* mImage;
		Animator* mAnimator;

	private:
		float mTime;
		int Check_Ground;
	};
}