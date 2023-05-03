#include "Ring_Point_Manager.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"


namespace jk
{
	Ring_Point_Manager::Ring_Point_Manager(Gameobject* owner)
		:mOwner(nullptr)
		, mSonic(nullptr)
		, mImage(nullptr)
		, Ring_point(0)
		, UnitsDigit(0)
		, TensDigit(0)
		, HundredsDigit(0)
		, Ring_point_U(0)
		, Ring_point_T(0)	
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
		Ring_point = mSonic->Get_Ring_Point();
		Ring_point_U = Ring_point;
		Ring_point_T = Ring_point;
		Ring_point_H = Ring_point;
		int a = 0;

		//1의자리
		if ((Ring_point_U >= 10) && (Ring_point_U < 20))
			Ring_point_U = Ring_point_U - 10;
		if ((Ring_point_U >= 20) && (Ring_point_U < 30))
			Ring_point_U = Ring_point_U - 20;
		if ((Ring_point_U >= 30) && (Ring_point_U < 40))
			Ring_point_U = Ring_point_U - 30;
		if ((Ring_point_U >= 40) && (Ring_point_U < 50))
			Ring_point_U = Ring_point_U - 40;
		if ((Ring_point_U >= 50) && (Ring_point_U < 60))
			Ring_point_U = Ring_point_U - 50;
		if ((Ring_point_U >= 60) && (Ring_point_U < 70))
			Ring_point_U = Ring_point_U - 60;
		if ((Ring_point_U >= 70) && (Ring_point_U < 80))
			Ring_point_U = Ring_point_U - 70;
		if ((Ring_point_U >= 80) && (Ring_point_U < 90))
			Ring_point_U = Ring_point_U - 80;
		if ((Ring_point_U >= 90) && (Ring_point_U < 100))
			Ring_point_U = Ring_point_U - 90;
	

		if (Ring_point_U == 0)
			UnitsDigit = 0;
		if(Ring_point_U ==1)
			UnitsDigit = 1;
		else if (Ring_point_U == 2)
			UnitsDigit = 2;
		else if (Ring_point_U == 3)
			UnitsDigit = 3;
		else if (Ring_point_U == 4)
			UnitsDigit = 4;
		else if (Ring_point_U == 5)
			UnitsDigit = 5;
		else if (Ring_point_U == 6)
			UnitsDigit = 6;
		else if (Ring_point_U == 7)
			UnitsDigit = 7;
		else if (Ring_point_U == 8)
			UnitsDigit = 8;
		else if (Ring_point_U == 9)
			UnitsDigit = 9;
		else if (Ring_point_U == 10)
			UnitsDigit = 0;				
		

		//10의자리
		if ((Ring_point_T >= 100) && (Ring_point_T < 200))
			Ring_point_T = Ring_point_T - 100;
		if ((Ring_point_T >= 200) && (Ring_point_T < 300))
			Ring_point_T = Ring_point_T - 200;
		if ((Ring_point_T >= 300) && (Ring_point_T < 400))
			Ring_point_T = Ring_point_T - 300;
		if ((Ring_point_T >= 400) && (Ring_point_T < 500))
			Ring_point_T = Ring_point_T - 400;
		if ((Ring_point_T >= 500) && (Ring_point_T < 600))
			Ring_point_T = Ring_point_T - 500;
		if ((Ring_point_T >= 600) && (Ring_point_T < 700))
			Ring_point_T = Ring_point_T - 600;
		if ((Ring_point_T >= 700) && (Ring_point_T < 800))
			Ring_point_T = Ring_point_T - 700;
		if ((Ring_point_T >= 800) && (Ring_point_T < 900))
			Ring_point_T = Ring_point_T - 800;
		if ((Ring_point_T >= 900) && (Ring_point_U < 1000))
			Ring_point_T = Ring_point_T - 900;


		if (Ring_point_T < 10)
			TensDigit = 0;
		if ((Ring_point_T >= 10)&& (Ring_point_T < 20))
			TensDigit = 1;
		else if ((Ring_point_T >= 20) && (Ring_point_T < 30))
			TensDigit = 2;
		else if ((Ring_point_T >= 30) && (Ring_point_T < 40))
			TensDigit = 3;
		else if ((Ring_point_T >= 40) && (Ring_point_T < 50))
			TensDigit = 4;
		else if ((Ring_point_T >= 50) && (Ring_point_T < 60))
			TensDigit = 5;
		else if ((Ring_point_T >= 60) && (Ring_point_T < 70))
			TensDigit = 6;
		else if ((Ring_point_T >= 70) && (Ring_point_T < 80))
			TensDigit = 7;
		else if ((Ring_point_T >= 80) && (Ring_point_T < 90))
			TensDigit = 8;
		else if ((Ring_point_T >= 90) && (Ring_point_T < 100))
			TensDigit = 9;
		else if (Ring_point_T >= 100)
			TensDigit = 0;				
		
		

		//100의자리		
		if (Ring_point < 100) 
			HundredsDigit = 0;
		if ((Ring_point >= 100) && (Ring_point < 200))
			HundredsDigit = 1;
		else if ((Ring_point >= 200) && (Ring_point < 300))
			HundredsDigit = 2;
		else if ((Ring_point >= 300) && (Ring_point < 400))
			HundredsDigit = 3;
		else if ((Ring_point >= 400) && (Ring_point < 500))
			HundredsDigit = 4;
		else if ((Ring_point >= 500) && (Ring_point < 600))
			HundredsDigit = 5;
		else if ((Ring_point >= 600) && (Ring_point < 700))
			HundredsDigit = 6;
		else if ((Ring_point >= 700) && (Ring_point < 800))
			HundredsDigit = 7;
		else if ((Ring_point >= 800) && (Ring_point < 900))
			HundredsDigit = 8;
		else if ((Ring_point >= 900) && (Ring_point < 1000))
			HundredsDigit = 9;
		else if (Ring_point >= 1000)
			HundredsDigit = 0;

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
