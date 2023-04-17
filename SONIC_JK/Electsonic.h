#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Electsonic : public Gameobject
	{
	public:

		Electsonic(Gameobject* owner);
		~Electsonic();


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
