#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Sound;
	class Image;
	class Rigidbody;
	class Animator;
	class Collapses_GR_left : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Collapses_GR_left();
		~Collapses_GR_left();

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
		int mCheck_Ground;
	};
}