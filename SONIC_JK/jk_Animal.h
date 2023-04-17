#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"


namespace jk
{
	class Animal : public Gameobject
	{
	public:
		Animal(Gameobject* owner);
		~Animal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		Vector2 Sonic;
		Gameobject* mOwner;
	};
}
