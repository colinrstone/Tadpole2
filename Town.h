#ifndef Town_h
#define Town_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"


#include "TerrainGrid.h"
#include "FloodGrid.h"

#include "RainEffect.h"
#include "Car.h"


using namespace QuickSDL;

class Town : public GameEntity {

public:

	enum LEVEL_STATES { running, finished, gameover };

	LEVEL_STATES mCurrentState;
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mStageBackground;	
	

	bool mNewTownStarted;

	TerrainGrid* mTerrainGrid;
	int** mTerrainValues;

	FloodGrid* mFloodGrid;
	int** mFloodValues;


	RainEffect* mRainEffect;
	Car* mCar;



private:

	int** mTileMap;
	int mTileRows;
	int mTileColumns;

private:



public:

	Town();
	~Town();
	
	LEVEL_STATES State();

	//RNG
	int RandomVertical(void);
	int RandomHorizontal(void);
	int RandomCount(int count);
	int RandomFiftyFifty(void);

	void LoadInitialGrids(int stageNumber);
	void LoadInitialValues(int stageNumber);

	void LoadGrids();
	void DrawGrids();

	void Update();
	void Render();


};

#endif /* Town_h */
