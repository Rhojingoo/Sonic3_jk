#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Sonic;
	class Elec_effect;
	class Rigidbody;
	class Image;
	class Animator;
	class Electsonic : public Gameobject
	{
	public:
		enum class State
		{
			Idle,
			Elect_Effect,
		};

		Electsonic(Gameobject* owner);
		~Electsonic();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void idle();
		void elect_effect();
		void effect();


	private:
		Animator* mAnimator;
		Gameobject* mOwner;
		Vector2 mSonic_pos;
		State mState;
		Sonic* mSonic;
		Elec_effect* mElect1;
		Elec_effect* mElect2;
		int mEffect_check;
		int mEffect_call;
		float mTime;
	};
}
