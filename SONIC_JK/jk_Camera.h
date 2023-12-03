#pragma once
#include "SONIC_Engine.h"



namespace jk
{
	class Gameobject;	
	class Camera
	{
	public:
		enum class eCameraEffectType
		{
		None,
		FadeIn,
		FadeOut,
		Shake,
		End,
		};


		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(Gameobject* target) { mTarget = target; }
		static Vector2 CaluatePos(Vector2 pos) { return pos - mDistance; }	
		
		
		static Vector2 GetMove(Vector2 pos) { return pos - mMove; }


		static void SetCamera(int cam) { camera = cam; }


		//static void Move_L(float pos) { mMove.x = pos;}
		//static float GetMove_L() { return mMove.x; }
	
	
		

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static Gameobject* mTarget;

		static eCameraEffectType mType;
		static class Image* mCutton;
		static float mCuttonAlpha;
		static float mAlphaTime;
		static float mEndTime;
		static int camera;

		static Vector2 mMove;
		static Vector2 target_pos;		
	};
}

