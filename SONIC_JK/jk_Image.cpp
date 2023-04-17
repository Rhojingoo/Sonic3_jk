#include "jk_Image.h"
#include "jk_Application.h"
#include "jk_Resources.h"

extern jk::Application application;
namespace jk
{
	Image* Image::Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb)
	{
		if (widht == 0 || height == 0)
			return nullptr;


		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, widht, height);

		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = widht;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Image>(name, image);

		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldbrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldbrush);
		DeleteObject(oldbrush);

		return image;
	}


	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Image::~Image()
	{
	}

	HRESULT Image::Load(const std::wstring& path)
	{

		mBitmap = (HBITMAP)LoadImageW(nullptr       //비트맵 추가하여 이미지 넣기(소닉)
			, path.c_str(), IMAGE_BITMAP
			, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
			return E_FAIL;

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);   
		DeleteObject(oldBitmap);

		return S_OK;
	}

	COLORREF Image::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}
	COLORREF Image::GetPixel(const Vector2& pos)
	{
		return ::GetPixel(mHdc, static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
	void Image::Setpixel(int x, int y, COLORREF color)
	{
		::SetPixel(mHdc, x, y, color);
	}
}