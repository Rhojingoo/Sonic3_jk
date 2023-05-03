#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Tails.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Act1_Water : public Gameobject
	{
	public:
		Act1_Water();
		~Act1_Water();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Water_Splashes(float a, float b);

	private:
		Image* mImage;
		float mTime;
		float checktime;

		Sonic::eSonicState sonicState;
		Tails::eTailsState tails_State;
	};
}