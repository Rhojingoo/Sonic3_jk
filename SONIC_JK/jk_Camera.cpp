#include "jk_Camera.h"
#include "jk_Application.h"
#include "jk_Gameobject.h"
#include "jk_Transform.h"
#include "jk_Input.h"
#include "jk_Time.h"
#include "jk_Image.h"

extern jk::Application application;
namespace jk
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	Gameobject* Camera::mTarget = nullptr;

	//Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	//class Image* Camera::mCutton = nullptr;
	//float Camera::mCuttonAlpha = 1.0f;
	//float Camera::mAlphaTime = 0.0f;
	//float Camera::mEndTime = 5.0f;

	void Camera::Initialize()
	{
		mResolution.x = static_cast<float>(application.GetWidth());
		mResolution.y = static_cast<float>(application.GetHeight());
		mLookPosition = (mResolution / 2.0f);		

		//mType = eCameraEffectType::FadeIn;
		//mCutton = Image::Create(L"Cutton", mResolution.x, mResolution.y, RGB(255, 255,255));
	}

	void Camera::Update()
	{		
		//카메라가 움직일수 있는기능
		if (Input::GetKey(eKeyCode::G))
			mLookPosition.x -= 100.0f * static_cast<float>(Time::DeltaTime());

		if (Input::GetKey(eKeyCode::J))
			mLookPosition.x += 100.0f * static_cast<float>(Time::DeltaTime());

		if (Input::GetKey(eKeyCode::Y))
			mLookPosition.y -= 100.0f * static_cast<float>(Time::DeltaTime());

		if (Input::GetKey(eKeyCode::H))
			mLookPosition.y += 100.0f * static_cast<float>(Time::DeltaTime());

		
		//캐릭터를 중심으로 움직이게 설정
		if (mTarget != nullptr)
		{
			mLookPosition
				= mTarget->GetComponent<Transform>()->GetPos();
		}
		mDistance.x = mLookPosition.x - (mResolution.x / 2.0f);
		mDistance.y = mLookPosition.y - (mResolution.y/ 2.0f);

		//if (mAlphaTime < mEndTime)
		//{
		//	//255->1
		//	mAlphaTime += Time::DeltaTime();
		//	float ratio = (mAlphaTime / mEndTime);

		//	if (mType == eCameraEffectType::FadeIn)
		//	{
		//		mCuttonAlpha = 1.0f - ratio;
		//	}
		//	else if (mType == eCameraEffectType::FadeOut)
		//	{
		//		mCuttonAlpha = ratio;
		//	}
		//	else
		//	{
		//	}
		//}
	}

	void Camera::Render(HDC hdc)
	{
		//if (mAlphaTime<mEndTime && mType == eCameraEffectType::FadeIn)
		//{
		//	BLENDFUNCTION func = {};
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = 0;
		//	func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		//	AlphaBlend(hdc, 0, 0
		//		, mResolution.x, mResolution.y
		//		, mCutton->GetHdc()
		//		, 0, 0
		//		, mCutton->GetWidth(), mCutton->GetHeight()
		//		, func);
		//}
	}

	void Camera::Clear()
	{
		mResolution.x = static_cast<float>(application.GetWidth());
		mResolution.y = static_cast<float>(application.GetHeight());
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
		mTarget = nullptr;
	}
}