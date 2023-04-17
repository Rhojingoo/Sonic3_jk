#include "jk_Act1skyBG.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk 
{
	Act1skyBG::Act1skyBG()
	{
	}

	Act1skyBG::~Act1skyBG()
	{
	}

	void Act1skyBG::Initialize()
	{
		mImage = Resources::Load<Image>(L"forest", L"..\\Resources\\forest.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 + 300) });
		//tr->SetPos(Vector2{ 11415 + 2790.0f * 3, 3096 + (940.0f * 3 + 120) });
		Gameobject::Initialize();
	}

	void Act1skyBG::Update()
	{
		Gameobject::Update();
	}

	void Act1skyBG::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		tr->SetPos(pos);	
		//Vector2 imagepos = Vector2 (11515, 1026);
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x /3.f,  mpos.y, 11515, 1026, mImage->GetHdc(), 33,15 , 11515, 1026, RGB(13, 72, 7));

	
	}

	void Act1skyBG::Release()
	{
		Gameobject::Release();
	}

}