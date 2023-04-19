#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Minibos : public Gameobject
	{
	public:
		enum class eState
		{
			Down,
			Up,
			Left,
			Right,
			Waiting,
			Atack,
			Hurt,
			Death
		};


		Minibos(Gameobject* owner);
		~Minibos();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void down();
		void up();
		void right();
		void left();
		void waiting();
		void atack();
		void hurt();
		void death();





	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;

		Gameobject* mOwner;
		Vector2 mCenterpos;
		Vector2 pos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		int UpDOWN;
		float fDist;
		float time_check;
		int attack;
		
		
	};
}
