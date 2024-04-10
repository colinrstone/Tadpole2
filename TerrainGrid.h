#ifndef TerrainGrid_h
#define TerrainGrid_h

#include "GameEntity2.h"
#include "AnimatedTexture.h"
#include "Texture.h"
#include "InputManager.h"

using namespace QuickSDL;


class TerrainGrid : public GameEntity {

private:

	InputManager* mInput;

	//Stage Number
	int mStageNumber;

	//Terrain Grid
	int** mTerrainGrid;
	int mRows;
	int mColumns;

	//Terrain Tile Position 
	int mTerrainHorizontal;
	int mTerrainVertical;

	//Texture Selection
	bool mChangeTerrainSelect;
	bool mTerrainSelect;
	int mTerrainType;

	//Texture grid for each terrain
	AnimatedTexture* mAnimatedTiles[6];

	//Texture for each type of terrains interface image and text
	Texture* mTerrainText[6];
	Texture* mTerrainInterfaceTexture[6];

	//This is a universal highlight that should either be moved by itself or just live here solely on the Terrain Grid because
	//every stage will have terrain at the very least as a universal object
	Texture* mTerrainHighlight;
	bool mTerrainHighlightOn;
	//
	//

public:


private:


public:

	TerrainGrid();
	~TerrainGrid();

	void LoadInitialTerrainGrid(int stageNumber, int** terrainGrid);
	int GetValuesTerrainGrid(int row, int column, int stageNumber);

	void LoadTerrainGrid(int** terrainGrid);
	void DrawTerrainGrid();

	void HandleTerrainSelect();
	void DrawTerrainSelect();

	void Update(int** terrainGrid);
	void Render();


};

#endif /* TerrainGrid_h */