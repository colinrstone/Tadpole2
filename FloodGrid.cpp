#include "FloodGrid.h"

//Flood selection box constants
const int FLOOD_SELECT_WIDTH = 32;
const int FLOOD_SELECT_HEIGHT = 32;

//FLOOD MAPS
//
// 0 is Empty
// X is Value of Flood
//


int mLevelOneFlood[28][17] = {

	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,1,1,1,1,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,1,2,2,2,2,2,2,2,2,2},
	{ 2,0,1,2,2,1,1,1,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,1,2,2,2,2,2,2,2,2,2},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,2,2,2,0,2,2,2,0,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2}


};

int mLevelTwoFlood[56][23] = {

	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};

FloodGrid::FloodGrid() {

	mInput = InputManager::Instance();

	mStageNumber = NULL;

	mFloodGrid = nullptr;
	mRows = NULL;
	mColumns = NULL;

	mFloodHorizontal = Graphics::Instance()->SCREEN_WIDTH * 0.98;
	mFloodVertical = Graphics::Instance()->SCREEN_HEIGHT * 0.72;

	mAnimatedFloodTiles[0] = new AnimatedTexture("floodleveloneanimation.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);
	mAnimatedFloodTiles[1] = new AnimatedTexture("floodleveltwoanimation.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);
	mAnimatedFloodTiles[2] = new AnimatedTexture("floodlevelthreeanimation.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);

	mFloodText = new Texture("Flood Level", "unispace.ttf", 14, { 72, 31, 228 });

	mChangeFloodSelect = false;
	mFloodSelect = false;
	mFloodValue = NULL;

}

FloodGrid::~FloodGrid() {

	for (int row = 0; row < mRows; row++)
	{
		for (int column = 0; column < mColumns; column++)
		{
			mFloodGrid[row][column] = NULL;
		}
	}

	for (int i = 0; i < 2; ++i) {
		delete mAnimatedFloodTiles[i];
	}

	mStageNumber = NULL;
	mRows = NULL;
	mColumns = NULL;

	mFloodHorizontal = NULL;
	mFloodVertical = NULL;

	mFloodText = NULL;

	mChangeFloodSelect = NULL;
	mFloodSelect = NULL;
	mFloodValue = NULL;


}

int FloodGrid::GetValuesFloodGrid(int row, int column, int stageNumber) {

	switch (stageNumber)
	{
	case 0:
		break;

	case 1:

		return  mLevelOneFlood[row][column];
		break;

	case 2:

		return  mLevelTwoFlood[row][column];
		break;

	default:
		break;
	}

}

void FloodGrid::LoadInitialFloodGrid(int stageNumber, int** floodGrid) {

	mStageNumber = stageNumber;

	// Deallocate previous memory if it was allocated
	if (mFloodGrid != nullptr) {
		for (int i = 0; i < mRows; ++i) {
			delete[] mFloodGrid[i];
		}
		delete[] mFloodGrid;
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

	// Allocate memory for mFloodGrid
	mFloodGrid = new int* [mRows];
	for (int i = 0; i < mRows; ++i) {
		mFloodGrid[i] = new int[mColumns];
	}

	// Copy floodGrid values to mFloodGrid
	for (int row = 0; row < mRows; ++row) {
		for (int col = 0; col < mColumns; ++col) {
			mFloodGrid[row][col] = floodGrid[row][col];
		}
	}

}

void FloodGrid::LoadFloodGrid(int** floodGrid) {

	for (int row = 0; row < mRows; row++)
	{
		for (int column = 0; column < mColumns; column++)
		{
			mFloodGrid[row][column] = floodGrid[row][column];
		}
	}
}

void FloodGrid::DrawFloodGrid() {

	for (int row = 0; row < mRows; row++) {

		for (int column = 0; column < mColumns; column++) {

			int floodType = mFloodGrid[row][column];

			mAnimatedFloodTiles[floodType]->Pos(Vector2((mFloodHorizontal)-(68.0f * row), ((mFloodVertical)-(68.0f * column))));
			mAnimatedFloodTiles[floodType]->Scale(Vector2(2.0f, 2.0f));
			mAnimatedFloodTiles[floodType]->Render();


		}

	}

}

void FloodGrid::HandleFloodSelect() {

	// If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {
		// Get mouse position

		int x, y;
		SDL_GetMouseState(&x, &y);
		mFloodSelect = false;

		// Loop through the flood grid
		for (int row = 0; row < mRows; row++) {
			for (int column = 0; column < mColumns; column++) {

				if (mFloodSelect == true) {
					break;
				}

				if (x < 840 && x > 640 && y < 883 && y > 720) {
					break;
				}

				int horizontal = row * 68;
				int vertical = column * 68;

				//Check if mouse is in button
				bool inside = true;

				if (x < mFloodHorizontal - FLOOD_SELECT_WIDTH - horizontal || x > mFloodHorizontal + FLOOD_SELECT_WIDTH - horizontal || y < mFloodVertical - FLOOD_SELECT_HEIGHT - vertical || y > mFloodVertical + FLOOD_SELECT_HEIGHT - vertical)
					inside = false;

				if (inside == true) {

					//Mouse is inside tile, change select variable to True; change loop break variable (mTileselect) to True 
					mChangeFloodSelect = true;
					mFloodSelect = true;


					int floodValue = mFloodGrid[row][column];
					mFloodValue = floodValue;

					mFloodText->Pos(Vector2(785, 865));;
			

				}
				else {
					// Mouse click is not inside the current tile
					mChangeFloodSelect = false;

				}
			}
		}
	}
}

void FloodGrid::DrawFloodInterface() {

	if (mChangeFloodSelect == true) {

		mFloodText->Render();
		//mFloodInterfaceTexture[0]->Render();

	}

}

void FloodGrid::Update(int** floodGrid) {

	HandleFloodSelect();
	LoadFloodGrid(floodGrid);
	//mAnimatedTile->Update();

	for (int i = 0; i < 3; ++i) {
		mAnimatedFloodTiles[i]->Update();
	}

}

void FloodGrid::Render() {

	DrawFloodGrid();
	DrawFloodInterface();
}
