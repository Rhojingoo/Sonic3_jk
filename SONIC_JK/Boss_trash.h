#pragma once
#include "jk_Effect.h"



namespace jk
{
	class Boss_trash : public Effect
	{
	public:
		Boss_trash(Gameobject* owner);
		~Boss_trash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
		Vector2 mPos;
	};
}
