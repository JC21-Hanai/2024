#include "time.h"
#include <Windows.h>
#include <DxLib.h>
namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
	float refreshRate;
	// 直近の処理時間を保存
	const int BUF_SIZE = 30;
	float timeBuf[BUF_SIZE];
	int readP;
	int writeP;
};

void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);

	HDC hdc = GetDC(GetMainWindowHandle());	// デバイスコンテキストの取得
	refreshRate = (float)GetDeviceCaps(hdc, VREFRESH);	// リフレッシュレートの取得
	ReleaseDC(GetMainWindowHandle(), hdc);	// デバイスコンテキストの解放

	readP = 0;
	writeP = 0;
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	float dt = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
	timeBuf[writeP] = dt;
	writeP = (writeP+1) % BUF_SIZE;
	if (writeP == readP) {
		readP = (readP + 1) % BUF_SIZE;
	}
	float sum = 0;
	int num = 0;
	for (int i = readP; i != writeP; i = (i + 1) % BUF_SIZE) {
		sum += timeBuf[i];
		num++;
	}
	if (num>BUF_SIZE/2)
		deltaTime = sum / num;
	else
		deltaTime = dt;
	//int frames = (int)((dt * 1.2f) * refreshRate);
	//if (frames >= 2)
	//{
	//	frames = 2;
	//}
	//deltaTime = frames / refreshRate;
}

float Time::DeltaTime()
{
	return deltaTime;
}

void Time::Release()
{
}