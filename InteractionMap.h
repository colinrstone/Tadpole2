#ifndef InteractionMap_h
#define InteractionMap_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
//#include "PlayLevelData.h"

//#include "GameEntity2.h"
//#include "PlaySideBar.h"
//#include "Player.h"
//#include "Unit.h"
//#include "PlayLevel.h"
//#include "UnitDisplay.h"

#include "Scoreboard.h"
#include "RainEffect.h"
#include "Car.h"

#include "PowerMap.h"
#include "SewageMap.h"

#include <iostream>
#include <cctype>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;

using namespace QuickSDL;

class InteractionMap : public GameEntity {

public:

	enum LEVEL_STATES { running, finished, gameover };
	
	
	
private:


	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	LEVEL_STATES mCurrentState;

	//LevelData* mPlayLevelData;

	Texture* mStageOneBackground;


	//Timers
	float mStageTimer;

	float mCarSpawnTimer;
	float mCarSpawnTimerInterval;

	float mHouseSpawnTimer;
	float mHouseSpawnTimerInterval;

	float mRainSpawnTimer;
	float mRainSpawnTimerInterval;

	float mFloodTimer;
	float mFloodTimerInterval;

	float mDrainTimer;
	float mDrainTimerInterval;

	float mWaterMovementTimer;
	float mWaterMovementTimerInterval;

	float mGameOverTimer;
	float mGameOverDelay;

	//TEST
	Texture* mTestText1;
	Texture* mTestText2;


	//PLAYER LOSES
	bool mHouseFloodedLose;
	Texture* mGameOverLabel;
	float mGameOverLabelOnScreen;


	//Money
	Texture* mFundingText;
	Texture* mDollarSignInterface;
	int mDollarValue;
	Scoreboard* mDollarInterface;


	//Tile Variables
	int mTileHorizontal;
	int mTileVertical;

	bool mChangeTileSelect;
	bool mTileSelect;

	Texture* mTileText;


	Texture* mWaterText;
	Texture* mDirtText;
	Texture* mGrassText;
	Texture* mStreetText;

	Texture* mTileInterfaceTexture;

	Texture* mWaterInterfaceTexture;
	Texture* mDirtInterfaceTexture;
	Texture* mGrassInterfaceTexture;
	Texture* mStreetInterfaceTexture;


	Texture* mTileHighlight;
	bool mTileHighlightOn;



	//Tile Map
	int mTileMap[26][17];

	//Elevation Contour Map
	int mContourMap[26][17];

	//Car Map
	int mCarMap[26][17];
	
	//Structure Map
	int mStructureMap[26][17];


	//Position of Unit
	int mUnitMap[26][17];

	//Position of Unit Value
	int mUnitValueMap[26][17];

	//Position of Pipe; Type of Pipe
	int mPipeMap[26][17];

	//Sewage Facility Map
	SewageMap* mSewageMap;

	//Power Map
	PowerMap* mPowerMap;

	//Flood Value Map
	int mFloodValueMap[26][17];

	//Contaminant Value Map
	int mContaminantValueMap[26][17];

	//Charge Value Map
	int mChargeValueMap[26][17];

	//Movement Check Map
	int mValueMovementMap[26][17];




	Texture* mUtilityManInterface;
	AnimatedTexture* mAnimatedUtilityManInterface;
	//AnimatedTexture* mCar;
	AnimatedTexture* mCarSideways;



	//Car
	Car* mCar;
	Car* mCarTwo;
	int mLitterRow;
	int mLitterColumn;
	int mLitterRowTwo;
	int mLitterColumnTwo;
	bool mCarSpawned;
	float mDropTime;
	float mDropTimeTwo;

	Texture* mLitter;
	Texture* mTrashCan;

	//Condition for random spawn on same tile
	bool mUnitNotPlaced;
	bool mRainNotPlaced;
	bool mFloodNotDrained;



