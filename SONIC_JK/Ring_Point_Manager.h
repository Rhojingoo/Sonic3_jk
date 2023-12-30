#pragma once
#include "jk_Sonic.h"
#include "jk_Gameobject.h"


namespace jk
{
	class Image;
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

		int GetRingPoint_UnitsDigit() { return mUnitsDigit; }
		int GetRingPoint_TensDigit() { return mTensDigit; }
		int GetRingPoint_HundredsDigit() { return mHundredsDigit; }

	private:
		Gameobject* mOwner;
		Sonic* mSonic;
		Image* mImage;

		int mRing_point;
		int mRing_point_U;
		int mRing_point_T;
		int mRing_point_H;


		int mUnitsDigit;
		int mTensDigit;
		int mHundredsDigit;

	};
}