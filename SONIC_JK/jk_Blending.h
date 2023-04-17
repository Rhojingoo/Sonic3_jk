#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

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
		Image* mImage;
		float mTime;
		float checktime;
	};
}