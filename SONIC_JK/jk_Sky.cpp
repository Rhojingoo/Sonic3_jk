#include "jk_Sky.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Sky::Sky()
	{
	}
	Sky::~Sky()
	{
	}
	void Sky::Initialize()
	{
		mImage = Resources::Load<Image>(L"Sky", L"..\\Resources\\Sky.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 -1270) });
		//tr->SetPos(Vector2{ 11415 + 2790.0f * 3, 3096 + (940.0f * 3 + 120) });
		Gameobject::Initialize();
	}
	void Sky::Update()
	{
		Gameobject::Update();
	}
	void Sky::Render(HDC hdc)
	{
			
			Gameobject::Render(hdc);
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(pos);
			Vector2 mpos = Camera::CaluatePos(pos);
			int imageWidth = 15160; // 이미지의 가로 크기
			int screenWidth = 1200; // 화면의 가로 크기
			int moveSpeed = 15; // 화면의 이동 속도

			// 화면을 가로로 움직이기
			//mpos.x += moveSpeed; // 이동 속도만큼 x 축 위치를 증가시킴
			if (mpos.x >= imageWidth) // 화면의 끝에 도달하면
			{
				mpos.x = 0; // 다시 처음 위치로 돌아감
			}

			TransparentBlt(hdc, mpos.x / 3.f, mpos.y, 15160.0f, 1100.0f, mImage->GetHdc(), 0, 34, 15160.0f, 1100.0f, RGB(13, 72, 7));
		


		//Gameobject::Render(hdc);
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);
		//Vector2 mpos = Camera::CaluatePos(pos);
		//TransparentBlt(hdc, mpos.x / 3.f, mpos.y, 15160.0f, 1100.0f, mImage->GetHdc(), 0, 34, 15160.0f, 1100.0f, RGB(13, 72, 7));
	}
	void Sky::Release()
	{
		Gameobject::Release();
	}
}
