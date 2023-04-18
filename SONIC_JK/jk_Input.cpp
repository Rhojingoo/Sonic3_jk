#include "jk_Input.h"




namespace jk
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		VK_UP,
		VK_DOWN,
		VK_LEFT,
		VK_RIGHT,
		VK_SPACE,
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	std::vector<Input::Key> Input::mKeys;
	int spKey;

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}
	void Input::Update()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ���� �־���
				if (mKeys[i].bPressed)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;
			}
			else // ���� �����ӿ� Ű�� �������� �ʴ�.
			{
				// ���� �����ӿ� ��Ű�� �����־���.
				if (mKeys[i].bPressed)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;
			}
		}


		//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		//{
		//	// ���� �����ӿ��� ���� �־���
		//	if (spKey.bPressed)
		//		spKey.state = eKeyState::Pressed;
		//	else
		//		spKey.state = eKeyState::Down;

		//	spKey.bPressed = true;
		//}
		//else // ���� �����ӿ� Ű�� �������� �ʴ�.
		//{
		//	// ���� �����ӿ� ��Ű�� �����־���.
		//	if (spKey.bPressed)
		//		spKey.state = eKeyState::Up;
		//	else
		//		spKey.state = eKeyState::None;

		//	spKey.bPressed = false;
		//}


	}

	void Input::Render(HDC hdc)
	{
	}

}