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

namespace jk
{
	bool Snake::LifeCheck = true;

	Snake::Snake(Vector2 _Pos)
		: mScene(nullptr)
		, Death(nullptr)
		, mAnimator(nullptr)
		, pos(_Pos)
		, sonicState()
		, tailsState()	
		, Obdel(false)
	{

	}
	Snake::Snake(Snake* abc)
		: mScene(nullptr)
		, Death(nullptr)
		, mAnimator(nullptr)
		, pos(Vector2(0.f,0.f))
		, sonicState()
		, tailsState()
		, Obdel(false)
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

		LifeCheck = true;
		mScene = SceneManager::GetActiveScene();

		snake[0] = new Snake_Head();
		snake[0]->SetName(L"Snake_head");
		mScene->AddGameobeject(snake[0], jk_LayerType::Monster);
		snake[0]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[0]->Initialize();		

		snake[1] = new Snake_First_Body(dynamic_cast<Snake_Head*>(snake[0]));
		snake[1]->SetName(L"Snake_Body");	
		mScene->AddGameobeject(snake[1], jk_LayerType::Monster);
		snake[1]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[1]->Initialize();

		snake[2] = new Snake_Second_Body(dynamic_cast<Snake_First_Body*>(snake[1]));
		snake[2]->SetName(L"Snake_Body2");
		mScene->AddGameobeject(snake[2], jk_LayerType::Monster);
		snake[2]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[2]->Initialize();

		snake[3] = new Snake_Third_Body(dynamic_cast<Snake_Second_Body*>(snake[2]));
		snake[3]->SetName(L"Snake_Body3");
		mScene->AddGameobeject(snake[3], jk_LayerType::Monster);
		snake[3]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[3]->Initialize();



		snake[4] = new Snake_Last_Body(dynamic_cast<Snake_Third_Body*>(snake[3]));
		snake[4]->SetName(L"Snake_Body4");
		mScene->AddGameobeject(snake[4], jk_LayerType::Monster);
		snake[4]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[4]->Initialize();



		snake[5] = new Snake_Tail(dynamic_cast<Snake_Last_Body*>(snake[4]));
		snake[5]->SetName(L"Snake_Body4");
		mScene->AddGameobeject(snake[5], jk_LayerType::Monster);
		snake[5]->GetComponent<Transform>()->SetPos(Vector2{ pos.x, pos.y });
		snake[5]->Initialize();

		Gameobject::Initialize();

	}
	void Snake::Update()
	{
		if (LifeCheck == false)
		{
			if (Obdel == false)
			{
				object::Destory(snake[0]);
				object::Destory(snake[1]);
				object::Destory(snake[2]);
				object::Destory(snake[3]);
				object::Destory(snake[4]);
				object::Destory(snake[5]);

				Obdel = true;
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
