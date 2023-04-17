#pragma once
#include "jk_Entity.h"

namespace jk
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;  //가상함수에  = 0을 붙이면, 순수가상함수가되고 순수가상함수를 갖은 클래스는 추상클래스를 만듬.
		// 추상클래스는 상속을받은 자식은 무조적 순수가상함수를 사용해야 한다.													
		// HRESULT는 윈도우에서 실패나, 승인을 얘기한다.
		const std::wstring& GetKey() { return mKey; }  // wstring은 문자열 자료형이기 떄문에 &'참조'를 안붙이면 글자하나하나만 옮겨지므로 레퍼런스를 붙여 주소만을옮길수 있도록한다.
		const std::wstring& GetPath() { return mPath; }
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;
	};


	//class Image : public Resource
	//{

	//};

	//class Sound : public Resource
	//{

	//};
}
