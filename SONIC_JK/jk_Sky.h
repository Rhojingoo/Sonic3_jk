#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Sky : public BackGround
	{
	public:
		Sky();
		~Sky();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
