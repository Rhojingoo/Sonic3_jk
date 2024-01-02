#include "jk_Snake.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Snake_Head.h"
#include "jk_Snake_First_Body.h"
#include "jk_Snake_Second_Body.h"
#include "jk_Snake_Third_Body.h"
#include "jk_Snake_Last_Body.h"
#include "jk_Snake_Tail.h"
#include "jk_Animal.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"

namespace jk
{
	bool Snake::mLifeCheck = true;

	Snake::Snake(Vector2 _Pos)
		: mScene(nullptr)
		, mDeath(nullptr)
		, mAnimator(nullptr)
		, mPos(_Pos)
		, mObdel(false)
	{
	}
	Snake::Snake(Snake* abc)
		: mScene(nullptr)
		, mDeath(nullptr)
		, mAnimator(nullptr)
		, mPos(Vector2(0.f,0.f))
		, mObdel(false)
	{
	}
	Snake::Snake()
	{
	}
	Snake::~Snake()
	{
	}
	void Snake::Initialize()
	{

		mLifeCheck = true;
		mScene = SceneManager::GetActiveScene();

		mSnake[0] = new Snake_Head();
		mSnake[0]->SetName(L"Snake_head");
		mScene->AddGameobeject(mSnake[0], jk_LayerType::Monster);
		mSnake[0]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[0]->Initialize();		

		mSnake[1] = new Snake_First_Body(dynamic_cast<Snake_Head*>(mSnake[0]));
		mSnake[1]->SetName(L"Snake_Body");	
		mScene->AddGameobeject(mSnake[1], jk_LayerType::Monster);
		mSnake[1]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[1]->Initialize();

		mSnake[2] = new Snake_Second_Body(dynamic_cast<Snake_Head*>(mSnake[0]));
		mSnake[2]->SetName(L"Snake_Body2");
		mScene->AddGameobeject(mSnake[2], jk_LayerType::Monster);
		mSnake[2]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[2]->Initialize();

	/*	mSnake[3] = new Snake_Third_Body(dynamic_cast<Snake_Second_Body*>(mSnake[2]));
		mSnake[3]->SetName(L"Snake_Body3");
		mScene->AddGameobeject(mSnake[3], jk_LayerType::Monster);
		mSnake[3]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[3]->Initialize();



		mSnake[4] = new Snake_Last_Body(dynamic_cast<Snake_Third_Body*>(mSnake[3]));
		mSnake[4]->SetName(L"Snake_Body4");
		mScene->AddGameobeject(mSnake[4], jk_LayerType::Monster);
		mSnake[4]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[4]->Initialize();


		mSnake[5] = new Snake_Tail(dynamic_cast<Snake_Last_Body*>(mSnake[4]));
		mSnake[5]->SetName(L"Snake_Body4");
		mScene->AddGameobeject(mSnake[5], jk_LayerType::Monster);
		mSnake[5]->GetComponent<Transform>()->SetPos(Vector2{ mPos.x, mPos.y });
		mSnake[5]->Initialize();*/

		Gameobject::Initialize();

	}
	void Snake::Update()
	{
		if (mLifeCheck == false)
		{
			if (mObdel == false)
			{
				object::Destory(mSnake[0]);
				object::Destory(mSnake[1]);
				object::Destory(mSnake[2]);
				//object::Destory(mSnake[3]);
				//object::Destory(mSnake[4]);
				//object::Destory(mSnake[5]);

				mObdel = true;
			}
		}
		Gameobject::Update();
	}
	void Snake::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
		
	
	void Snake::Release()
	{
		Gameobject::Release();
	}
	void Snake::OnCollisionEnter(Collider* other)
	{
	}
	void Snake::OnCollisionStay(Collider* other)
	{
	}
	void Snake::OnCollisionExit(Collider* other)
	{
	}

	double Snake::TimeSinceStart()
	{
		LARGE_INTEGER frequency;
		LARGE_INTEGER counter;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&counter);
		return static_cast<double>(counter.QuadPart) / static_cast<double>(frequency.QuadPart);
	}
}
