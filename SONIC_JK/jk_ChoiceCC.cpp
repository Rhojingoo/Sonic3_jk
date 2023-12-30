#include "jk_ChoiceCC.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Image.h"

namespace jk
{
	ChoiceCC::ChoiceCC()
		: mImage1(nullptr)
		, mAnimator(nullptr)
	{	

	}

	ChoiceCC::~ChoiceCC()
	{
	}

	void ChoiceCC::Initialize()
	{
		mImage1 = Resources::Load<Image>(L"CC_BG1", L"..\\Resources\\Ch_BG1.bmp");
		Gameobject::Initialize();
	}

	void ChoiceCC::Update()
	{
		Gameobject::Update();
	}

	void ChoiceCC::Render(HDC hdc)
	{
		//소닉&테일즈창
		Gameobject::Render(hdc);
		Transform* tr1 = GetComponent<Transform>();
		Vector2 pos1 = tr1->GetPos();//24,216   343,439
		TransparentBlt(hdc, 272, 39, 291, 552, mImage1->GetHdc(), 49, 496, 97, 184, RGB(13, 72, 7));

		//너클즈창
		Gameobject::Render(hdc);
		Transform* tr2 = GetComponent<Transform>();
		Vector2 pos2 = tr2->GetPos();//24,216   343,439
		TransparentBlt(hdc, 686, 39, 291, 552, mImage1->GetHdc(), 277, 495, 97, 184, RGB(13, 72, 7));

		//데이터셀렉창
		Gameobject::Render(hdc);
		Transform* tr3 = GetComponent<Transform>();
		Vector2 pos3 = tr3->GetPos();//24,216   343,439
		TransparentBlt(hdc, 465, 650, 342, 100, mImage1->GetHdc(), 350, 409, 114, 33, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}

	void ChoiceCC::Release()
	{
		Gameobject::Release();
	}
}