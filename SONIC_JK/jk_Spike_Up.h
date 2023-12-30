#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Animator;
	class Spike_Up : public BackGround
	{
	public:

		Spike_Up();
		~Spike_Up();

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