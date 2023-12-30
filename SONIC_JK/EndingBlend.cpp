#include "EndingBlend.h"
#include "jk_SceneManager.h"
#include "jk_Time.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Image.h"

namespace jk
{

	EndingBlend::EndingBlend()
		:mCheckTime(0.f)
		, mImage(nullptr)
	{

	}

	EndingBlend::~EndingBlend()
	{
	}

	void EndingBlend::Initialize()
	{
		mImage = Resources::Load<Image>(L"AlpaB", L"..\\Resources\\Fadeinout.bmp");
		Gameobject::Initialize();
	}

	void EndingBlend::Update()
	{
		Gameobject::Update();
	}

	void EndingBlend::Render(HDC hdc)
	{
		mCheckTime += (float)Time::DeltaTime() * 255.0f * 0.7f;
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = (BYTE)mCheckTime;

		AlphaBlend(hdc, -1, -1, 1201, 841, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		if (mCheckTime > 255.0f)
		object::Destory(this);

		Gameobject::Render(hdc);
	}

	void EndingBlend::Release()
	{
		Gameobject::Release();
	}
}