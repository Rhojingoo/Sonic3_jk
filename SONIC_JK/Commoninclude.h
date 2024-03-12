#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <assert.h>   //assert.h 는 거짓인 경우 진단 메시지를 출력한다.(bmp파일외 걸러내기)



// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>


//#include <random>// 최소값(min)과 최대값(max) 사이의 무작위 부동소수점 값을 반환하는 함수


#pragma comment(lib, "Msimg32.lib")   //소닉캐릭터 배경이미 삭제할떄 필요 


#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64




//#include <random>
//
//// 최소값(min)과 최대값(max) 사이의 무작위 부동소수점 값을 반환하는 함수
//float RandomFloat(float min, float max)
//{
//    // C++11 이상에서 제공되는 random 라이브러리를 사용하여 무작위 값을 생성
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> dis(min, max);
//    return dis(gen);
//}