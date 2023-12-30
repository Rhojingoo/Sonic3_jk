#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Collider;
	class Animator;
	class Act1_2_Boss_wall : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Act1_2_Boss_wall();
		~Act1_2_Boss_wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void death();


	private:
		class Collider* mCollider;	
	};

}
