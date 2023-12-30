#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Collider;
	class Dead_line : public BackGround
	{
	public:

		Dead_line();
		~Dead_line();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;



	private:
		Collider* mCollider;
	};

}
