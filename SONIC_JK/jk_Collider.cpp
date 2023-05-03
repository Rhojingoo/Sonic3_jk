#include "jk_Collider.h"
#include "jk_Transform.h"
#include "jk_GameObject.h"
#include "jk_Input.h"
#include "jk_Camera.h"

namespace jk
{
	int Collider::ONOFF = 0;
	UINT Collider::ColliderNumver = 0;
	Collider::Collider()
		: Component(jk_ComponentType::Collider)
		, mCenter(Vector2 ::Zero)
		, mScale (Vector2::One)		
		, mPos(Vector2::Zero)
		, mSize(100.0f,100.0f)
		, mID(ColliderNumver++)
		,mCollisionCount(0)
		
	{
	
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mScale = tr->GetScale();		
		mPos = tr->GetPos() + mCenter;		
	}

	void Collider::Render(HDC hdc)
	{

		if (Input::GetKeyDown(eKeyCode::P))
		{
			ONOFF = 1;
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			ONOFF = 0;
		}
	
			HPEN pen = NULL;
			if (mCollisionCount == 0)
				pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
			else
				pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));


			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

			Vector2 pos = Camera::CaluatePos(mPos);

			if (ONOFF == 0)
			{
				Rectangle(hdc, pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);
			}
			//Rectangle(hdc, pos.x - mSize.x/2, pos.y - mSize.y, pos.x + mSize.x /2, pos.y);


			(HPEN)SelectObject(hdc, oldPen);
			(HBRUSH)SelectObject(hdc, oldBrush);
			DeleteObject(pen);

			mCollisionCount = 0;
		
	}

	void Collider::Release()
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		//mCollisionCount++;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		mCollisionCount = 1;
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		//mCollisionCount--;
		GetOwner()->OnCollisionExit(other);
	}
}