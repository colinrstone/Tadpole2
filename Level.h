#ifndef Level_h
#define Level_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"

#include "Player.h"
#include "Terrain.h"
#include "Camera.h"
#include "Textbox.h"
#include "TriggerManager.h"
#include "EventManager.h"
#include "GameState.h"
#include "ConversationState.h"
#include "TedTheGuy.h"




#include <functional>

using namespace QuickSDL;

class CharacterSpawn;

class Level : public GameEntity {

public:

	enum ZONE { OUTSIDE, BUILDING_ONE, BUILDING_TWO };

	// Define a callback function type
	using ZoneCallback = std::function<void(Level::ZONE)>;



private:


	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Camera* mCamera;
	Vector2 mCameraOffset;

	int mZoneIdentifier;

	Player* mPlayer;
	Terrain* mTerrain;
	CharacterSpawn* mCharacterSpawn;
	std::vector<Character*> mAllCharacters;
	std::vector<Character*> mInRangeCharacters;
	TriggerManager* mTriggerManager;
	EventManager* mEventManager;
	GameState gameState;
	ConversationState conversationState;

	Character* mCurrentCharacter;
	Textbox* mTextbox;
	int mSelectedMenuItem;
	bool mTextboxInput;
	bool mWaitForPlayerInput;
	int mTextboxProgress;

	int mCharacterValue;
	int mCharacterOrder;
	int mCharacterMaxTextbox;

	float mPlayerIdleDelayTimer;
	float mPlayerIdleDelayTimerInterval;

	std::vector<std::string> mDialogue;
	std::vector<std::string> mResponses;


	std::vector<Vector2> mExitPositions;
	float mExitTimer;
	float mExitTimerInterval;
	
	ZoneCallback mZoneTransitionCallback;
	ZONE mCurrentZone;


	bool mShouldStartCombat;



public:

	Level(Level::ZONE zone, std::function<void(Level::ZONE)> zoneTransitionCallback, TriggerManager* triggerManager);
	~Level();

	Vector2 GetCameraOffset(Vector2 cameraposition);
	void UpdateCameraPosition();

	void SetCharacters(std::vector<Character*> characters);
	
	//ZONE GetCurrentZone() const { return mCurrentZone; }
	Level::ZONE GetCurrentZone() const;
	std::pair<int, int> CheckCurrentCharacter(Character* characterInRange);

	// Set the callback function
	void SetZoneTransitionCallback(ZoneCallback callback);
	std::vector<Vector2>& GetZoneExitPositions(Level::ZONE zone);

	//Update function
	void HandleExitCheck();



	float CalculateDistance(const Vector2& position1, const Vector2& position2);
	bool CheckRange(Player* player, Character* character);
	void HandleCharacterInteract();
	void InitializeConversation(int zoneValue, int characterValue, int characterOrder);
	int SelectedMenuItem();
	void ChangeMenuItem(int change);

	void ModifyImpassableAreas();




	void Update();
	void Render();


};

#endif /* Level_h */