	//Da Rain
	RainEffect* mRaindrops;
	RainEffect* mRaindropsTwo;
	int mRainInitialX;
	int mRainInitialY;
	int mRainPositionX;
	int mRainPositionY;
	int mRainTwoPositionX;
	int mRainTwoPositionY;
	bool mIsRaining;
	bool mFloodReduce;
	AnimatedTexture* mFloodLevelOne;
	AnimatedTexture* mFloodLevelTwo;
	AnimatedTexture* mFloodLevelThree;
	AnimatedTexture* mFloodLevelOneAnimation;
	AnimatedTexture* mFloodLevelTwoAnimation;
	AnimatedTexture* mFloodLevelThreeAnimation;



	//Texture for each flood value and label
	Texture* mFloodLabelText;
	Scoreboard* mFloodValue;


	//Texture for each contaminant value and label
	Texture* mContaminantLabelText;
	Scoreboard* mContaminantValue;



	//Textures for Contour Maps
	Texture* mContour;
	bool mCliffTileCheck;

	Texture* mElevationOneLeft;
	Texture* mElevationOneRight;
	Texture* mElevationOneTop;
	Texture* mElevationOneBottom;
	Texture* mElevationOneLeftTopCorner;
	Texture* mElevationOneLeftBottomCorner;
	Texture* mElevationOneRightTopCorner;
	Texture* mElevationOneRightBottomCorner;
	Texture* mElevationOneUShapeLeft;
	Texture* mElevationOneUShapeRight;
	Texture* mElevationOneUShapeTop;
	Texture* mElevationOneUShapeBottom;
	Texture* mElevationOneVerticalTunnel;
	Texture* mElevationOneHorizontalTunnel;
	Texture* mElevationOneSquare;




	//Structure Textures
	Texture* mStructure;

	Texture* mHouse;



	
	//Structure interface trigger and possible textures/texts/subtexts
	Texture* mStructureInterface;
	bool mStructureInterfaceOn;

	Texture* mWaterTreatmentInterface;
	Texture* mHouseInterface;


	Texture* mStructureText;
	Texture* mWaterTreatmentText;
	Texture* mHouseText;
	Texture* mDrainagePipeText;

	Texture* mStructureSubText;


	//Loop breaker for after selection change is true
	bool mChangeStructureSelect;


	bool mStructureMenuMouseOver;
	bool mStructureMenuSelect;




	//Coordinates for the origins of the boundaries of Unit Menu selection boxes
	SDL_Point mPosition;
	SDL_Point mUnitMenuMovementPosition;
	SDL_Point mUnitMenuActionPosition;
	SDL_Point mUnitMenuItemPosition;
	SDL_Point mUnitMenuStatusPosition;





	//Action indication variables
	Texture* mActionIndicator;
	Texture* mActionTrue;
	Texture* mActionFalse;



	//Structure menu and possible items to select
	int mStructureMenuTotal;
	Texture* mStructureMenuBackground;
	Texture* mStructureMenuBackgroundHighlight;
	Texture* mStructureMenuBackgroundSelect;

	//Movement
	Texture* mStructureMenuMovementBackground;
	Texture* mStructureMenuMovementBackgroundHighlight;
	Texture* mStructureMenuMovementBackgroundSelect;
	bool mChangeStructureMenuMovementMouseOver;
	bool mChangeStructureMenuMovementSelect;

	//Action
	Texture* mStructureMenuActionBackground;
	Texture* mStructureMenuActionBackgroundHighlight;
	Texture* mStructureMenuActionBackgroundSelect;
	bool mChangeStructureMenuActionMouseOver;
	bool mChangeStructureMenuActionSelect;

	//Item
	Texture* mStructureMenuItemBackground;
	Texture* mStructureMenuItemBackgroundHighlight;
	Texture* mStructureMenuItemBackgroundSelect;
	bool mChangeStructureMenuItemMouseOver;
	bool mChangeStructureMenuItemSelect;

