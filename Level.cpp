#include "Level.h"

Level::Level(Level::ZONE zone, ZoneCallback callback, TriggerManager* triggerManager) :
	gameState(0, 100, 0), // Initialize game state (zone, health, gold, etc.)
	conversationState(0, 0) // Initialize conversation state (zone, characterValue)
 {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mExitTimer = 0.0f;
	mExitTimerInterval = 1.0f;

	mPlayerIdleDelayTimer = 0.0f;
	mPlayerIdleDelayTimerInterval = 0.02f;

	mCurrentZone = zone;
	SetZoneTransitionCallback(callback);

	mTextbox = NULL;
	mSelectedMenuItem = 0;
	mTextboxInput = NULL; 
	mWaitForPlayerInput = NULL; 

	mTriggerManager = triggerManager;
	mEventManager = new EventManager();








	switch (mCurrentZone) {
	case ZONE::OUTSIDE:

		mCamera = NULL;
		mCameraOffset = VEC2_ZERO;

		mZoneIdentifier = 1;

		mPlayer = new Player();
		mPlayer->Parent(this);
		mPlayer->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH / 2), (Graphics::Instance()->SCREEN_HEIGHT / 2)));


		mTerrain = new Terrain(mZoneIdentifier);
		mTerrain->Parent(this);
		mTerrain->Pos(Vector2(960.0f, 540.0f));
		
		
		//mTriggerManager->AddTrigger(std::make_tuple(1,1,1,1), 1);	

		break;
	case ZONE::BUILDING_ONE:

		mCamera = NULL;
		mCameraOffset = VEC2_ZERO;	

		mZoneIdentifier = 2;

		mPlayer = new Player();
		mPlayer->Parent(this);
		mPlayer->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH / 2), (Graphics::Instance()->SCREEN_HEIGHT / 2)));


		mTerrain = new Terrain(mZoneIdentifier);
		mTerrain->Parent(this);
		mTerrain->Pos(Vector2(960.0f, 540.0f));	


		break;
	case ZONE::BUILDING_TWO:

		break;

	}

}

Level::~Level() {


	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	mZoneIdentifier = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mTerrain;
	mTerrain = NULL;

	delete mCamera;
	mCameraOffset = NULL;

	delete mTextbox;
	mTextbox = NULL;
	mSelectedMenuItem = NULL;


}

Vector2 Level::GetCameraOffset(Vector2 cameraposition) {

	//Takes in a new camera position as input, returns offsets necessary to move player and other objects away from this point

	//Set new camera position
	Camera camera;
	camera.SetCameraPosition(cameraposition);

	//Get the offset
	Vector2 offset = camera.GetOffset();

	return offset;

}

void Level::UpdateCameraPosition() {

	//mCameraOffset.x--;
	//mCameraOffset.y--;

	mPlayer->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH / 2), (Graphics::Instance()->SCREEN_HEIGHT / 2)) + mCameraOffset);
	mTerrain->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH * 9 / 10), (Graphics::Instance()->SCREEN_HEIGHT * 7 / 10)) + mCameraOffset);

}

void Level::SetCharacters(std::vector<Character*> characters) {

	mAllCharacters = characters;

}
Level::ZONE Level::GetCurrentZone() const {

	return mCurrentZone;
}

void Level::SetZoneTransitionCallback(ZoneCallback callback) {
	mZoneTransitionCallback = callback;
}

std::vector<Vector2>& Level::GetZoneExitPositions(Level::ZONE zone) {
	mExitPositions.clear();

	switch (zone) {
	case ZONE::OUTSIDE:
		mExitPositions.push_back(Vector2(758, 408));
		break;
	case ZONE::BUILDING_ONE:
		mExitPositions.push_back(Vector2(952, 466));
		break;
	case ZONE::BUILDING_TWO:
		break;
	}

	return mExitPositions;
}

