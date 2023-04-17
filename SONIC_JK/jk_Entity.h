#pragma once
#include "SONIC_Engine.h"

namespace jk
{
	class Entity
	{
	public:
		Entity();
		~Entity();


		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }



	private:
		std::wstring mName;
		UINT64 mID;
	};

}
