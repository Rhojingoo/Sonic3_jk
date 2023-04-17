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
	
		// ���� ������Ʈ Ŭ���� (GameObject) ���� Render �Լ�

	
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			tr->SetPos(pos);
			Vector2 mpos = Camera::CaluatePos(pos);



			// �ִϸ��̼ǿ� ���� �̹����� ������ ����                                           
			int frameWidth = 15166; // �������� ���� ũ��
			int frameHeight = 48; // �������� ���� ũ��
			int frameCount = 10; // ��ü ������ ��
			int currentFrame = 0; // ���� ������ �ε���
			int frameSpeed = 3; // ������ ��ȯ �ӵ� (�������� ����)
			DWORD currentTime = Time::DeltaTime(); // ���� �ð�
			DWORD lastTime = currentTime; // ���� �ð�

			//// ������ ���� �ð� ���̸� ����Ͽ� �ִϸ��̼��� ����
			if (currentTime - lastTime >= frameSpeed)
			{
				currentFrame++; // ���� ���������� ��ȯ
				if (currentFrame >= frameCount)
					currentFrame = 0; // ������ �������� ��� ó������ �ǵ��ư�
				lastTime = currentTime; // ���� �ð� ����
			}

			// ���� �����ӿ� �ش��ϴ� �̹����� ������
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