	//Status
	Texture* mStructureMenuStatusBackground;
	Texture* mStructureMenuStatusBackgroundHighlight;
	Texture* mStructureMenuStatusBackgroundSelect;
	bool mChangeStructureMenuStatusMouseOver;
	bool mChangeStructureMenuStatusSelect;

    //Text for each kind of unit
	Texture* mStructureMenuMovementText;
	Texture* mStructureMenuActionText;
	Texture* mStructureMenuItemText;
	Texture* mStructureMenuStatusText;

	//Position to be moved by Movement
	int mStructurePositionValue;
	bool mStructurePositionSelect;
	int mStructurePositionSelectX;
	int mStructurePositionSelectY;
	int mStructurePositionTargetX;
	int mStructurePositionTargetY;

	//Position to be acted by Action
	int mStructureActionSelectValue;
	int mStructureActionTargetValue;
	bool mStructureActionSelect;
	int mStructureActionSelectX;
	int mStructureActionSelectY;
	int mStructureActionTargetX;
	int mStructureActionTargetY;




	//SHOP ITEMS, PIPES

	//Texture for each type of shop item
	Texture* mPipe;

	Texture* mWaterTreatmentPlant;



	//Background imamge for all stores
	Texture* mPipeShopBackground;


	//PIPE SELECTION
	Texture* mDrainageInterface;
	Texture* mDrainageText;
	Texture* mDrainageMenuSellText;
	Texture* mDrainageMenuToggleText;
	bool mChangeDrainageSelect;

	int mDrainagePositionSelectX;
	int mDrainagePositionSelectY;

	Texture* mDrainagePipeInterface;






	//Pipe Menu
	 
	 
	//Coordinates for the origins of the boundaries of Pipe Menu selection boxes
	SDL_Point mPipeMenuPosition;


	bool mPipeMenuMouseOver;
	bool mPipeMenuSelect;

	Texture* mPipeMenuBackground;
	Texture* mPipeMenuBackgroundHighlight;
	Texture* mPipeMenuBackgroundSelect;

	Texture* mPipeMenuText;


	//Vertical Pipe directed Up

	Texture* mDrainagePipeVUp;
	Texture* mDrainagePipeVUpFlood;
	Texture* mDrainagePipeVUpNONSelect;
	Texture* mDrainagePipeVUpMouseOver;
	Texture* mDrainagePipeVUpSelect;

	//Vertical Pipe directed Down
	Texture* mDrainagePipeVDown;
	Texture* mDrainagePipeVDownFlood;
	Texture* mDrainagePipeVDownNONSelect;
	Texture* mDrainagePipeVDownMouseOver;
	Texture* mDrainagePipeVDownSelect;


	Texture* mDrainagePipeHLeft;
	Texture* mDrainagePipeHLeftFlood;
	Texture* mDrainagePipeHLeftNONSelect;
	Texture* mDrainagePipeHLeftMouseOver;
	Texture* mDrainagePipeHLeftSelect;


	Texture* mDrainagePipeHRight;
	Texture* mDrainagePipeHRightFlood;
	Texture* mDrainagePipeHRightNONSelect;
	Texture* mDrainagePipeHRightMouseOver;
	Texture* mDrainagePipeHRightSelect;

	Texture* mDrainagePipeCROneRight;
	Texture* mDrainagePipeCROneRightFlood;
	Texture* mDrainagePipeCROneRightNONSelect;
	Texture* mDrainagePipeCROneRightMouseOver;
	Texture* mDrainagePipeCROneRightSelect;
	Texture* mDrainagePipeCROneDown;
	Texture* mDrainagePipeCROneDownFlood;
	Texture* mDrainagePipeCROneDownNONSelect;
	Texture* mDrainagePipeCROneDownMouseOver;
	Texture* mDrainagePipeCROneDownSelect;

