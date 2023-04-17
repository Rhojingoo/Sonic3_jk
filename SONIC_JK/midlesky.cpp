#include "midlesky.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	midlesky::midlesky()
	{
	}
	midlesky::~midlesky()
	{
	}
	void midlesky::Initialize()
	{
		mImage = Resources::Load<Image>(L"mksy", L"..\\Resources\\mksy.bmp");
		//mAnimator = AddComponent<Animator>();
		//{
		//	mAnimator->CreateAnimation(L"mksy", mImage, Vector2{0.0f,34.0f}, Vector2{ 15166.0f,72.0f }, Vector2{ 0.0f,24.0f }, 4, 1, 4, Vector2::Zero, 0.1);
		//}
				

		//mAnimator->Play(L"mksy", true);
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{2790.0f * 3, (940.0f * 3 - 175) });

 		Gameobject::Initialize();
	 }
  	void midlesky::Update()
	{
		Gameobject::Update();
            	}
	void midlesky::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	
		// 게임 오브젝트 클래스 (GameObject) 내의 Render 함수

	
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(pos);
			Vector2 mpos = Camera::CaluatePos(pos);



			// 애니메이션에 사용될 이미지의 프레임 정보                                           
			int frameWidth = 15166; // 프레임의 가로 크기
			int frameHeight = 48; // 프레임의 세로 크기
			int frameCount = 10; // 전체 프레임 수
			int currentFrame = 0; // 현재 프레임 인덱스
			int frameSpeed = 3; // 프레임 전환 속도 (낮을수록 빠름)
			DWORD currentTime = Time::DeltaTime(); // 현재 시간
			DWORD lastTime = currentTime; // 이전 시간

			//// 프레임 간의 시간 차이를 계산하여 애니메이션을 제어
			if (currentTime - lastTime >= frameSpeed)
			{
				currentFrame++; // 다음 프레임으로 전환
				if (currentFrame >= frameCount)
					currentFrame = 0; // 마지막 프레임일 경우 처음으로 되돌아감
				lastTime = currentTime; // 이전 시간 갱신
			}

			// 현재 프레임에 해당하는 이미지를 렌더링
			TransparentBlt(hdc, mpos.x / 3.f, mpos.y, frameWidth, frameHeight,
				mImage->GetHdc(), currentFrame * frameWidth, 34, frameWidth, frameHeight, RGB(13, 72, 7));

		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);
		//Vector2 mpos = Camera::CaluatePos(pos);
		//TransparentBlt(hdc, mpos.x/3.f, mpos.y, 15166.0f, 72.0f, mImage->GetHdc(), 0, 34, 15166.0f, 72.0f, RGB(13, 72, 7));
	}
	void midlesky::Release()
	{
		Gameobject::Release();
	}
}
