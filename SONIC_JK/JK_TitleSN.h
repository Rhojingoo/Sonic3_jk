#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Animator;
	class TitleSN : public BackGround
	{
	public:
		TitleSN();
		~TitleSN();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		int mDir;
		Image* mImage;
		eState mState;
		Animator* mAnimator;
		Gameobject* mOwner;
		bool mTurn;
		float mTime;
		int mTurn_Index;

	};
}
