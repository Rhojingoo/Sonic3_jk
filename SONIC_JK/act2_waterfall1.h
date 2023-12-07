#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class act2_waterfall1 : public BackGround
	{
	public:
		act2_waterfall1();
		~act2_waterfall1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		
	private:
		Image* mImage;
		Animator* mAnimator;
	};
}