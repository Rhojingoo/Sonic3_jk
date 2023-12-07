#pragma once
#include "jk_Gameobject.h"
namespace jk
{
	class Effect : public Gameobject
	{
	public:
		Effect();
		~Effect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}


