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
			int imageWidth = 15160; // �̹����� ���� ũ��
			int screenWidth = 1200; // ȭ���� ���� ũ��
			int moveSpeed = 15; // ȭ���� �̵� �ӵ�

			// ȭ���� ���η� �����̱�
			//mpos.x += moveSpeed; // �̵� �ӵ���ŭ x �� ��ġ�� ������Ŵ
			if (mpos.x >= imageWidth) // ȭ���� ���� �����ϸ�
			{
				mpos.x = 0; // �ٽ� ó�� ��ġ�� ���ư�
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
