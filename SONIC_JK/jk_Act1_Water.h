#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Animator;
	class Act1_Water : public BackGround
	{
	public:
		Act1_Water();
		~Act1_Water();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Water_Splashes(float a, float b);

	private:
		Image* mImage;
		float mCcheckTime;
	};
}