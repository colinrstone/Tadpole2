#ifndef Rain_h
#define Rain_h
#include "Timer.h"
#include "Texture.h"

#include <iostream>
#include <cctype>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;
using namespace QuickSDL;


class Rain : public Texture {

private:


	static bool sScroll;

	Timer* mTimer;


	bool mVisible;
	float mFlickerTimer;
	float mFlickerSpeed;

	Vector2 RainPos;
	int mRandomv;
	int mRandomh;


	float mScrollSpeed;

public:
	static void Scroll(bool b);

	Rain(int layer, int randomh, int randomv);
	~Rain();

	int RandomHeight(void);
	void Update();
	void Render();


private:
	void ScrollRain();


};





#endif /* Rain_h */

