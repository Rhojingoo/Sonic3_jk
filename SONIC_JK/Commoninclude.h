#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <assert.h>   //assert.h �� ������ ��� ���� �޽����� ����Ѵ�.(bmp���Ͽ� �ɷ�����)



// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>


//#include <random>// �ּҰ�(min)�� �ִ밪(max) ������ ������ �ε��Ҽ��� ���� ��ȯ�ϴ� �Լ�


#pragma comment(lib, "Msimg32.lib")   //�Ҵ�ĳ���� ����̹� �����ҋ� �ʿ� 


#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64




//#include <random>
//
//// �ּҰ�(min)�� �ִ밪(max) ������ ������ �ε��Ҽ��� ���� ��ȯ�ϴ� �Լ�
//float RandomFloat(float min, float max)
//{
//    // C++11 �̻󿡼� �����Ǵ� random ���̺귯���� ����Ͽ� ������ ���� ����
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> dis(min, max);
//    return dis(gen);
//}