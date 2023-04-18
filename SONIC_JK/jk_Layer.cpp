#include "jk_Layer.h"

namespace jk
{
	Layer::Layer()
	{

	}
	
	Layer::~Layer()
	{
		for (Gameobject* gameObj : mGameobjects)
		{
			if (gameObj)
			{
				delete gameObj;
				gameObj = nullptr;
			}
		}
	}


	void Layer::Initialize()
	{
		for (Gameobject* gameObj : mGameobjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= Gameobject::eState::Active)
				continue;

			gameObj->Initialize();
		}
	}


	void Layer::Update()
	{
		for (Gameobject* gameObj : mGameobjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= Gameobject::eState::Active)
				continue;

			gameObj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (Gameobject* gameObj : mGameobjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState()
				!= Gameobject::eState::Active)
				continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Release()
	{	
		for (Gameobject* gameObj : mGameobjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
		}
	}

	void Layer::AddGameobject(Gameobject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameobjects.push_back(gameObj);
	}
}