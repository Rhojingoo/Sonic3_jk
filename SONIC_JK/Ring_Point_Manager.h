#pragma once

#include "jk_Sonic.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Ring_Point_Manager : public Gameobject
	{
	public:
		Ring_Point_Manager(Gameobject* owner);
		~Ring_Point_Manager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		int GetRingPoint_UnitsDigit() { return UnitsDigit; }
		int GetRingPoint_TensDigit() { return TensDigit; }
		int GetRingPoint_HundredsDigit() { return HundredsDigit; }

	private:
		Gameobject* mOwner;
		Sonic* mSonic;
		Image* mImage;

		int Ring_point;
		int Ring_point_U;
		int Ring_point_T;
		int Ring_point_H;


		int UnitsDigit;
		int TensDigit;
		int HundredsDigit;

	};
}