#include "Town.h"


Town::Town() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	//Initialize the background imagery
	mStageBackground = NULL;
	
	//Load Tile Terrains
	mTileMap = NULL;

	//Arrays that hold values of grids
	//mTerrainValues = NULL;
	mTerrainGrid = NULL;
	mFloodGrid = NULL;

	mRainEffect = NULL;
	mCar = NULL;
}

Town::~Town() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	mStageBackground = NULL;
	mTileMap = NULL;

	mTerrainGrid = NULL;
	mFloodGrid = NULL;

	mRainEffect = NULL;
	mCar = NULL;
}

Town::LEVEL_STATES Town::State() {

	return mCurrentState;

}

int Town::RandomVertical(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 15);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomHorizontal(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 24);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomCount(int count) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, (count - 1));

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomFiftyFifty(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 1);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

void Town::LoadInitialValues(int stageNumber) {

	//Allocate memory for size of grid
	switch (stageNumber)
	{
	case 0:
		break;
	case 1:
		mTileRows = 28;
		mTileColumns = 17;

		mTerrainValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mTerrainValues[i] = new int[mTileColumns];
		}

		mFloodValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mFloodValues[i] = new int[mTileColumns];
		}
		break;
	case 2:
		mTileRows = 56;
		mTileColumns = 23;

		mTerrainValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mTerrainValues[i] = new int[mTileColumns];
		}

		mFloodValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mFloodValues[i] = new int[mTileColumns];
		}
		break;
	default:
		break;
	}

	//Begin retreiving values
	for (int row = 0; row < mTileRows; row++)
	{
		for (int column = 0; column < mTileColumns; column++)
		{
			mTerrainValues[row][column] = mTerrainGrid->GetValuesTerrainGrid(row, column, stageNumber);
			mFloodValues[row][column] = mFloodGrid->GetValuesFloodGrid(row, column, stageNumber);

		}
	}



}

void Town::LoadInitialGrids(int stageNumber) {

	//create new
	mTerrainGrid = new TerrainGrid();
	mFloodGrid = new FloodGrid();

	//need a function that sets mTerrainValue to the static variable on top of TerrainGrid.cpp
	LoadInitialValues(stageNumber);

	//Functions that take stage number and gather intital grid values
	mTerrainGrid->LoadInitialTerrainGrid(stageNumber, mTerrainValues);
	mFloodGrid->LoadInitialFloodGrid(stageNumber, mFloodValues);
}

void Town::LoadGrids() {
	 
	//Functions that pass new values of grids to be updated by their containers
	mTerrainGrid->Update(mTerrainValues);
	mFloodGrid->Update(mFloodValues);
}

void Town::DrawGrids() {

	//mTerrainGrid->DrawTerrainGrid();
	mTerrainGrid->Render();
	mFloodGrid->Render();
}


void Town::Update() {

	//Timers


	//Loss conditions



	//Animations
	//character, dynamic tiles (floodwater)
	

	//Handle timing based events that check timers
	
	//Check and handle if the player selects the range of selections he can perform at a given time


	//Check and handle if a player is placing an object from menu or using a move or action command on the board


	//Reload the grids with new information adjusted
	LoadGrids();
	//mCar->Update();



}

void Town::Render() {

	DrawGrids();
	//mCar->Render();

}