	Texture* mDrainagePipeCRTwoLeft;
	Texture* mDrainagePipeCRTwoLeftFlood;
	Texture* mDrainagePipeCRTwoLeftNONSelect;
	Texture* mDrainagePipeCRTwoLeftMouseOver;
	Texture* mDrainagePipeCRTwoLeftSelect;
	Texture* mDrainagePipeCRTwoDown;
	Texture* mDrainagePipeCRTwoDownFlood;
	Texture* mDrainagePipeCRTwoDownNONSelect;
	Texture* mDrainagePipeCRTwoDownMouseOver;
	Texture* mDrainagePipeCRTwoDownSelect;

	Texture* mDrainagePipeCRThreeLeft;
	Texture* mDrainagePipeCRThreeLeftFlood;
	Texture* mDrainagePipeCRThreeLeftNONSelect;
	Texture* mDrainagePipeCRThreeLeftMouseOver;
	Texture* mDrainagePipeCRThreeLeftSelect;
	Texture* mDrainagePipeCRThreeUp;
	Texture* mDrainagePipeCRThreeUpFlood;
	Texture* mDrainagePipeCRThreeUpNONSelect;
	Texture* mDrainagePipeCRThreeUpMouseOver;
	Texture* mDrainagePipeCRThreeUpSelect;

	Texture* mDrainagePipeCRFourRight;
	Texture* mDrainagePipeCRFourRightFlood;
	Texture* mDrainagePipeCRFourRightNONSelect;
	Texture* mDrainagePipeCRFourRightMouseOver;
	Texture* mDrainagePipeCRFourRightSelect;
	Texture* mDrainagePipeCRFourUp;
	Texture* mDrainagePipeCRFourUpFlood;
	Texture* mDrainagePipeCRFourUpNONSelect;
	Texture* mDrainagePipeCRFourUpMouseOver;
	Texture* mDrainagePipeCRFourUpSelect;

	Texture* mDrainagePipeTOneRight;
	Texture* mDrainagePipeTOneRightFlood;
	Texture* mDrainagePipeTOneRightNONSelect;
	Texture* mDrainagePipeTOneRightMouseOver;
	Texture* mDrainagePipeTOneRightSelect;
	Texture* mDrainagePipeTOneDown;
	Texture* mDrainagePipeTOneDownFlood;
	Texture* mDrainagePipeTOneDownNONSelect;
	Texture* mDrainagePipeTOneDownMouseOver;
	Texture* mDrainagePipeTOneDownSelect;
	Texture* mDrainagePipeTOneLeft;
	Texture* mDrainagePipeTOneLeftFlood;
	Texture* mDrainagePipeTOneLeftNONSelect;
	Texture* mDrainagePipeTOneLeftMouseOver;
	Texture* mDrainagePipeTOneLeftSelect;

	Texture* mDrainagePipeTTwoUp;
	Texture* mDrainagePipeTTwoUpFlood;
	Texture* mDrainagePipeTTwoUpNONSelect;
	Texture* mDrainagePipeTTwoUpMouseOver;
	Texture* mDrainagePipeTTwoUpSelect;
	Texture* mDrainagePipeTTwoDown;
	Texture* mDrainagePipeTTwoDownFlood;
	Texture* mDrainagePipeTTwoDownNONSelect;
	Texture* mDrainagePipeTTwoDownMouseOver;
	Texture* mDrainagePipeTTwoDownSelect;
	Texture* mDrainagePipeTTwoLeft;
	Texture* mDrainagePipeTTwoLeftFlood;
	Texture* mDrainagePipeTTwoLeftNONSelect;
	Texture* mDrainagePipeTTwoLeftMouseOver;
	Texture* mDrainagePipeTTwoLeftSelect;

	Texture* mDrainagePipeTThreeUp;
	Texture* mDrainagePipeTThreeUpFlood;
	Texture* mDrainagePipeTThreeUpNONSelect;
	Texture* mDrainagePipeTThreeUpMouseOver;
	Texture* mDrainagePipeTThreeUpSelect;
	Texture* mDrainagePipeTThreeDown;
	Texture* mDrainagePipeTThreeDownFlood;
	Texture* mDrainagePipeTThreeDownNONSelect;
	Texture* mDrainagePipeTThreeDownMouseOver;
	Texture* mDrainagePipeTThreeDownSelect;
	Texture* mDrainagePipeTThreeRight;
	Texture* mDrainagePipeTThreeRightFlood;
	Texture* mDrainagePipeTThreeRightNONSelect;
	Texture* mDrainagePipeTThreeRightMouseOver;
	Texture* mDrainagePipeTThreeRightSelect;

