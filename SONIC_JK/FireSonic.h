#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Image;
	class Animator;
	class FireSonic : public Gameobject
	{
	public:
		enum class State
		{
			Idle,
			Fire_Attack,
		};

		FireSonic(Gameobject* owner);
		~FireSonic();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void idle();
		void fire_attack();
		void fire_effect();


	private:
		Gameobject* mOwner;
		Sonic* mSonic;
		Animator* mAnimator;
		State mState;
		Vector2 mSonic_Pos;
		int mDir;
		int mEffect_check;

	};

}
