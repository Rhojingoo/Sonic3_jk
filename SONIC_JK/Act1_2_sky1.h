#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Act1_2_sky1 : public BackGround
	{
	public:
		Act1_2_sky1();
		~Act1_2_sky1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
