#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Pixel_Ground;
	class Animator;
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
		Pixel_Ground* mGround;
	}; 
}