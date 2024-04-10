#ifndef RainProcess_h
#define RainProcess_h

#include "Timer.h"

using namespace QuickSDL;

class RainProcess {


private:

	Timer* mTimer;	Timer* mTimer;
	float mRainSpawnTimer;


public:

	void Update();
	void Render();

private:

	RainProcess();
	~RainProcess();

	void HandleRainSpawn();

};



#endif /* RainProcess_h */

