#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class act1_forest1 : public Gameobject
	{
	public:
		act1_forest1();
		~act1_forest1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
