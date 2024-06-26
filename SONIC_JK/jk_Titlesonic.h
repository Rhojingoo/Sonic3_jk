#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Animator;
	class Titlesonic : public BackGround
	{
	public:
		Titlesonic();
		~Titlesonic();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		Animator* GetmAnimator() { return mAnimator; }

		void startscene();

	private:
		Image* mImage;
		Animator* mAnimator;
	};
}