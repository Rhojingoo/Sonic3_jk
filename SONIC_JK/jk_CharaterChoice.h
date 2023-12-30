#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Animator;
	class CharaterChoice : public BackGround
	{
	public:
		CharaterChoice();
		~CharaterChoice();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		class Image* mImage;
	};
}