#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Elec_effect : public Gameobject
	{
	public:

		Elec_effect(Gameobject* owner);
		~Elec_effect();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
		Vector2 mSonic;
		Gameobject* mOwner;
		int mDir;
		int tailcheck;


	};

}