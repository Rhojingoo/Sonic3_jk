#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Act1_2_sky5 : public Gameobject
	{
	public:
		Act1_2_sky5();
		~Act1_2_sky5();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};

}