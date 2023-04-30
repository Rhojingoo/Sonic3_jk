#pragma once

#include "jk_Sonic.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Life_Manager : public Gameobject
	{
	public:
		Life_Manager(Gameobject* owner);
		~Life_Manager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		int GetSonicLife_UnitsDigit() { return UnitsDigit; }
		int GetSonicLife_TensDigit() { return TensDigit; }
		

	private:
		Gameobject* mOwner;
		Sonic* mSonic;
		Image* mImage;

		int Life_point;
		int Life_point_U;
		int Life_point_T;

		int UnitsDigit;
		int TensDigit;


	};
}