void Level::HandleExitCheck() {

	// Get the player's current position from Player.cpp
	Vector2 playerPosition = mPlayer->GetPosition();

	// Get the exit positions for the current zone
	ZONE currentZone = GetCurrentZone();
	mExitPositions = GetZoneExitPositions(mCurrentZone);

	// Determine the new zone based on the current zone and player's position
	ZONE newZone = mCurrentZone; // Default to the current zone
	printf("Player Position: (%f, %f)\n", playerPosition.x, playerPosition.y);


	for (const Vector2& exitPosition : mExitPositions) {
		printf("Exit Position: (%f, %f)\n", exitPosition.x, exitPosition.y);

		// Using a tolerance value for position matching
		if (CalculateDistance(playerPosition, exitPosition) < 7.0f) {
			printf("Match found: Player (%.2f, %.2f) == Exit (%.2f, %.2f)\n",
				playerPosition.x, playerPosition.y,
				exitPosition.x, exitPosition.y);

			// Determine the new zone based on the exit position
			if (currentZone == ZONE::OUTSIDE) {
				//if (exitPosition == Vector2(100, 200)) {
					newZone = ZONE::BUILDING_ONE;
					//mZoneTransitionCallback(newZone);
				//}
				//else if (exitPosition == Vector2(200, 300)) {
					//newZone = ZONE::BUILDING_TWO;
				//}
			}
			else if (currentZone == ZONE::BUILDING_ONE) {
				// Define transitions for BUILDING_ONE exits;
				newZone = ZONE::OUTSIDE;
			}
			else if (currentZone == ZONE::BUILDING_TWO) {
				// Define transitions for BUILDING_TWO exits
			}

			// Exit the loop if a valid exit is found
			if (newZone != currentZone) {
				break;
			}
		}
	}

	// Zone transition
	if (mZoneTransitionCallback && newZone != currentZone) {
		mZoneTransitionCallback(newZone);
	}
}


float Level::CalculateDistance(const Vector2& position1, const Vector2& position2) {
	// Calculate the Euclidean distance between two positions
	return sqrt(pow(position2.x - position1.x, 2) + pow(position2.y - position1.y, 2));
}

bool Level::CheckRange(Player* player, Character* character) {

	// Calculate the distance between theW player and the character
	float distance = CalculateDistance(player->GetPosition(), character->GetPosition());

	float interactionRange = player->GetInteractionRange();

	// Check if the player is within the attack range of the character
	if (distance <= interactionRange) {
		// Perform other actions here
		return true;
	}

	return false;

}

int Level::SelectedMenuItem() {

	return mSelectedMenuItem;
}

void Level::ChangeMenuItem(int change) {

	mSelectedMenuItem += change;

	if (mSelectedMenuItem < 1)
		mSelectedMenuItem = 1;
	else if (mSelectedMenuItem > 1)
		mSelectedMenuItem = 0;

}

void Level::HandleCharacterInteract() {
	// Detect and add characters in range
	for (Character* character : mAllCharacters) {
		if (CheckRange(mPlayer, character)) {
			mInRangeCharacters.push_back(character);
		}
	}

	for (Character* characterInRange : mInRangeCharacters) {
		characterInRange->HandleInteraction();

		if (characterInRange->IsSpeaking()) {

			mCurrentCharacter = characterInRange;
			mCharacterValue = mCurrentCharacter->GetCharacterValue();



			// DYNAMIC TRIGGER BASED ORDER FETCH
			std::pair<int, int> pair = CheckCurrentCharacter(characterInRange); //see which character it is and apply a specific trigger check to get character order number, also get max textbox number

			int newCharacterOrderValue = pair.first;
			int newMaxTextboxValue = pair.second;

			// DYNAMIC NUMBER OF THE LAST TEXTBOX / TOTAL TEXTBOXES
			if (newCharacterOrderValue)
				mCharacterOrder = newCharacterOrderValue;
			else
				mCharacterOrder = 1;


			if (newMaxTextboxValue)
				mCharacterMaxTextbox = newMaxTextboxValue;
			else
				mCharacterMaxTextbox = 2; //Default is 2 which is 1 textbox up from the default 1 mTextboxProgress value


			//CURRENT TEXTBOX
			mTextboxProgress = 1; // Initialize mTextboxProgress to 0 or 1

			//printf("%i \n", mZoneIdentifier);
			//printf("%i \n", mCharacterValue);
			//printf("%i \n", mCharacterOrder);
			//printf("%i \n \n \n", mTextboxProgress);

			// Initialize the conversation here
			InitializeConversation(mZoneIdentifier, mCharacterValue, mCharacterOrder);
		}

		mInRangeCharacters.clear();
	}
}

