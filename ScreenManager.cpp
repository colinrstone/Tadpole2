#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {

	if (sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;

}

void ScreenManager::Release() {

	delete sInstance;
	sInstance = NULL;


}

ScreenManager::ScreenManager() {

	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mCutsceneScreen = new CutsceneScreen();
	mTownScreen = new TownScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {

	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;

	delete mCutsceneScreen;
	mCutsceneScreen = NULL;

	delete mTownScreen;
	mTownScreen = NULL;
}


void ScreenManager::Update() {

	switch (mCurrentScreen) {

	case start:

		
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

			mCurrentScreen = play;
			mStartScreen->ResetAnimation();

			//Character creation?
			
			//Opening Cutscne??


			//New TownScreen start
			mTownScreen->StartNewTown();

			//The old playscreen start
			//mPlayScreen->StartNewGame();

		}
		break;

	case play:



		//mPlayScreen->Update();
		mTownScreen->Update();
		if (mPlayScreen->GameOver()) {

			mCurrentScreen = start;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {

			mCurrentScreen = start;
		}

		if (mPlayScreen->PlayCutscene()) {

			mCurrentScreen = cutscene;
		}
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

			mCurrentScreen = battle;
		}
		break;



	case cutscene:

		mCutsceneScreen->Update();

		//if statement for when cutscene timer is up and a cutscene end function is executed, will trigger this if statement
			//after triggered will go back to either playscreen or battle depending on parameter

		break;

		                                                                                         
	case battle:

		mTownScreen->Update();

		//if statement for when combat variables are expended and a battle end function is executed, will trigger this if statement
			//after triggered will go back to either playscreen or battle depending on parameter

		break;

	}

}

void ScreenManager::Render() {

	

	switch (mCurrentScreen) {

	case start:

		
		mStartScreen->Render();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

			mCurrentScreen = play;
			mStartScreen->ResetAnimation();
		}
		break;

	case play:

		//mPlayScreen->Render();
		mTownScreen->Render();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {

			mCurrentScreen = start;
			
		}
		break;

	case battle:


		mPlayScreen->Render();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

			mCurrentScreen = battle;

		}
		break;
	
	}



}
