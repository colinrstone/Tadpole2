#include "TownScreen.h"

TownScreen::TownScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mTown = NULL;
	mStageNumber = 1;
	mSideBar = NULL;

}

TownScreen::~TownScreen() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;


	mTown = NULL;
	mStageNumber = NULL;
	mSideBar = NULL;

}


void TownScreen::StartNewTown() {

	//Needs to be dynamic to include which stage you are on in campaign

	//Put in function that interchanges stage number
	//mTown = new Town(mStageNumber);

	// if mStageNumber does not exist use 1, other wise use stage number
	
	mStageNumber = 1;

	//Load Town object
	mTown = new Town();
	mTown->LoadInitialGrids(mStageNumber);

	//Load Sidebar object
	mSideBar = new SideBar();
}


void TownScreen::Update() {

	mSideBar->Update();
	mTown->Update();


}


void TownScreen::Render() {

	mSideBar->Render();
	mTown->Render();



}
