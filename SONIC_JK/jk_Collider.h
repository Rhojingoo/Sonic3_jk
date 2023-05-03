#pragma once
#include "jk_Component.h"

namespace jk
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);


		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		void SetScale(Vector2 scale) { mScale = scale; };
		void SetPos(Vector2 pos) { mPos = pos; };
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }

		Vector2 Getpos() { return mPos; }
		UINT GetID() { return mID; }

	private:
		static UINT ColliderNumver;
		UINT mCollisionCount;
		UINT mID;
		Vector2 mCenter;
		Vector2 mSize;
		Vector2 mScale;		
		Vector2 mPos;

		static int ONOFF;
	};

}