void Level::InitializeConversation(int zoneValue, int characterValue, int characterOrder) {

	// Fetch initial dialogue and responses
	std::vector<std::string> dialogue = mCurrentCharacter->GetDialogue(zoneValue, characterValue, characterOrder, mTextboxProgress);
	mResponses = mCurrentCharacter->GetResponses(zoneValue, characterValue, characterOrder, mTextboxProgress);

	// Create the textbox only once
	mTextbox = new Textbox();
	mTextbox->SetBackground();
	mTextbox->SetDialogueText(dialogue, "unispace.ttf", 12, { 150, 0, 0 });

	if (!mResponses.empty()) {
		mTextbox->SetResponseTexts(mResponses, "unispace.ttf", 10, { 150, 0, 0 });

		// Menu Item value change with arrow keys
		mSelectedMenuItem = 0;
	}

	// Wait for player input in the game's update loop
	mWaitForPlayerInput = true;
}

std::pair<int, int> Level::CheckCurrentCharacter(Character* characterInRange) {
	//int mCharacterOrder = 0;
	//int mCharacterMaxTextbox = 0;

	//Use function triggermanager


	// Check if the current character is TedTheGuy

	TedTheGuy* ted = dynamic_cast<TedTheGuy*>(characterInRange);
	if (ted != nullptr) {
		// This is TedTheGuy, you can use TedTheGuy-specific functions
		ted->SetTriggerManager(mTriggerManager);
		std::pair<int, int> tedValues = ted->TedSpecificFunction(mZoneIdentifier, mCharacterValue, mCharacterOrder, mTextboxProgress, mSelectedMenuItem);

		// Assign values to member variables
		mCharacterOrder = tedValues.first;
		mCharacterMaxTextbox = tedValues.second;
	}
	// Add checks for other character types as needed

	//printf("%i \n", mCharacterOrder);
	//printf("%i \n", mCharacterMaxTextbox);

	return std::make_pair(mCharacterOrder, mCharacterMaxTextbox);
}




void Level::Update() {


	// Handle waiting for player input
	if (mWaitForPlayerInput) {

		

		//Set player idle
		mPlayerIdleDelayTimer += mTimer->DeltaTime();
		if (mPlayerIdleDelayTimer > mPlayerIdleDelayTimerInterval) {

			mPlayer->SetPlayerIdle();
			mPlayerIdleDelayTimer = 0.0f;

		}

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
			ChangeMenuItem(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP))
			ChangeMenuItem(-1);

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

			//printf("%i \n \n \n", mSelectedMenuItem);
			mTriggerManager->AddTrigger(std::make_tuple(mZoneIdentifier, mCharacterValue, mCharacterOrder, mTextboxProgress), mSelectedMenuItem);
			//mTriggerManager->AddTrigger(std::make_tuple(1,1,1,1), 1);


			mTextboxProgress++; // Advance the conversation
			mWaitForPlayerInput = false;

			// Check if the conversation has ended
			if (mTextboxProgress >= mCharacterMaxTextbox) {
				// The conversation has ended, clean up the textbox
				delete mTextbox;
				mTextbox = nullptr;
				mResponses.clear();
				mTextboxProgress = 1;
				mCharacterOrder = 1;
				// You can perform any other necessary actions when the conversation ends.
			}
			else {
				//Check triggers again
				//std::pair<int, int> pair = CheckCurrentCharacter(mCurrentCharacter);

			 
				//need if statement to check if a trigger pair exists or not or just keep going with current convo
				//
				//
				//
				//
				//
				//
				
				//int newCharacterOrderValue = pair.first;
				//int newMaxTextboxValue = pair.second;
				// Continue the conversation
				//InitializeConversation(mZoneIdentifier, mCharacterValue, newCharacterOrderValue);
				InitializeConversation(mZoneIdentifier, mCharacterValue, mCharacterOrder);
			}
		}
	}

	if (!mResponses.empty()) {

		if (mTextbox)
			mTextbox->Update();
	}




	if (!mWaitForPlayerInput) {

		mPlayer->Update();


		if (mTerrain) {

			mTerrain->Update();

		}



		for (Character* character : mAllCharacters) {


			character->Update();

		}



		if (mInput->KeyDown(SDL_SCANCODE_SPACE)) {

			HandleCharacterInteract();

		}



		mExitTimer += mTimer->DeltaTime();

		if (mExitTimer >= mExitTimerInterval) {

			HandleExitCheck();
			mExitTimer = 0.0f;


		}


	}
	 

}


void Level::Render() {

	if (mTerrain) {

		mTerrain->Render();

	}



	for (Character* character : mAllCharacters) {

		character->Render();

	}

	mPlayer->Render();

	if (mTextbox)
		mTextbox->Render();


}
