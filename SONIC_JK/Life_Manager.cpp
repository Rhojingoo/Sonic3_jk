#include "Life_Manager.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"


namespace jk
{
	Life_Manager::Life_Manager(Gameobject* owner)
		:mOwner(nullptr)
		, mSonic(nullptr)
		, mImage(nullptr)
		, Life_point(0)
		, Life_point_U(0)
		, Life_point_T(0)
		, UnitsDigit(0)
		, TensDigit(0)	
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
		Life_point = mSonic->Get_Life_Point();
		Life_point_U = Life_point;
		Life_point_T = Life_point;

		int a = 0;

		//1의자리
		if ((Life_point_U >= 10) && (Life_point_U < 20))
			Life_point_U = Life_point_U - 10;
		if ((Life_point_U >= 20) && (Life_point_U < 30))
			Life_point_U = Life_point_U - 20;
		if ((Life_point_U >= 30) && (Life_point_U < 40))
			Life_point_U = Life_point_U - 30;
		if ((Life_point_U >= 40) && (Life_point_U < 50))
			Life_point_U = Life_point_U - 40;
		if ((Life_point_U >= 50) && (Life_point_U < 60))
			Life_point_U = Life_point_U - 50;
		if ((Life_point_U >= 60) && (Life_point_U < 70))
			Life_point_U = Life_point_U - 60;
		if ((Life_point_U >= 70) && (Life_point_U < 80))
			Life_point_U = Life_point_U - 70;
		if ((Life_point_U >= 80) && (Life_point_U < 90))
			Life_point_U = Life_point_U - 80;
		if ((Life_point_U >= 90) && (Life_point_U < 100))
			Life_point_U = Life_point_U - 90;

		if (Life_point_U == 1)
			UnitsDigit = 1;
		else if (Life_point_U == 2)
			UnitsDigit = 2;
		else if (Life_point_U == 3)
			UnitsDigit = 3;
		else if (Life_point_U == 4)
			UnitsDigit = 4;
		else if (Life_point_U == 5)
			UnitsDigit = 5;
		else if (Life_point_U == 6)
			UnitsDigit = 6;
		else if (Life_point_U == 7)
			UnitsDigit = 7;
		else if (Life_point_U == 8)
			UnitsDigit = 8;
		else if (Life_point_U == 9)
			UnitsDigit = 9;
		else if (Life_point_U == 10)
			UnitsDigit = 0;


		//10의자리
		if ((Life_point_T >= 10) && (Life_point_T < 20))
			TensDigit = 1;
		else if ((Life_point_T >= 20) && (Life_point_T < 30))
			TensDigit = 2;
		else if ((Life_point_T >= 30) && (Life_point_T < 40))
			TensDigit = 3;
		else if ((Life_point_T >= 40) && (Life_point_T < 50))
			TensDigit = 4;
		else if ((Life_point_T >= 50) && (Life_point_T < 60))
			TensDigit = 5;
		else if ((Life_point_T >= 60) && (Life_point_T < 70))
			TensDigit = 6;
		else if ((Life_point_T >= 70) && (Life_point_T < 80))
			TensDigit = 7;
		else if ((Life_point_T >= 80) && (Life_point_T < 90))
			TensDigit = 8;
		else if ((Life_point_T >= 90) && (Life_point_T < 100))
			TensDigit = 9;
		else if (Life_point_T >= 100)
			TensDigit = 0;

		Gameobject::Update();

	}
	void Life_Manager::Render(HDC hdc)
	{
	}
	void Life_Manager::Release()
	{
	}
}