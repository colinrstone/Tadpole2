#ifndef ScreenManager_h
#define ScreenManager_h
#include "StartScreen2.h"
#include "PlayScreen2.h"
#include "CutsceneScreen.h"
#include "TownScreen.h"


class ScreenManager {


	private:

		enum SCREENS { start, play, battle, cutscene };

		static ScreenManager* sInstance;

		InputManager* mInput;

		StartScreen* mStartScreen;
		PlayScreen* mPlayScreen;
		CutsceneScreen* mCutsceneScreen;
		TownScreen* mTownScreen;

		SCREENS mCurrentScreen;



	public:


		static ScreenManager* Instance();
		static void Release();

		void Update();
		void Render();


	private:

		ScreenManager();
		~ScreenManager();



};




#endif /* ScreenManager2_h */

