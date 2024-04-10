#ifndef Car_h
#define Car_h

#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"
#include "GameEntity2.h"
#include "AnimatedTexture.h"
//#include "InteractionMap.h"

#include <iostream>
#include <cctype>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;


class Car : public GameEntity {

private:


	static Car* sInstance;

	Timer* mTimer;
	AudioManager* mAudio;

	int mCarValue;
	int mCarRow;
	int mCarColumn;

	AnimatedTexture* mCarDown;
	AnimatedTexture* mCarUp;
	AnimatedTexture* mCarLeft;
	AnimatedTexture* mCarRight;

	bool mCarMovingUp;
	bool mCarMovingDown;
	bool mCarMovingLeft;
	bool mCarMovingRight;

	bool mCarSpawned;

	//int mStartingPointsX[10];
	//int mStartingPointsY[10];
	
	SDL_Point mCarPosition;

	bool mVisible;
	//bool mAnimating;

	float mMoveSpeed;
	Vector2 mMoveBounds;



public:

	AnimatedTexture* mCar;


private:





public:



	static Car* Instance(int value, int row, int column);
	static void Release();


	Car(int value, int row, int column);
	~Car();

	void SpawnCar();
	void HandleCarMovement();


	void Update();
	void Render();



};














#endif /* PlaySideBar_h */