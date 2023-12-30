#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Animator;
	class Blending : public Gameobject
	{
	public:
		Blending();
		~Blending();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;	

	private:
		class Image* mImage;
		float mCcheckTime;
	};
}