	Texture* mDrainagePipeTFourUp;
	Texture* mDrainagePipeTFourUpFlood;
	Texture* mDrainagePipeTFourUpNONSelect;
	Texture* mDrainagePipeTFourUpMouseOver;
	Texture* mDrainagePipeTFourUpSelect;
	Texture* mDrainagePipeTFourLeft;
	Texture* mDrainagePipeTFourLeftFlood;
	Texture* mDrainagePipeTFourLeftNONSelect;
	Texture* mDrainagePipeTFourLeftMouseOver;
	Texture* mDrainagePipeTFourLeftSelect;
	Texture* mDrainagePipeTFourRight;
	Texture* mDrainagePipeTFourRightFlood;
	Texture* mDrainagePipeTFourRightNONSelect;
	Texture* mDrainagePipeTFourRightMouseOver;
	Texture* mDrainagePipeTFourRightSelect;

	Texture* mDrainagePipeSquareUp;
	Texture* mDrainagePipeSquareUpFlood;
	Texture* mDrainagePipeSquareUpNONSelect;
	Texture* mDrainagePipeSquareUpMouseOver;
	Texture* mDrainagePipeSquareUpSelect;

	Texture* mDrainagePipeSquareLeft;
	Texture* mDrainagePipeSquareLeftFlood;
	Texture* mDrainagePipeSquareLeftNONSelect;
	Texture* mDrainagePipeSquareLeftMouseOver;
	Texture* mDrainagePipeSquareLeftSelect;

	Texture* mDrainagePipeSquareDown;
	Texture* mDrainagePipeSquareDownFlood;
	Texture* mDrainagePipeSquareDownNONSelect;
	Texture* mDrainagePipeSquareDownMouseOver;
	Texture* mDrainagePipeSquareDownSelect;

	Texture* mDrainagePipeSquareRight;
	Texture* mDrainagePipeSquareRightFlood;
	Texture* mDrainagePipeSquareRightNONSelect;
	Texture* mDrainagePipeSquareRightMouseOver;
	Texture* mDrainagePipeSquareRightSelect;

	//Pipe Shop Coordinates
	SDL_Point mDrainagePipeVUpPosition;
	SDL_Point mDrainagePipeVDownPosition;

	SDL_Point mDrainagePipeHRightPosition;
	SDL_Point mDrainagePipeHLeftPosition;

	SDL_Point mDrainagePipeCROneDownPosition;
	SDL_Point mDrainagePipeCROneRightPosition;

	SDL_Point mDrainagePipeCRTwoDownPosition;
	SDL_Point mDrainagePipeCRTwoLeftPosition;

	SDL_Point mDrainagePipeCRThreeUpPosition;
	SDL_Point mDrainagePipeCRThreeLeftPosition;

	SDL_Point mDrainagePipeCRFourUpPosition;
	SDL_Point mDrainagePipeCRFourRightPosition;

	SDL_Point mDrainagePipeTOneDownPosition;
	SDL_Point mDrainagePipeTOneLeftPosition;
	SDL_Point mDrainagePipeTOneRightPosition;

	SDL_Point mDrainagePipeTTwoDownPosition;
	SDL_Point mDrainagePipeTTwoLeftPosition;
	SDL_Point mDrainagePipeTTwoUpPosition;

	SDL_Point mDrainagePipeTThreeUpPosition;
	SDL_Point mDrainagePipeTThreeDownPosition;
	SDL_Point mDrainagePipeTThreeRightPosition;

	SDL_Point mDrainagePipeTFourUpPosition;
	SDL_Point mDrainagePipeTFourLeftPosition;
	SDL_Point mDrainagePipeTFourRightPosition;

