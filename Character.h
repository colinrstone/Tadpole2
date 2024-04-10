#ifndef Character_h
#define Character_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "Player.h"
#include "Dialogue.h"
#include "Response.h"



using namespace QuickSDL;

class Player;

class Character : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;

	int mCharacterValue;

	AnimatedTexture* mCharacter;
	AnimatedTexture* mCharacterIdle;
	AnimatedTexture* mCharacterSpeak;

	float mCharacterSpeakTimer;
	float mCharacterSpeakTimerInterval;
	bool mCharacterIsSpeak;
	Vector2 mCharacterPosition;
	float mCharacterRange;

	std::vector<std::string> mCharacterDialogue;
	bool mIsSpeaking;
	std::string mCharacterDialogueString;
	std::vector<std::string> mCharacterResponses;



	int mCharacterHealth;

	float mScrollSpeed;

private:


public:

	Character(int characternumber);
	//~Character();
	virtual ~Character() = default;

	int GetCharacterValue();
	Vector2 GetPosition() const;
	float GetInteractRange() const;
	std::vector<std::string> GetDialogue(int zoneValue, int characterValue, int characterOrder, int textboxProgress);
	std::vector<std::string> GetResponses(int zoneValue, int characterValue, int characterOrder, int textboxProgress);


	void PlayAttackAnimation();
	//void PerformAttack();

	void HandleCharacterShift();
	//void HandleCharacterAttack();
	void HandleInteraction();

	//virtual std::pair<int, int> TedSpecificFunction() = 0;

	void PrintDialogue(std::vector<std::string> dialogue);
	bool IsSpeaking() const;

	void StartBattle();
	void TakeDamage();

	void Update();
	void Render();


};





#endif /* Character_h */
