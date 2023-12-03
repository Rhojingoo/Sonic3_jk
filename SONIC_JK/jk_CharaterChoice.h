#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"


namespace jk
{
	class Animator;
	class CharaterChoice : public Gameobject
	{
	public:
		CharaterChoice();
		~CharaterChoice();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;	
	};
}