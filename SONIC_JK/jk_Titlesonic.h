#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Titlesonic : public Gameobject
	{
	public:
		//enum class eState
		//{
		//	Idle,	
		//	Move,
		//};

		Titlesonic();
		~Titlesonic();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		Animator* GetmAnimator() { return mAnimator; }

		void startscene();


	//private:
	//	void idle();
	//	void move();

		

	private:
		int mDir;
		Image* mImage;
		eState mState;
		Animator* mAnimator;
		Animator* mAnimator1;
		Gameobject* mOwner;
		bool bTurn;
		float time;
		int turnindex;
	};

}