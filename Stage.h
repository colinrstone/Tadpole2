#ifndef Stage_h
#define Stage_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"


using namespace QuickSDL;

class Stage : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;






private:



public:

	Stage();
	~Stage();

	void SetBattleEnemies();

	void Update();
	void Render();


};





#endif /* Stage_h */
