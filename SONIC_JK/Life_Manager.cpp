#include "Life_Manager.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	Life_Manager::Life_Manager(Gameobject* owner)
		:mOwner(nullptr)
		, mSonic(nullptr)
		, mImage(nullptr)
		, mLife_point(0)
		, mLife_point_U(0)
		, mLife_point_T(0)
		, mUnitsDigit(0)
		, mTensDigit(0)	
	{
		mOwner = owner;
		mSonic = dynamic_cast<Sonic*>(owner);
	}
	Life_Manager::~Life_Manager()
	{
	}
	void Life_Manager::Initialize()
	{
		Gameobject::Initialize();
	}
	void Life_Manager::Update()
	{
		mLife_point = mSonic->Get_Life_Point();
		mLife_point_U = mLife_point;
		mLife_point_T = mLife_point;

		int a = 0;

		//1의자리
		if ((mLife_point_U >= 10) && (mLife_point_U < 20))
			mLife_point_U = mLife_point_U - 10;
		if ((mLife_point_U >= 20) && (mLife_point_U < 30))
			mLife_point_U = mLife_point_U - 20;
		if ((mLife_point_U >= 30) && (mLife_point_U < 40))
			mLife_point_U = mLife_point_U - 30;
		if ((mLife_point_U >= 40) && (mLife_point_U < 50))
			mLife_point_U = mLife_point_U - 40;
		if ((mLife_point_U >= 50) && (mLife_point_U < 60))
			mLife_point_U = mLife_point_U - 50;
		if ((mLife_point_U >= 60) && (mLife_point_U < 70))
			mLife_point_U = mLife_point_U - 60;
		if ((mLife_point_U >= 70) && (mLife_point_U < 80))
			mLife_point_U = mLife_point_U - 70;
		if ((mLife_point_U >= 80) && (mLife_point_U < 90))
			mLife_point_U = mLife_point_U - 80;
		if ((mLife_point_U >= 90) && (mLife_point_U < 100))
			mLife_point_U = mLife_point_U - 90;


		if (mLife_point_U == 0)
			mUnitsDigit = 0;
		if (mLife_point_U == 1)
			mUnitsDigit = 1;
		else if (mLife_point_U == 2)
			mUnitsDigit = 2;
		else if (mLife_point_U == 3)
			mUnitsDigit = 3;
		else if (mLife_point_U == 4)
			mUnitsDigit = 4;
		else if (mLife_point_U == 5)
			mUnitsDigit = 5;
		else if (mLife_point_U == 6)
			mUnitsDigit = 6;
		else if (mLife_point_U == 7)
			mUnitsDigit = 7;
		else if (mLife_point_U == 8)
			mUnitsDigit = 8;
		else if (mLife_point_U == 9)
			mUnitsDigit = 9;
		else if (mLife_point_U == 10)
			mUnitsDigit = 0;


		//10의자리
		if (mLife_point_T < 10) 
			mTensDigit = 0;
		if ((mLife_point_T >= 10) && (mLife_point_T < 20))
			mTensDigit = 1;
		else if ((mLife_point_T >= 20) && (mLife_point_T < 30))
			mTensDigit = 2;
		else if ((mLife_point_T >= 30) && (mLife_point_T < 40))
			mTensDigit = 3;
		else if ((mLife_point_T >= 40) && (mLife_point_T < 50))
			mTensDigit = 4;
		else if ((mLife_point_T >= 50) && (mLife_point_T < 60))
			mTensDigit = 5;
		else if ((mLife_point_T >= 60) && (mLife_point_T < 70))
			mTensDigit = 6;
		else if ((mLife_point_T >= 70) && (mLife_point_T < 80))
			mTensDigit = 7;
		else if ((mLife_point_T >= 80) && (mLife_point_T < 90))
			mTensDigit = 8;
		else if ((mLife_point_T >= 90) && (mLife_point_T < 100))
			mTensDigit = 9;
		else if (mLife_point_T >= 100)
			mTensDigit = 0;

		Gameobject::Update();

	}
	void Life_Manager::Render(HDC hdc)
	{
	}
	void Life_Manager::Release()
	{
	}
}