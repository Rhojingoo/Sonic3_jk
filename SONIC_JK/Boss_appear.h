#pragma once
#include "jk_Boss.h"

namespace jk
{
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
		class Image* mImage;
		class Animator* mAnimator;

		float mMonspeed;
		Vector2 mPos;
		Gameobject* mOwner;
	};
}