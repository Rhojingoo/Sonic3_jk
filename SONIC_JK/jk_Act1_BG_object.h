#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Act1_BG_object : public BackGround
	{
	public:
		Act1_BG_object();
		~Act1_BG_object();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
	};
}
