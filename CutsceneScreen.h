#ifndef CutsceneScreen_h
#define CutsceneScreen_h
#include "AnimatedTexture.h"
#include "InputManager.h"





using namespace QuickSDL;

class CutsceneScreen : public GameEntity {


private:
	Timer* mTimer;
	InputManager* mInput;

	//Screen animation variables

	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;






public:

	CutsceneScreen();
	~CutsceneScreen();




	void Update();
	void Render();

};





#endif /* CutsceneScreen_h */
