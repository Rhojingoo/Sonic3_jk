#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class Act1_3_BG : public Gameobject
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