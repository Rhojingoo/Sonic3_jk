#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
	class Animator;
	class Sky : public Gameobject
	{
	public:
		Sky();
		~Sky();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Animator* mAnimator;
	};

}