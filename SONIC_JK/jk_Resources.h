#pragma once
#include "jk_Resource.h"

namespace jk
{
	class Resources
	{

	public:
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			//리소스맵에서 데이터를 탐색한다 데이터가 있다면 해당데이터를 반환하고
			//데이터가 없다면 end를 반환해준다.
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key); //이터레이터로 찾는다 안나온다면 END()로반환됨

			//찾고자 하는 데이터가 존재한다면
			//해당타입으로 형변환하여 반환
			if (iter != mResources.end())   // 이터레이터는 찾고자 하는 데이터가 없으면 엔드 데이터를 반환해줌으로 이를 이용.
			{
				return dynamic_cast<T*>(iter->second); //찾았다면 이미지를의값을 보낸다.
			}

			//데이터 없다면 널을 반환
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 해당 리소스가 없다면
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false); // 강제 종료 컴온에 인크루드함.
				return nullptr;
			}


			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}


		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}



	private:
		static std::map<std::wstring, Resource*> mResources;
	};						//이름, 리소스 = 이미지, 사운드 등
}
