#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Animator;
	class Ending_boss : public Gameobject
	{
	public:


		Ending_boss(Gameobject* owner);
		~Ending_boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		
	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 pos;
		Gameobject* mOwner;
	};
}
