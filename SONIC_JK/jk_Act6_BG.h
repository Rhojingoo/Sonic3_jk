#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class jk_Act6_BG : public BackGround
	{
	public:
		jk_Act6_BG();
		~jk_Act6_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
			

	private:
		Image* mImage;
	};
}