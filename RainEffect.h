#ifndef RainEffect_h
#define RainEffect_h
#include "RainLayer.h"


#include <iostream>
#include <cctype>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;


class RainEffect {


private:



	static RainEffect* sInstance;
	//int mRandomv;
	//int mRandomh;

	static const int LAYER_COUNT = 3;
	RainLayer* mLayers[LAYER_COUNT];

public:


	static RainEffect* Instance(int randomv, int randomh);
	static void Release();


	int RandomVertical(void);
	int RandomHorizontal(void);

	void Scroll(bool b);

	void Update();
	void Render();

private:

	RainEffect(int randomv, int randomh);
	~RainEffect();







};



#endif /* RainEffect_h */

