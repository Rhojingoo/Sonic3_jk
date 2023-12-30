#pragma once

#include "jk_Gameobject.h"

namespace jk
{
	class Sonic;
	class Image;
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

		int GetSonicLife_UnitsDigit() { return mUnitsDigit; }
		int GetSonicLife_TensDigit() { return mTensDigit; }
		

	private:
		Gameobject* mOwner;
		Sonic* mSonic;
		Image* mImage;

		int mLife_point;
		int mLife_point_U;
		int mLife_point_T;

		int mUnitsDigit;
		int mTensDigit;
	};
}