#pragma once
#include "jk_Boss.h"

namespace jk
{
	class boss_bomber : public Boss
	{
	public:
		boss_bomber(Gameobject* owner);
		~boss_bomber();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;		

	private:
		class Image* mImage;
		class Animator* mAnimator;	
		Vector2 mPos;	
		float mMonspeed;
	};
}