#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Animator;
	class StageSave : public BackGround
	{
	public:
		StageSave();
		~StageSave();

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
