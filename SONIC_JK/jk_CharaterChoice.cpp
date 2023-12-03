#include "jk_CharaterChoice.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Resources.h"

namespace jk
{
	CharaterChoice::CharaterChoice()
		:mImage(nullptr)
	{
	}

	CharaterChoice::~CharaterChoice()
	{
	}

	void CharaterChoice::Initialize()
	{
		mImage = Resources::Load<Image>(L"Choicing_BG", L"..\\Resources\\Ch_BG.bmp");
		Gameobject::Initialize();
	}

	void CharaterChoice::Update()
	{
		Gameobject::Update();
	}

	void CharaterChoice::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), 24, 216, 319, 223, RGB(1, 1, 1));		
	}

	void CharaterChoice::Release()
	{
		Gameobject::Release();
	}
}

