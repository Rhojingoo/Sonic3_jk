#include "Ring_Point_Manager.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"
#include "jk_Image.h"


namespace jk
{
	Ring_Point_Manager::Ring_Point_Manager(Gameobject* owner)
		:mOwner(nullptr)
		, mSonic(nullptr)
		, mImage(nullptr)
		, mRing_point(0)
		, mUnitsDigit(0)
		, mTensDigit(0)
		, mHundredsDigit(0)
		, mRing_point_U(0)
		, mRing_point_T(0)	
		, mRing_point_H(0)
	{
		mOwner = owner;
		mSonic = dynamic_cast<Sonic*>(owner);
	}
	Ring_Point_Manager::~Ring_Point_Manager()
	{

	}
	void Ring_Point_Manager::Initialize()
	{
		
		Gameobject::Initialize();
	}
	void Ring_Point_Manager::Update()
	{
		mRing_point = mSonic->Get_Ring_Point();
		mRing_point_U = mRing_point;
		mRing_point_T = mRing_point;
		mRing_point_H = mRing_point;
		int a = 0;

		//1의자리
		if ((mRing_point_U >= 10) && (mRing_point_U < 20))
			mRing_point_U = mRing_point_U - 10;
		if ((mRing_point_U >= 20) && (mRing_point_U < 30))
			mRing_point_U = mRing_point_U - 20;
		if ((mRing_point_U >= 30) && (mRing_point_U < 40))
			mRing_point_U = mRing_point_U - 30;
		if ((mRing_point_U >= 40) && (mRing_point_U < 50))
			mRing_point_U = mRing_point_U - 40;
		if ((mRing_point_U >= 50) && (mRing_point_U < 60))
			mRing_point_U = mRing_point_U - 50;
		if ((mRing_point_U >= 60) && (mRing_point_U < 70))
			mRing_point_U = mRing_point_U - 60;
		if ((mRing_point_U >= 70) && (mRing_point_U < 80))
			mRing_point_U = mRing_point_U - 70;
		if ((mRing_point_U >= 80) && (mRing_point_U < 90))
			mRing_point_U = mRing_point_U - 80;
		if ((mRing_point_U >= 90) && (mRing_point_U < 100))
			mRing_point_U = mRing_point_U - 90;
	

		if (mRing_point_U == 0)
			mUnitsDigit = 0;
		if(mRing_point_U ==1)
			mUnitsDigit = 1;
		else if (mRing_point_U == 2)
			mUnitsDigit = 2;
		else if (mRing_point_U == 3)
			mUnitsDigit = 3;
		else if (mRing_point_U == 4)
			mUnitsDigit = 4;
		else if (mRing_point_U == 5)
			mUnitsDigit = 5;
		else if (mRing_point_U == 6)
			mUnitsDigit = 6;
		else if (mRing_point_U == 7)
			mUnitsDigit = 7;
		else if (mRing_point_U == 8)
			mUnitsDigit = 8;
		else if (mRing_point_U == 9)
			mUnitsDigit = 9;
		else if (mRing_point_U == 10)
			mUnitsDigit = 0;				
		

		//10의자리
		if ((mRing_point_T >= 100) && (mRing_point_T < 200))
			mRing_point_T = mRing_point_T - 100;
		if ((mRing_point_T >= 200) && (mRing_point_T < 300))
			mRing_point_T = mRing_point_T - 200;
		if ((mRing_point_T >= 300) && (mRing_point_T < 400))
			mRing_point_T = mRing_point_T - 300;
		if ((mRing_point_T >= 400) && (mRing_point_T < 500))
			mRing_point_T = mRing_point_T - 400;
		if ((mRing_point_T >= 500) && (mRing_point_T < 600))
			mRing_point_T = mRing_point_T - 500;
		if ((mRing_point_T >= 600) && (mRing_point_T < 700))
			mRing_point_T = mRing_point_T - 600;
		if ((mRing_point_T >= 700) && (mRing_point_T < 800))
			mRing_point_T = mRing_point_T - 700;
		if ((mRing_point_T >= 800) && (mRing_point_T < 900))
			mRing_point_T = mRing_point_T - 800;
		if ((mRing_point_T >= 900) && (mRing_point_U < 1000))
			mRing_point_T = mRing_point_T - 900;


		if (mRing_point_T < 10)
			mTensDigit = 0;
		if ((mRing_point_T >= 10)&& (mRing_point_T < 20))
			mTensDigit = 1;
		else if ((mRing_point_T >= 20) && (mRing_point_T < 30))
			mTensDigit = 2;
		else if ((mRing_point_T >= 30) && (mRing_point_T < 40))
			mTensDigit = 3;
		else if ((mRing_point_T >= 40) && (mRing_point_T < 50))
			mTensDigit = 4;
		else if ((mRing_point_T >= 50) && (mRing_point_T < 60))
			mTensDigit = 5;
		else if ((mRing_point_T >= 60) && (mRing_point_T < 70))
			mTensDigit = 6;
		else if ((mRing_point_T >= 70) && (mRing_point_T < 80))
			mTensDigit = 7;
		else if ((mRing_point_T >= 80) && (mRing_point_T < 90))
			mTensDigit = 8;
		else if ((mRing_point_T >= 90) && (mRing_point_T < 100))
			mTensDigit = 9;
		else if (mRing_point_T >= 100)
			mTensDigit = 0;				
		
		

		//100의자리		
		if (mRing_point < 100) 
			mHundredsDigit = 0;
		if ((mRing_point >= 100) && (mRing_point < 200))
			mHundredsDigit = 1;
		else if ((mRing_point >= 200) && (mRing_point < 300))
			mHundredsDigit = 2;
		else if ((mRing_point >= 300) && (mRing_point < 400))
			mHundredsDigit = 3;
		else if ((mRing_point >= 400) && (mRing_point < 500))
			mHundredsDigit = 4;
		else if ((mRing_point >= 500) && (mRing_point < 600))
			mHundredsDigit = 5;
		else if ((mRing_point >= 600) && (mRing_point < 700))
			mHundredsDigit = 6;
		else if ((mRing_point >= 700) && (mRing_point < 800))
			mHundredsDigit = 7;
		else if ((mRing_point >= 800) && (mRing_point < 900))
			mHundredsDigit = 8;
		else if ((mRing_point >= 900) && (mRing_point < 1000))
			mHundredsDigit = 9;
		else if (mRing_point >= 1000)
			mHundredsDigit = 0;

		Gameobject::Update();
	}

	void Ring_Point_Manager::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Ring_Point_Manager::Release()
	{
		Gameobject::Release();
	}
}
