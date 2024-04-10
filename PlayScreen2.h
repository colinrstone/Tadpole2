#ifndef PlayScreen_h
#define PlayScreen_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"

#include "Camera.h"
#include "Level.h"
#include "CharacterSpawn.h"
#include "TriggerManager.h"

using namespace QuickSDL;

class PlayScreen : public GameEntity {

	
private:
	
	
	//Timer* mTimer;
	//InputManager* mInput;
	//AudioManager* mAudio;

	float mGameTimer;
	float mGameTimerInterval;

	float mFPSTimer;
	float mAverageFPS;

	Texture* mFPSText;
	
	Level* mLevel;

	CharacterSpawn* mCharacterSpawn;

	TriggerManager* mTriggerManager;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mLevelStarted;

	Camera* mCamera;
	Vector2 mCameraOffset;


	
private:
	

	
public:
	
	PlayScreen();
	~PlayScreen();
	
	//void StartNextLevel();

	void StartNewGame();
	void ChangeLevel(Level::ZONE newZone);

	bool GameOver();

	bool StartBattle();
	bool PlayIntroCutscene();
	bool PlayCutscene();

	void HandleZoneTransition(Level::ZONE newZone);
	
	void Update();
	void Render();
	
	
};

#endif /* PlayScreen_h */
