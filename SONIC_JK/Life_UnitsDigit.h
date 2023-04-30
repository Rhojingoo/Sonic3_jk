#pragma once
#include "Life_Manager.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Life_UnitsDigit : public Gameobject
	{
	public:
		Life_UnitsDigit(Gameobject* owner);
		~Life_UnitsDigit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		Life_Manager* Units;
		Image* mImage;

		float UnitsDigit;
	};
}