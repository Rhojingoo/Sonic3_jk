#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Ground;
	class Animator;
	class check_circle : public Gameobject
	{
	public:
		check_circle();
		~check_circle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		Image* mImage;
		float mTime;
		float checktime;
		class Collider* mCollider;
		Ground* mGround;
		int checkcheck;
	};
}