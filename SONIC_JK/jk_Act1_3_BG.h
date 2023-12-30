#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Act1_3_BG : public BackGround
	{
	public:
		Act1_3_BG();
		~Act1_3_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}