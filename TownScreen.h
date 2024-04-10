#ifndef TownScreen_h
#define TownScreen_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"

#include "Stage.h"
#include "InteractionMap.h"
#include "Town.h"
#include "Sidebar.h"


using namespace QuickSDL;

class TownScreen : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Town* mTown;
	int mStageNumber;

	SideBar* mSideBar;

private:



public:

	TownScreen();
	~TownScreen();

	void StartNewTown();

	void Update();
	void Render();


};

#endif /* TownScreen_h */
