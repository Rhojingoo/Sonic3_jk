#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class act6_sky1 : public BackGround
	{
	public:
		act6_sky1();
		~act6_sky1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
	};
}