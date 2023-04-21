#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"



namespace jk
{
	class Bullet_Act1_L_DIA : public Gameobject
	{
	public:
		Bullet_Act1_L_DIA(Gameobject* owner);
		~Bullet_Act1_L_DIA();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		Vector2 Sonic;
		Gameobject* mOwner;
	};
}
