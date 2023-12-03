#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Ground;
	class check1 : public Gameobject
	{
	public:
		check1();
		~check1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetCheckTargetGround(Ground* ground) { mGround = ground; }


	private:
		class Collider* mCollider;
		Ground* mGround;
	};
}