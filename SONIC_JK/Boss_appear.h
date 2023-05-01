#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	class Ground;
	class Animator;
	class Boss_appear : public Gameobject
	{
	public:
		enum class eState
		{
			Move,
			Death
		};

		Boss_appear(Gameobject* owner);
		~Boss_appear();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


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