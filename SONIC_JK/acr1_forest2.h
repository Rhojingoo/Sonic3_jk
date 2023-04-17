#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class acr1_forest2 : public Gameobject
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