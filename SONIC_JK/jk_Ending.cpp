#include "jk_Ending.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"

namespace jk
{
	Ending::Ending()
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
		BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		/*TransparentBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(0, 0, 0));*/

		Gameobject::Render(hdc);
	}


	void Ending::Release()
	{
		Gameobject::Release();
	}
}