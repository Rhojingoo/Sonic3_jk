#pragma once
#include "jk_Gameobject.h"
#include "jk_Tails.h"
#include "jk_Image.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class tail_jump : public Gameobject
	{
	public:

		tail_jump(Gameobject* owner, int dir, int falling);
		~tail_jump();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
		Vector2 mTails;
		Gameobject* mOwner;
		int mDir;	
		int mFalling;
	};

}
