#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Animator;
	class Boss_trash : public Gameobject
	{
	public:
		Boss_trash(Gameobject* owner);
		~Boss_trash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
		Vector2 pos;
	};
}
