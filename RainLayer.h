#ifndef RainLayer_h
#define RainLayer_h
#include "Rain.h"


class RainLayer {


private:

	static const int RAIN_COUNT = 30;
	Rain* mRaindrops[RAIN_COUNT];




public:

	RainLayer(int layer, int randomv, int randomh);
	~RainLayer();

	void Update();
	void Render();



};


#endif /* RainLayer_h */
