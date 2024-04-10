#ifndef Player_h
#define Player_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Camera.h"

#include <algorithm>
#include <vector>
#include "Character.h"

//Idea men create pocket man? is controlled by a rogue idea man? they from a universe where they are just concepts not physical beings. just inventing communication and words. takes place in a vacuum of space in the greater universe somewhere, no matter just waves/energy?? enemies are energy swirls depicted by leafs or debris flying in circles??
// vacuum cleaner them up sometimes maybe towards the end stages, pocket man goes by some other greek like name also the antagonists call him, they are always inquisitive about the time of his date of birth. they end up revealing that they are a part of a doom prophecy the reverse of a chosen one or messiah like prophet
// the prophet is the controller rogue one and his dooming of their world reciprocates in a subatomic particle forming.

//can fill interface of 3-9 bags up with letters which can be combined into items, some items are junk or just picked up


using namespace QuickSDL;

class Enemy;

class Player : public GameEntity {
	
private:
	
	
	Timer* mTimer;
	InputManager* mInput;
	//AudioManager* mAudio;
	
	Vector2 mPlayerPosition;


	Texture* mPlayerIdle;
	Texture* mPlayerIdleUp;
	Texture* mPlayerIdleDown;
	Texture* mPlayerIdleLeft;
	Texture* mPlayerIdleRight;
	
	bool mIsAnimating;
	AnimatedTexture* mPlayerAnimate;

	AnimatedTexture* mPlayerRunUp;
	AnimatedTexture* mPlayerRunDown;
	AnimatedTexture* mPlayerRunLeft;
	AnimatedTexture* mPlayerRunRight;


	AnimatedTexture* mPlayerJump;
	float mJumpTimer;
	float mJumpTimerInterval;

	bool mIsInteracting;
	AnimatedTexture* mPlayerInteract;
	AnimatedTexture* mPlayerInteractUp;
	AnimatedTexture* mPlayerInteractDown;
	AnimatedTexture* mPlayerInteractLeft;
	AnimatedTexture* mPlayerInteractRight;
	float mInteractionTimer;
	float mInteractionTimerInterval;
	float mInteractionRange;
	std::vector<Enemy*> mEnemiesInRange; // Collection of enemies in range


	float mSetIdleDelayTimer;
	float mSetIdleDelayTimerInterval;


	float mMoveSpeed;
	Vector2 mMoveLowerBounds;
	Vector2 mMoveUpperBounds;

	bool mVisible;

	int mScore;
	int mLives;

	
private:
	
	void HandleMovement();
	void HandleJump();
	void HandleInteract();

public:
	
	Player();
	~Player();

	static Player& Instance();



	
	void Visible(bool visible);

	int Score();
	int Lives();
	
	void AddScore(int change);

	Vector2 GetPosition() const;
	float GetInteractionRange() const;
	
	void SetPlayerIdle();

	// Set the position of the object in the game world
	//void SetPlayerPosition(float x, float y);
	//void SetPlayerPosition(const Vector2& position);

	void Update();
	void Render();
	
	
};






#endif /* Player_h */
