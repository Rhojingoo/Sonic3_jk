#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Rigidbody;
	class Add_force : public BackGround
	{
	public:
		Add_force();
		~Add_force();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetAddforce(int a) { mCheck_up = a; }



	private:
		class Collider* mCollider;
		Rigidbody* mRigidbody;
		int mCheck_up;
	};
}
