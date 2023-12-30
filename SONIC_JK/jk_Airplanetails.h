#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Animator;
	class Airplanetails : public BackGround

	{
	public:
		Airplanetails();
		~Airplanetails();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		Animator* GetmAnimator() { return mAnimator; }

	private:
		Image* mImage;
		Animator* mAnimator;

	private:
		Vector2 mCenterpos;
		int mDir;
		float mSpeed;
		float mMaxdistance;
	};
}