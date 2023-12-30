#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Act1skyBG : public BackGround
	{
	public:
		Act1skyBG();
		~Act1skyBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
