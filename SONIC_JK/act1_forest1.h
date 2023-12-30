#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class act1_forest1 : public BackGround
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
