#ifndef PlayLevel_h
#define PlayLevel_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"


using namespace QuickSDL;

class PlayLevel : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;

	Texture* mTile;
	int mTileValue;

	Texture* mDirt;
	Texture* mWater;
	Texture* mGrass;
	Texture* mVerticalStreet;
	Texture* mHorizontalStreet;
	Texture* mIntersectionStreet;

	AnimatedTexture* mAnimatedTile;
	AnimatedTexture* mGrassOne;

	bool mPassable;
	int mStatus;

	int mMinimapVector;

	bool mPlayerOccupy;
	bool mUnitOccupy;
	bool mEnemyOccupy;
	bool mAdjacent;

	int mMap[26][17];
	int mType;


private:



public:

	PlayLevel(int tilemap[26][17]);
	~PlayLevel();

	void LoadMap(int arr[26][17]);
	void DrawMap();


	void Update();
	void Render();


};





#endif /* PlayLevel_h */