	SDL_Point mDrainagePipeSquareUpPosition;
	SDL_Point mDrainagePipeSquareDownPosition;
	SDL_Point mDrainagePipeSquareLeftPosition;
	SDL_Point mDrainagePipeSquareRightPosition;


	bool mChangeDrainagePipeVUpMouseOver;
	bool mChangeDrainagePipeVUpSelect;
	bool mChangeDrainagePipeVDownMouseOver;
	bool mChangeDrainagePipeVDownSelect;

	bool mChangeDrainagePipeHRightMouseOver;
	bool mChangeDrainagePipeHRightSelect;
	bool mChangeDrainagePipeHLeftMouseOver;
	bool mChangeDrainagePipeHLeftSelect;

	bool mChangeDrainagePipeCROneDownMouseOver;
	bool mChangeDrainagePipeCROneDownSelect;
	bool mChangeDrainagePipeCROneRightMouseOver;
	bool mChangeDrainagePipeCROneRightSelect;

	bool mChangeDrainagePipeCRTwoDownMouseOver;
	bool mChangeDrainagePipeCRTwoDownSelect;
	bool mChangeDrainagePipeCRTwoLeftMouseOver;
	bool mChangeDrainagePipeCRTwoLeftSelect;

	bool mChangeDrainagePipeCRThreeUpMouseOver;
	bool mChangeDrainagePipeCRThreeUpSelect;
	bool mChangeDrainagePipeCRThreeLeftMouseOver;
	bool mChangeDrainagePipeCRThreeLeftSelect;

	bool mChangeDrainagePipeCRFourUpMouseOver;
	bool mChangeDrainagePipeCRFourUpSelect;
	bool mChangeDrainagePipeCRFourRightMouseOver;
	bool mChangeDrainagePipeCRFourRightSelect;

	bool mChangeDrainagePipeTOneDownMouseOver;
	bool mChangeDrainagePipeTOneDownSelect;
	bool mChangeDrainagePipeTOneRightMouseOver;
	bool mChangeDrainagePipeTOneRightSelect;
	bool mChangeDrainagePipeTOneLeftMouseOver;
	bool mChangeDrainagePipeTOneLeftSelect;

	bool mChangeDrainagePipeTTwoDownMouseOver;
	bool mChangeDrainagePipeTTwoDownSelect;
	bool mChangeDrainagePipeTTwoUpMouseOver;
	bool mChangeDrainagePipeTTwoUpSelect;
	bool mChangeDrainagePipeTTwoLeftMouseOver;
	bool mChangeDrainagePipeTTwoLeftSelect;

	bool mChangeDrainagePipeTThreeDownMouseOver;
	bool mChangeDrainagePipeTThreeDownSelect;
	bool mChangeDrainagePipeTThreeUpMouseOver;
	bool mChangeDrainagePipeTThreeUpSelect;
	bool mChangeDrainagePipeTThreeRightMouseOver;
	bool mChangeDrainagePipeTThreeRightSelect;


	bool mChangeDrainagePipeTFourUpMouseOver;
	bool mChangeDrainagePipeTFourUpSelect;
	bool mChangeDrainagePipeTFourLeftMouseOver;
	bool mChangeDrainagePipeTFourLeftSelect;
	bool mChangeDrainagePipeTFourRightMouseOver;
	bool mChangeDrainagePipeTFourRightSelect;


	bool mChangeDrainagePipeSquareUpMouseOver;
	bool mChangeDrainagePipeSquareUpSelect;
	bool mChangeDrainagePipeSquareDownMouseOver;
	bool mChangeDrainagePipeSquareDownSelect;
	bool mChangeDrainagePipeSquareLeftMouseOver;
	bool mChangeDrainagePipeSquareLeftSelect;
	bool mChangeDrainagePipeSquareRightMouseOver;
	bool mChangeDrainagePipeSquareRightSelect;






