#pragma once
#include "jk_Resource.h"

namespace jk
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		COLORREF GetPixel(int x, int y);
		COLORREF GetPixel(const Vector2& pos);
		void Setpixel(int x, int y, COLORREF color);

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetWidth(UINT width) { mWidth = width; }
		void SetHeight(UINT height) { mHeight = height; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}
