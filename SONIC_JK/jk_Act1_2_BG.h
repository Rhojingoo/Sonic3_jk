#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Act1_2_BG : public BackGround
	{
	public:
		Act1_2_BG();
		~Act1_2_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};

}