	//Contaminant Shop
	SDL_Point mContaminantMenuPosition;

	bool mContaminantMenuMouseOver;
	bool mContaminantMenuSelect;

	Texture* mContaminantMenuBackground;
	Texture* mContaminantMenuBackgroundHighlight;
	Texture* mContaminantMenuBackgroundSelect;


	//Texture for each type of shop item
	Texture* mSewage;

	Texture* mFilter;

	//Sewage Shop Coordinates
	SDL_Point mFilterPosition;

	bool mChangeFilterMouseOver;
	bool mChangeFilterSelect;

	Texture* mFilterMouseOver;
	Texture* mFilterSelect;
	Texture* mFilterNONSelect;






	//Power Shop

	SDL_Point mPowerMenuPosition;

	bool mPowerMenuMouseOver;
	bool mPowerMenuSelect;

	Texture* mPowerMenuBackground;
	Texture* mPowerMenuBackgroundHighlight;
	Texture* mPowerMenuBackgroundSelect;




	//Texture for each type of shop item
	Texture* mPower;

	Texture* mGenerator;




	//Sewage Shop Coordinates
	SDL_Point mGeneratorPosition;

	bool mChangeGeneratorMouseOver;
	bool mChangeGeneratorSelect;

	Texture* mGeneratorMouseOver;
	Texture* mGeneratorSelect;
	Texture* mGeneratorNONSelect;




private:

	//void HandleMovement();
	

public:

	InteractionMap(int tilemap[26][17], int contourmap[26][17], int carmap[26][17], int structureemap[26][17], int unitmap[26][17], int unitvaluemap[26][17], int pipemap[26][17], int sewagemap[26][17], int powermap[26][17], int floodvaluemap[26][17], int contaminantvaluemap[26][17], int chargevaluemap[26][17]);
	~InteractionMap();

	LEVEL_STATES State();

	//RNG
	int RandomVertical(void);
	int RandomHorizontal(void);
	int RandomCount(int count);
	int RandomFiftyFifty(void);


	//Handle automatically changing elements of the map
	void HandleHouseFloodLoss();
	void HandleRainSpawn();
	void HandleFloodValue();
	void HandleHouseSpawn();
	void HandleCarSpawn();
	//void HandleCarLitterSpawn();
	void HandleDrain();


	//Select Functions
	//void HandleSelect();
	void HandleTileSelect();
	void HandleMenuSelect(int x, int y);
	void HandlePipeSelect();
	void HandleStructureSelect();
	

	void HandlePipeMenuSelect();
	void HandlePipeShopSelect();

	void HandleContaminantMenuSelect();
	void HandleSewageShopSelect();

	void HandlePowerMenuSelect();
	void HandlePowerShopSelect();

	//Changes to the Map
	void HandlePipePlacement();
	void HandleMovement();
	void HandleAction();


	//Loading preset maps
	void LoadTileMap(int arr[26][17]);
	void LoadContourMap(int arr[26][17]);
	void LoadCarMap(int arr[26][17]);
	void LoadStructureMap(int arr[26][17]);
	void LoadUnitMap(int arr[26][17]);
	void LoadUnitValueMap(int arr[26][17]);

	void LoadPipeMap(int arr[26][17]);
	void LoadSewageMap(int arr[26][17]);
	void LoadPowerMap(int arr[26][17]);

	void LoadFloodValueMap(int arr[26][17]);
	void LoadContaminantValueMap(int arr[26][17]);
	void LoadChargeValueMap(int arr[26][17]);

	//Map for checking tiles that items have already been moved to
	void LoadValueMovementMap();


	//Drawing sprite textures of map elements
	void DrawContourMap();
	void DrawStructureMap();

	void DrawPipeMap();
	void DrawSewageMap();
	void DrawPowerMap();

	void DrawContaminantMap();


	//Drawing visuals for players to choose interactions
	void DrawMovementTiles();
	void DrawActionTiles();
	

	void Update();
	void Render();


};






#endif /* InteractionMap_h */
