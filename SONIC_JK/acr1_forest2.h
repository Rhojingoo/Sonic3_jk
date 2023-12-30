#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class acr1_forest2 : public BackGround
	{
	public:
		acr1_forest2();
		~acr1_forest2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}