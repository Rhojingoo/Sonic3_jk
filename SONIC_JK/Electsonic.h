#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	class Elec_effect;
	class Rigidbody;
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
		Vector2 mSonic;
		Gameobject* mOwner;
		int mDir;
		int tailcheck;
		State mState;
		Elec_effect* elect1;
		Elec_effect* elect2;


		Sonic* sonic;
		int effect_check;
		int effect_call;
		float time;

	};

}
