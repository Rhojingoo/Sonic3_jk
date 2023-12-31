#pragma once
#include "jk_Monster.h"

namespace jk
{
	class Animal : public Monster
	{
	public:
		Animal(Gameobject* owner);
		~Animal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
	};
}
