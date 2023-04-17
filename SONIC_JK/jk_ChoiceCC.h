#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class ChoiceCC : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
		};

		ChoiceCC();
		~ChoiceCC();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void move();




	private:
		int mDir;
		Image* mImage1;
		Image* mImage2;
		Image* mImage3;
		eState mState;
		Animator* mAnimator;
		Gameobject* mOwner;
		bool bTurn;
		float time;
		int turnindex;
	};

}
