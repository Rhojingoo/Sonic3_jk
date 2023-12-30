#include "jk_Blending.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Object.h"
#include "jk_Image.h"


namespace jk
{
	Blending::Blending()
		:mCcheckTime(255.f)
		, mImage(nullptr)	

	{
	}
	Blending::~Blending()
	{
	}
	void Blending::Initialize()
	{
		mImage = Resources::Load<Image>(L"AlpaB", L"..\\Resources\\Fadeinout.bmp");
		Gameobject::Initialize();
	}
	void Blending::Update()
	{
		Gameobject::Update();
	}
	void Blending::Render(HDC hdc)
	{
		Gameobject::Render(hdc);	


		mCcheckTime -= static_cast<float>(Time::DeltaTime()) *255*0.7f;
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = (BYTE)mCcheckTime;
			AlphaBlend(hdc, -1, -1, 1201, 841, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

			if(mCcheckTime<0.0f)
			object::Destory(this);

	}
	void Blending::Release()
	{
		Gameobject::Release();
	}
}