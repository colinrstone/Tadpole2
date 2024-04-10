#ifndef FloodGrid_h
#define FloodGrid_h

#include "GameEntity2.h"
#include "AnimatedTexture.h"
#include "Texture.h"
#include "InputManager.h"

using namespace QuickSDL;


class FloodGrid : public GameEntity {

private:

	InputManager* mInput;

	//Stage Number
	int mStageNumber;

	//Flood Grid
	int** mFloodGrid;
	int mRows;
	int mColumns;

	//Flood Tile Position 
	int mFloodHorizontal;
	int mFloodVertical;

	//Texture Selection
	bool mChangeFloodSelect;
	bool mFloodSelect;
	int mFloodValue;

	//Texture grid for flood levels
	AnimatedTexture* mAnimatedFloodTiles[3];

	//Texture for each type of terrains interface image and text
	Texture* mFloodText;



public:


private:


public:

	FloodGrid();
	~FloodGrid();

	void LoadInitialFloodGrid(int stageNumber, int** terrainGrid);
	int GetValuesFloodGrid(int row, int column, int stageNumber);

	void LoadFloodGrid(int** terrainGrid);
	void DrawFloodGrid();

	void HandleFloodSelect();
	void DrawFloodInterface();

	void Update(int** terrainGrid);
	void Render();


};

#endif /* FloodGrid_h */