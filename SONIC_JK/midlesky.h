#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class midlesky : public BackGround
	{
	public:
		midlesky();
		~midlesky();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};

}
