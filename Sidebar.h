#ifndef SideBar_h
#define SideBar_h

#include "ScoreBoard.h"
#include "AudioManager.h"
#include "GameEntity2.h"

class SideBar : public GameEntity {

private:


	//Timer* mTimer;
	AudioManager* mAudio;


	Texture* mBottomBackground;
	Texture* mTopBackground;

	//Texture* mHighLabel;
	//Texture* mScoreLabel;



private:

	


public:

	SideBar();
	~SideBar();

	void Update();
	void Render();



};




#endif /* SideBar_h */
