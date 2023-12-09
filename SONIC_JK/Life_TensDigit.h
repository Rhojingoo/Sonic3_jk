#pragma once
#include "Life_Manager.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Life_TensDigit : public Gameobject
	{
	public:
		Life_TensDigit(Gameobject* owner);
		~Life_TensDigit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		Life_Manager* Units;
		Image* mImage;
		int TensDigit;
	};
}