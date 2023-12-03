#include "jk_Animation.h"
#include "jk_Time.h"
#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_Transform.h"
#include "jk_Gameobject.h"
#include "jk_Camera.h"

namespace jk
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mSheetImage(nullptr)
		, mTime(0.0f)
		, mbComplete(false)
		, mSpriteIndex(0)

	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Initialize()
	{
	}

	void Animation::Update()
	{
		if (mbComplete == true)
			return;

		mTime += static_cast<float>(Time::DeltaTime());
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mSpriteSheet.size() <= mSpriteIndex + 1)
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex++;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		Transform* tr
			= mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		
		// 이미지가 그려질 좌표는 오브젝트 좌표의 위쪽 중간에 그려진다.
		//  겟포스(좌표)를 캐릭터의 발을 기준으로 포지션을 계산해서 화면에 띄운다
		Vector2 pos = tr->GetPos(); 
		pos = Camera::CaluatePos(pos);
		pos += mSpriteSheet[mSpriteIndex].offset;
		pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;// 이미지가 곱하기 3을 안해준것을 써서 콜라이더에 대해 
		pos.y -= mSpriteSheet[mSpriteIndex].size.y;
	
	
			TransparentBlt(hdc, (int)(pos.x), (int)(pos.y)
				, (int)(mSpriteSheet[mSpriteIndex].size.x * scale.x*3)
				, (int)(mSpriteSheet[mSpriteIndex].size.y * scale.y*3)								
				, mSheetImage->GetHdc()
				, (int)(mSpriteSheet[mSpriteIndex].leftTop.x), (int)(mSpriteSheet[mSpriteIndex].leftTop.y)
				, (int)(mSpriteSheet[mSpriteIndex].size.x), (int)(mSpriteSheet[mSpriteIndex].size.y),
				RGB(13, 72, 7));

	}



	void Animation::Create(Image* sheet, Vector2 leftTop, Vector2 ChaSize, Vector2 ChaSpace, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		mSheetImage = sheet;
		Vector2 size = Vector2::One;
		size.x = ChaSize.x;
		size.y =ChaSize.y;
		int x = 0;
		int y = 0;
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite spriteInfo;				
			if (x ==coulmn)
			{
				x = 0;
				y++;
			}			

			spriteInfo.leftTop.x = leftTop.x + (size.x * x);		
			spriteInfo.leftTop.y = leftTop.y + (size.y * y);
			spriteInfo.size = Vector2(size.x - ChaSpace.x, size.y- ChaSpace.y);
			spriteInfo.offset = offset;
			spriteInfo.duration = duration;

			mSpriteSheet.push_back(spriteInfo);
			x++;
		}
	}

	void Animation::Reset()
	{	
			mSpriteIndex = 0;
			mTime = 0.0f;
			mbComplete = false;		
	}
}