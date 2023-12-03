#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class UI_framework : public Gameobject
	{
	public:
		UI_framework();
		~UI_framework();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;		
		float mTime;
		float time;
	};
}