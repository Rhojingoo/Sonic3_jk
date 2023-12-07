#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class TitleSN : public BackGround
	{

	public:
		enum class eState
		{
			Idle,
			Move,
		};

		TitleSN();
		~TitleSN();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void move();


	private:
		int mDir;
		Image* mImage;
		eState mState;
		Animator* mAnimator;
		Gameobject* mOwner;
		bool bTurn;
		float time;
		int turnindex;

	};
}
