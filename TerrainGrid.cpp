#include "TerrainGrid.h"

//Terrain selection box constants
const int TERRAIN_SELECT_WIDTH = 32;
const int TERRAIN_SELECT_HEIGHT = 32;

//TERRAIN MAPS
//
// 0 is Water
// 1 is Dirt
// 2 is Grass
// 3 is Vertical Street
// 4 is Horizontal Street
// 5 is Intersection Street
//

int mLevelOneTerrain[28][17] = {

	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,2,2,2,4,2,2,2,0,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2}


};

int mLevelTwoTerrain[56][23] = {

	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,2,2,2,4,2,2,2,0,2,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2,2,2,2,2,2}

};

TerrainGrid::TerrainGrid() {

	mInput = InputManager::Instance();

	mStageNumber = NULL;

	mTerrainGrid = nullptr;
	mRows = NULL;
	mColumns = NULL;

	mTerrainHorizontal = Graphics::Instance()->SCREEN_WIDTH * 0.98;
	mTerrainVertical = Graphics::Instance()->SCREEN_HEIGHT * 0.72;

	mAnimatedTiles[0] = new AnimatedTexture("laketwo.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);
	mAnimatedTiles[1] = new AnimatedTexture("dirt.png", 0, 0, 32, 32, 1, 0.75f, AnimatedTexture::horizontal);
	mAnimatedTiles[2] = new AnimatedTexture("grassone.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);
	mAnimatedTiles[3] = new AnimatedTexture("verticalstreet.png", 0, 0, 32, 32, 1, 0.75f, AnimatedTexture::horizontal);;
	mAnimatedTiles[4] = new AnimatedTexture("horizontalstreet.png", 0, 0, 32, 32, 1, 0.75f, AnimatedTexture::horizontal);
	mAnimatedTiles[5] = new AnimatedTexture("intersectionstreet.png", 0, 0, 32, 32, 1, 0.75f, AnimatedTexture::horizontal);

	mTerrainText[0] = new Texture("Water", "unispace.ttf", 14, { 72, 31, 228 });
	mTerrainText[1] = new Texture("Dirt", "unispace.ttf", 14, { 72, 31, 228 });
	mTerrainText[2] = new Texture("Grass", "unispace.ttf", 14, { 72, 31, 228 });
	mTerrainText[3] = new Texture("Street", "unispace.ttf", 14, { 72, 31, 228 });
	mTerrainText[4] = new Texture("Street", "unispace.ttf", 14, { 72, 31, 228 });
	mTerrainText[5] = new Texture("Street", "unispace.ttf", 14, { 72, 31, 228 });

	mTerrainInterfaceTexture[0] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[0]->Pos(Vector2(1000, 1000));
	mTerrainInterfaceTexture[1] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[1]->Pos(Vector2(1000, 1000));
	mTerrainInterfaceTexture[2] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[2]->Pos(Vector2(1000, 1000));
	mTerrainInterfaceTexture[3] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[3]->Pos(Vector2(1000, 1000));
	mTerrainInterfaceTexture[4] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[4]->Pos(Vector2(1000, 1000));
	mTerrainInterfaceTexture[5] = new Texture("grassinterface.png");
	mTerrainInterfaceTexture[5]->Pos(Vector2(1000, 1000));

	mTerrainHighlight = new Texture("tilehighlight.png");
	mTerrainHighlight->Scale(Vector2(2.0f, 2.0f));
	mTerrainHighlightOn = NULL;

	mChangeTerrainSelect = false;
	mTerrainSelect = false;
	mTerrainType = NULL;
}

TerrainGrid::~TerrainGrid() {

	for (int row = 0; row < mRows; row++)
	{
		for (int column = 0; column < mColumns; column++)
		{
			mTerrainGrid[row][column] = NULL;
		}
	}

	for (int i = 0; i < 6; ++i) {
		delete mAnimatedTiles[i];
		delete mTerrainText[i];
		delete mTerrainInterfaceTexture[i];
	}

	mStageNumber = NULL;
	mRows = NULL;
	mColumns = NULL;

	mTerrainHorizontal = NULL;
	mTerrainVertical = NULL;

	mTerrainHighlight = NULL;

	mChangeTerrainSelect = NULL;
	mTerrainSelect = NULL;
	mTerrainType = NULL;

}

int TerrainGrid::GetValuesTerrainGrid(int row, int column, int stageNumber) {

	switch (stageNumber)
	{
	case 0:
		break;

	case 1:

		return  mLevelOneTerrain[row][column];
		break;

	case 2:

		return  mLevelTwoTerrain[row][column];
		break;

	default:
		break;
	}

}

void TerrainGrid::LoadInitialTerrainGrid(int stageNumber, int** terrainGrid) {

	mStageNumber = stageNumber;

	// Deallocate previous memory if it was allocated
	if (mTerrainGrid != nullptr) {
		for (int i = 0; i < mRows; ++i) {
			delete[] mTerrainGrid[i];
		}
		delete[] mTerrainGrid;
	}

	// Set new dimensions based on stageNumber
	switch (stageNumber) {
	case 0:
		// Handle stage 0 initialization if needed
		break;
	case 1:
		mRows = 28;
		mColumns = 17;
		break;
	case 2:
		mRows = 56;
		mColumns = 23;
		break;
	default:
		// Handle default case if needed
		break;
	}

	// Allocate memory for mTerrainGrid
	mTerrainGrid = new int* [mRows];
	for (int i = 0; i < mRows; ++i) {
		mTerrainGrid[i] = new int[mColumns];
	}

	// Copy terrainGrid values to mTerrainGrid
	for (int row = 0; row < mRows; ++row) {
		for (int col = 0; col < mColumns; ++col) {
			mTerrainGrid[row][col] = terrainGrid[row][col];
		}
	}
			
}

void TerrainGrid::LoadTerrainGrid(int** terrainGrid) {

		for (int row = 0; row < mRows; row++)
		{
			for (int column = 0; column < mColumns; column++)
			{
				mTerrainGrid[row][column] = terrainGrid[row][column];
			}
		}
}

void TerrainGrid::DrawTerrainGrid() {

	for (int row = 0; row < mRows; row++) {

		for (int column = 0; column < mColumns; column++) {

			int terrainType = mTerrainGrid[row][column];

			mAnimatedTiles[terrainType]->Pos(Vector2((mTerrainHorizontal) - (68.0f * row), ((mTerrainVertical) - (68.0f * column)) ));
			mAnimatedTiles[terrainType]->Scale(Vector2(2.0f, 2.0f));
			mAnimatedTiles[terrainType]->Render();

		}

	}

}

void TerrainGrid::HandleTerrainSelect() {

	// If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {
		// Get mouse position

		int x, y;
		SDL_GetMouseState(&x, &y);
		mTerrainSelect = false;

		// Loop through the terrain grid
		for (int row = 0; row < mRows; row++) {
			for (int column = 0; column < mColumns; column++) {

				if (mTerrainSelect == true) {
					break;
				}

				if (x < 840 && x > 640 && y < 883 && y > 720) {
					break;
				}

				int horizontal = row * 68;
				int vertical = column * 68;

				//Check if mouse is in button
				bool inside = true;

				if (x < mTerrainHorizontal - TERRAIN_SELECT_WIDTH - horizontal || x > mTerrainHorizontal + TERRAIN_SELECT_WIDTH - horizontal || y < mTerrainVertical - TERRAIN_SELECT_HEIGHT - vertical || y > mTerrainVertical + TERRAIN_SELECT_HEIGHT - vertical) 
					inside = false;

				if (inside == true) {

					//Mouse is inside tile, change select variable to True; change loop break variable (mTileselect) to True 
					mChangeTerrainSelect = true;
					mTerrainSelect = true;

					mTerrainHighlight->Pos(Vector2((mTerrainHorizontal) - (68.0f * row), ((mTerrainVertical) - (68.0f * column))));
					mTerrainHighlight->Scale(Vector2(2.0f, 2.0f));
					mTerrainHighlightOn = true;

					int terrainType = mTerrainGrid[row][column];
					mTerrainType = terrainType;

					mTerrainText[terrainType]->Pos(Vector2(785, 865));;
					//mTerrainInterfaceTexture[terrainType]->Pos(Vector2(1000, 1000));

				}
				else {
					// Mouse click is not inside the current tile
					mChangeTerrainSelect = false;

				}
			}
		}
	} 
}

void TerrainGrid::DrawTerrainSelect() {

	if (mChangeTerrainSelect == true) {

		if (mTerrainHighlightOn)
		mTerrainHighlight->Render();

		switch (mTerrainType)
		{
		case 0:
			mTerrainText[0]->Render();
			mTerrainInterfaceTexture[0]->Render();
			break;
		case 1:
			mTerrainText[1]->Render();
			mTerrainInterfaceTexture[1]->Render();
			break;
		case 2:
			mTerrainText[2]->Render();
			mTerrainInterfaceTexture[2]->Render();
			break;
		case 3:
			mTerrainText[3]->Render();
			mTerrainInterfaceTexture[3]->Render();
		case 4:
			mTerrainText[4]->Render();
			mTerrainInterfaceTexture[4]->Render();
			break;
		case 5:
			mTerrainText[5]->Render();
			mTerrainInterfaceTexture[5]->Render();
			break;
		default:
			break;
		}

	}

}

void TerrainGrid::Update(int** terrainGrid) {

	HandleTerrainSelect();
	LoadTerrainGrid(terrainGrid);
	//mAnimatedTile->Update();

	for (int i = 0; i < 6; ++i) {
		mAnimatedTiles[i]->Update();
	}

}

void TerrainGrid::Render() {

	DrawTerrainGrid();
	DrawTerrainSelect();
}
