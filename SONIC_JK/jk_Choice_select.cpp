#include "jk_Choice_select.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"


namespace jk
{
	Choice_select::Choice_select()
		:Select_state(1)
		, Box_space(0)
	{
	}
	Choice_select::~Choice_select()
	{
	}
	void Choice_select::Initialize()
	{
		Transform* tr1 = GetComponent<Transform>();
		mImage = Resources::Load<Image>(L"CC_BG1", L"..\\Resources\\Ch_BG1.bmp");
	 	mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Red_box", mImage, Vector2(526, 499), Vector2(78, 170), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"Red_box", true);
		tr1->SetPos(Vector2{ 335.f,210.f });


		Gameobject::Initialize();
	}
	void Choice_select::Update()
	{
		Transform* tr1 = GetComponent<Transform>();
		Vector2 pos1 = tr1->GetPos();

			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				if (Select_state == 1)
				{
					pos1.x = pos1.x+ 410;
					Select_state = -1;
				}
			}	
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				if (Select_state == -1)
				{
					pos1.x = pos1.x - 410;
					Select_state = 1;
				}
			}
			tr1->SetPos(pos1);

		Gameobject::Update();
	}
	void Choice_select::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Choice_select::Release()
	{
		Gameobject::Release();
	}
}
