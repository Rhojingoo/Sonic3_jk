#pragma once
#include "jk_Entity.h"

namespace jk
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;  //�����Լ���  = 0�� ���̸�, ���������Լ����ǰ� ���������Լ��� ���� Ŭ������ �߻�Ŭ������ ����.
		// �߻�Ŭ������ ��������� �ڽ��� ������ ���������Լ��� ����ؾ� �Ѵ�.													
		// HRESULT�� �����쿡�� ���г�, ������ ����Ѵ�.
		const std::wstring& GetKey() { return mKey; }  // wstring�� ���ڿ� �ڷ����̱� ������ &'����'�� �Ⱥ��̸� �����ϳ��ϳ��� �Ű����Ƿ� ���۷����� �ٿ� �ּҸ����ű�� �ֵ����Ѵ�.
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
