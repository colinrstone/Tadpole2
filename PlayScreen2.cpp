#include "PlayScreen2.h"

PlayScreen::PlayScreen() {
	
	//mTimer = Timer::Instance();
	//mInput = InputManager::Instance();
	//mAudio = AudioManager::Instance();

	mGameTimer = 0.0f;
	mGameTimerInterval = 5.0f;

	mLevel = nullptr;
	//mLevel->SetZoneTransitionCallback(std::bind(&PlayScreen::HandleZoneTransition, this, std::placeholders::_1));
	mCharacterSpawn = NULL;

	mCamera = NULL;
	mCameraOffset = VEC2_ZERO;

}

PlayScreen::~PlayScreen() {
	
	//mTimer = NULL;
	//mInput = NULL;
	

	mGameTimer = NULL;
	mGameTimerInterval = NULL;
	
	delete mLevel;
	mLevel = NULL;
	delete mTriggerManager;

	delete mCamera;
    mCameraOffset = NULL;
}

//THIS WILL PROBABLY BE CHANGED TO "ENTER TILESTAGE"
void PlayScreen::StartNewGame() {

	//NEW GAME, FIRST CUTSCENE THEN FIRST LEVEL

	//FIRST CUTSCENE GOES HERE


	//FIRST LEVEL

	//Create stage of OUTSIDE
	mTriggerManager = new TriggerManager();

	mLevel = new Level(Level::ZONE::OUTSIDE, [this](Level::ZONE newZone) {
		HandleZoneTransition(newZone);
		}, mTriggerManager);

	//Characters for stage
	mCharacterSpawn = new CharacterSpawn();
	mCharacterSpawn->LoadCharactersForZone(mLevel, Level::ZONE::OUTSIDE);

	//Play BGM
	//mAudio->PlayMusic("gamestart.wav", 0);
	
}

void PlayScreen::HandleZoneTransition(Level::ZONE newZone) {

	// Clean up the current level if needed
	if (mLevel) {
		delete mLevel;
		mLevel = nullptr;
	}

	// Create a lambda function that will handle the zone transition
	std::function<void(Level::ZONE)> zoneTransitionCallback = [&](Level::ZONE zone) {
		HandleZoneTransition(zone); // Call HandleZoneTransition recursively with the new zone
	};

	// Create a new level with the specified zone and callback
	mLevel = new Level(newZone, zoneTransitionCallback, mTriggerManager);

	//Characters for stage
	delete mCharacterSpawn;
	mCharacterSpawn = new CharacterSpawn();
	mCharacterSpawn->LoadCharactersForZone(mLevel, newZone);


}


bool PlayScreen::GameOver() {

	//if(!mLevelStarted)
		//return false;

	//return (mCurrentLevel->State() == Level::gameover);

	return 0;
}


bool PlayScreen::StartBattle() {

	return 0;
}


bool PlayScreen::PlayIntroCutscene() {

	//if(!mLevelStarted)
		//return false;

	//return (mCurrentLevel->State() == Level::gameover);

	return 0;
}



bool PlayScreen::PlayCutscene() {

	//if(!mLevelStarted)
		//return false;

	//return (mCurrentLevel->State() == Level::gameover);

	return 0;
}



void PlayScreen::Update() {
	
	//if (mLevel->HandleCharacterInteract())
	if (mLevel) {

		mLevel->Update();
	}


	//if (mBattleTrigger)
	//  StartBattle();

}


void PlayScreen::Render() {

	if (mLevel) {

		mLevel->Render();

	}

}
