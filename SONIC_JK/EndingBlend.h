#pragma once
#include "jk_Gameobject.h"


namespace jk
{
	class Animator;
	class EndingBlend : public Gameobject
	{
	public:
		EndingBlend();
		~EndingBlend();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		float mCheckTime;
	};
}