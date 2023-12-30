#include "jk_Ending.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Image.h"

namespace jk
{
	Ending::Ending()
		:mImage(nullptr)
	{
	}


	Ending::~Ending()
	{
	}


	void Ending::Initialize()
	{
		mImage = Resources::Load<Image>(L"Ending_BG", L"..\\Resources\\END_BG.bmp");
		Gameobject::Initialize();
	}


	void Ending::Update()
	{
		Gameobject::Update();
	}


	void Ending::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		BitBlt(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);

		Gameobject::Render(hdc);
	}

	void Ending::Release()
	{
		Gameobject::Release();
	}
}