#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class check2 : public BackGround
	{
	public:
		check2();
		~check2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetCheckTargetGround(Pixel_Ground* ground) { mGround = ground; }


	private:
		class Collider* mCollider;
		class Pixel_Ground* mGround;
	}; 
}