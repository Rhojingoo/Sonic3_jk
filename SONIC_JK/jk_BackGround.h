#pragma once
#include "jk_Gameobject.h"
namespace jk
{
	class BackGround : public Gameobject
	{
	public:
		BackGround();
		~BackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}


