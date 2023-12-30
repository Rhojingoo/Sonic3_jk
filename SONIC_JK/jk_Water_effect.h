#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Animator;
	class Water_effect : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Water_effect();
		~Water_effect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void idle();
		void death();
		void water_splashes();

	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;
	};
}