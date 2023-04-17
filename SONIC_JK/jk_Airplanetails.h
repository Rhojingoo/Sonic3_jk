#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Airplanetails : public Gameobject
	
	{
	public:
		enum class eState
		{		
			Move,
		};

		Airplanetails();
		~Airplanetails();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		Animator* GetmAnimator() { return mAnimator; }

	private:		
		void move();

	private:
		int mDir;
		Image* mImage;
		eState mState;
		Animator* mAnimator;	
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mspeed;
		float maxdistance;
	};

}