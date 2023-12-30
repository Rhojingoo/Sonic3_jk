#pragma once
#include "Life_Manager.h"
#include "jk_Gameobject.h"


namespace jk
{
	class Image;
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
		Life_Manager* mUnits;
		Image* mImage;
		int mUnitsDigit;
	};
}