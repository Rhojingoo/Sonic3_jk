#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Minigame : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Turn,
		};

		Minigame();
		~Minigame();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void move();
		void turn();



	private:	
		Image* mImage;
		Animator* mAnimator;
		eState mState;
		int mDir;
		int turnindex;
	};

}
