#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	class Pixel_Ground;
	class Animator;
	class Boss_appear : public Boss
	{
	public:	

		Boss_appear(Gameobject* owner);
		~Boss_appear();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;



	private:
		Image* mImage;
		Animator* mAnimator;

		float mMonspeed;
		Vector2 pos;
		Gameobject* mOwner;
	};
}