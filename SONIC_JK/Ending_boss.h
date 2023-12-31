#pragma once
#include "jk_Effect.h"

namespace jk
{
	class Ending_boss : public Effect
	{
	public:


		Ending_boss(Gameobject* owner);
		~Ending_boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		
	private:
		class Image* mImage;
		class Animator* mAnimator;
		Vector2 mPos;
		Gameobject* mOwner;
	};
}
