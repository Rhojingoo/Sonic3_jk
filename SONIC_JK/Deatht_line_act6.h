#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Deatht_line_act6 : public BackGround
	{
	public:

		Deatht_line_act6();
		~Deatht_line_act6();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		class Collider* mCollider;

	};

}