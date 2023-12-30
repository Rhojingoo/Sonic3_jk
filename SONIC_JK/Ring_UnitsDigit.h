#pragma once
#include "Ring_Point_Manager.h"
#include "jk_Gameobject.h"


namespace jk
{
	class Image;
	class Animator;
	class Ring_UnitsDigit : public Gameobject
	{
	public:
		Ring_UnitsDigit(Gameobject* owner);
		~Ring_UnitsDigit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		Ring_Point_Manager* Units;
		Image* mImage;

		int mUnitsDigit;
	};
}