#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	class Ground;
	class Animator;
	class boss_bomber : public Gameobject
	{
	public:
		enum class eState
		{
			Move,
			Death
		};

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
		void move();
		void death();


	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;

		int mDir;		
		float mMonspeed;
		Vector2 pos;		

		float fDist;
		Gameobject* mOwner;

	

	};
}