#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Ending : public BackGround
	{
	public:
		Ending();
		~Ending();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
