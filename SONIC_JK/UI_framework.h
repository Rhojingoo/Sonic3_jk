#pragma once
#include "jk_Gameobject.h"


namespace jk
{
	class Image;
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
		float mTime2;
	};
}