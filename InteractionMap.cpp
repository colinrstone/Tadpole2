#include "InteractionMap.h"

//Selection box constants
const int SELECT_WIDTH = 16;
const int SELECT_HEIGHT = 16;

//Tile selection box constants
const int TILE_SELECT_WIDTH = 16;
const int TILE_SELECT_HEIGHT = 16;

//Structure Menu selection box constants
const int UNIT_MENU_SELECT_WIDTH = 64;
const int UNIT_MENU_SELECT_HEIGHT = 16;

//Pipe Menu selection box constants
const int PIPE_MENU_SELECT_WIDTH = 16;
const int PIPE_MENU_SELECT_HEIGHT = 16;

//Pipe Menu selection box constants
const int PIPE_SHOP_SELECT_WIDTH = 16;
const int PIPE_SHOP_SELECT_HEIGHT = 16;




InteractionMap::InteractionMap(int tilemap[26][17], int contourmap[26][17], int carmap[26][17], int structureemap[26][17], int unitmap[26][17], int unitvaluemap[26][17], int pipemap[26][17], int sewagemap[26][17], int powermap[26][17], int floodvaluemap[26][17], int contaminantvaluemap[26][17], int chargevaluemap[26][17]) {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();


	LoadTileMap(tilemap);
	LoadContourMap(contourmap);
	LoadCarMap(carmap);
	LoadStructureMap(structureemap);

	LoadPipeMap(pipemap);


	mPowerMap = new PowerMap();
	mSewageMap = new SewageMap();


	LoadFloodValueMap(unitvaluemap);
	LoadContaminantValueMap(contaminantvaluemap);



	
	 mCurrentState = running;






	
	//Timers and Spawn Timers
	mStageTimer = 0.0f;
	mCarSpawnTimer = 12.5f;
	mCarSpawnTimerInterval = 12.5f;
	mHouseSpawnTimer = 0.0f;
	mHouseSpawnTimerInterval = 60.0f;
	mRainSpawnTimer = 20.0f;
	mRainSpawnTimerInterval = 20.0f;
	mDrainTimer = 0.0f;
	mDrainTimerInterval = 5.0f;
	mWaterMovementTimer = 0.0f;
	mWaterMovementTimerInterval = 10.0f;


	mGameOverTimer = NULL;
	mGameOverDelay = 10.0f;
	mGameOverLabelOnScreen = 1.0f; 

	//TEST
	//mTestText1 = new Texture("$", "unispace.ttf", 10, { 0, 150, 0 });
	//mTestText1->Parent(this);
	//mTestText1->Pos(Vector2(105, 751));
	//mTestText2 = new Texture("$", "unispace.ttf", 10, { 0, 150, 0 });
	//mTestText2->Parent(this);
	//mTestText2->Pos(Vector2(309, 853));

	//Player Loses
	mHouseFloodedLose = false;

	mGameOverLabel = new Texture("GAME OVER", "unispace.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));




	//Money
	mFundingText = new Texture("Funding", "unispace.ttf", 14, { 150, 0, 0 });;
	mFundingText->Parent(this);
	mFundingText->Pos(Vector2(130, 15));


	mDollarSignInterface = new Texture("$", "unispace.ttf", 10, { 0, 150, 0 });;
	mDollarSignInterface->Parent(this);
	mDollarSignInterface->Pos(Vector2(100, 35));

	mDollarValue = 1000;

	mDollarInterface = new Scoreboard({ 0, 150, 0 });
	mDollarInterface->Parent(this);
	mDollarInterface->Pos(Vector2(130, 35));
	mDollarInterface->Scoreboard::Score(mDollarValue);

	//TILE VARIABLES
	mTileHorizontal = Graphics::Instance()->SCREEN_WIDTH * 9 / 10;
	mTileVertical = Graphics::Instance()->SCREEN_HEIGHT * 7 / 10;

	mChangeTileSelect = false;
	mTileSelect = false;


	//Tile Text
	mTileText = NULL;



	mWaterText = new Texture("Water", "unispace.ttf", 14, { 72, 31, 228 });
	mWaterText->Parent(this);
	mWaterText->Pos(Vector2(945, 715));

	mDirtText = new Texture("Dirt", "unispace.ttf", 14, { 72, 31, 228 });
	mDirtText->Parent(this);
	mDirtText->Pos(Vector2(945, 715));

	mGrassText = new Texture("Grass", "unispace.ttf", 12, { 72, 31, 228 });
	mGrassText->Parent(this);
	mGrassText->Pos(Vector2(945, 715));

	mStreetText = new Texture("Street", "unispace.ttf", 14, { 72, 31, 228 });
	mStreetText->Parent(this);
	mStreetText->Pos(Vector2(945, 715));;

	//Tile Interface Texture
	mTileInterfaceTexture = NULL;

	mWaterInterfaceTexture = new Texture("elevationoneleft.png");
	mWaterInterfaceTexture->Parent(this);
	mWaterInterfaceTexture->Pos(Vector2(945, 785));

	mDirtInterfaceTexture = new Texture("elevationoneleft.png");
	mDirtInterfaceTexture->Parent(this);
	mDirtInterfaceTexture->Pos(Vector2(945, 785));

	mGrassInterfaceTexture = new Texture("grassinterface.png");
	mGrassInterfaceTexture->Parent(this);
	mGrassInterfaceTexture->Pos(Vector2(945, 780));

	mStreetInterfaceTexture = new Texture("elevationoneleft.png");
	mStreetInterfaceTexture->Parent(this);
	mStreetInterfaceTexture->Pos(Vector2(945, 785));

	//Tile Highlight
	mTileHighlight = new Texture("tilehighlight.png");
	mTileHighlightOn = NULL;



	//TileMap
	int mTileMap[26][17] = {};
	int mContourMap[26][17] = {};
	int mCarMap[26][17] = {};
	int mStructureMap[26][17] = {};

	int mUnitMap[26][17] = {};
	int mUnitValueMap[26][17] = {};

	int mPipeMap[26][17] = {};


	int mFloodValueMap[26][17] = {};
	int mContaminantValueMap[26][17] = {};
	int mChargeValueMap[26][17] = {};

	int mValueMovementMap[26][17] = {};


	//END TILE VARIABLES



		
	//UTILITY MAN OR CHARACTER CHOSEN ANIMATION
	mAnimatedUtilityManInterface = new AnimatedTexture("utilitymaninterfacespritesheet.png", 0, 0, 32, 38, 7, 6, AnimatedTexture::horizontal);
	mAnimatedUtilityManInterface->Pos(Vector2(450, 760));
	mAnimatedUtilityManInterface->Scale(Vector2(2.0f, 2.0f));





	//PIPE AND MAP VARIABLES
	

	//Car
	mCar = NULL;
	mCarSpawned = false;
	mLitterRow = NULL;
	mLitterColumn = NULL;
	mDropTime = NULL;
	mDropTimeTwo = NULL;


	mLitter = NULL;

	mTrashCan = new Texture("trashcan.png");
	mTrashCan->Parent(this);



	//Condition for random spawn on same tile
	mUnitNotPlaced = NULL;
	mRainNotPlaced = NULL;
	mFloodNotDrained = NULL;


	//RAIN VARIABLES
	mRainPositionY = NULL;
	mRainPositionX = NULL;
	mRainTwoPositionY = NULL;
	mRainTwoPositionX = NULL;

	mRainInitialY = RandomVertical();
	mRainInitialX = RandomHorizontal();

	mRaindrops = RainEffect::Instance(NULL, NULL);
	mRaindrops->Scroll(false);
	//mRaindropsTwo = RainEffect::Instance(NULL, NULL);
	//mRaindrops->Scroll(false);

	//RainEffect::Release();
	//mIsRaining = true;
	mFloodReduce = NULL;
	mFloodLevelOne = NULL;
	mFloodLevelTwo = NULL;
	mFloodLevelThree = NULL;
	mFloodValue = NULL;
	mFloodLevelOneAnimation = new AnimatedTexture("floodleveloneanimation.png", 0, 0, 32, 32, 5, 2.5f, AnimatedTexture::horizontal);
	mFloodLevelOneAnimation->Parent(this);
	mFloodLevelTwoAnimation = new AnimatedTexture("floodleveltwoanimation.png", 0, 0, 32, 32, 5, 2.5f, AnimatedTexture::horizontal);
	mFloodLevelTwoAnimation->Parent(this);
	mFloodLevelThreeAnimation = new AnimatedTexture("floodlevelthreeanimation.png", 0, 0, 32, 32, 5, 2.5f, AnimatedTexture::horizontal);
	mFloodLevelThreeAnimation->Parent(this);

	//Texture for each flood value and label
	mFloodLabelText = NULL;
	mFloodValue = NULL;



	//Texture for each contaminant value and label
	mContaminantLabelText = NULL;
	mContaminantValue = NULL;


	//CONTOUR MAP TEXTURES
	mContour = NULL;
	mCliffTileCheck = NULL;
	
	mElevationOneLeft = new Texture("elevationoneleft.png");
	mElevationOneLeft->Parent(this);

	mElevationOneRight = new Texture("elevationoneright.png");
	mElevationOneRight->Parent(this);

	mElevationOneTop = new Texture("elevationonetop.png");
	mElevationOneTop->Parent(this);

	mElevationOneBottom = new Texture("elevationonebottom.png");
	mElevationOneBottom->Parent(this);

	mElevationOneLeftTopCorner = new Texture("elevationonelefttopcorner.png");
	mElevationOneLeftTopCorner->Parent(this);

	mElevationOneLeftBottomCorner = new Texture("elevationoneleftbottomcorner.png");
	mElevationOneLeftBottomCorner->Parent(this);

	mElevationOneRightTopCorner = new Texture("elevationonerighttopcorner.png");
	mElevationOneRightTopCorner->Parent(this);

	mElevationOneRightBottomCorner = new Texture("elevationonerightbottomcorner.png");
	mElevationOneRightBottomCorner->Parent(this);

	mElevationOneUShapeLeft = new Texture("elevationoneushapeleft.png");
	mElevationOneUShapeLeft->Parent(this);

	mElevationOneUShapeRight = new Texture("elevationoneushaperight.png");
	mElevationOneUShapeRight->Parent(this);

	mElevationOneUShapeTop = new Texture("elevationoneushapeup.png");
	mElevationOneUShapeTop->Parent(this);

	mElevationOneUShapeBottom = new Texture("elevationoneushapedown.png");
	mElevationOneUShapeBottom->Parent(this);

	mElevationOneVerticalTunnel = new Texture("elevationoneverticaltunnel.png");
	mElevationOneVerticalTunnel->Parent(this);

	mElevationOneHorizontalTunnel = new Texture("elevationonehorizontaltunnel.png");
	mElevationOneHorizontalTunnel->Parent(this);

	mElevationOneSquare = new Texture("elevationonesquare.png");
	mElevationOneSquare->Parent(this);





	//Structure Display Texts and Subtexts
	mStructureText = NULL;

	mHouseText = new Texture("House", "unispace.ttf", 12, { 72, 31, 228 });
	mHouseText->Parent(this);
	mHouseText->Pos(Vector2(785, 715));

	mWaterTreatmentText = new Texture("Water Treatment Plant", "unispace.ttf", 12, { 72, 31, 228 });
	mWaterTreatmentText->Parent(this);
	mWaterTreatmentText->Pos(Vector2(785, 715));



	mStructureSubText = NULL;

	mStructureInterface = new Texture("unitdisplay.png");
	mStructureInterface->Pos(Vector2(500, 720));
	mStructureInterfaceOn = NULL;



	mWaterTreatmentInterface = new Texture("watertreatmentplant.png");
	mWaterTreatmentInterface->Parent(this);
	mWaterTreatmentInterface->Scale(Vector2(2.0f, 2.0f));
	mWaterTreatmentInterface->Pos(Vector2(785, 785));

	mHouseInterface = new Texture("house.png");
	mHouseInterface->Parent(this);
	mHouseInterface->Pos(Vector2(785, 785));


	//Structure Textures
	mStructure = NULL;

	mHouse = new Texture("house.png");
	mHouse->Parent(this);


	/////////lOOP BREAKERS FOR AFTER A MATCHING COORDINATE IS FOUND AND SELECTION CHANGE IS TRUE
	mChangeStructureSelect = false;
	///////////////////////////////////////////////////////////////////////////////////////////


	//Structure menu and possible items to select

	mStructureMenuMouseOver = NULL;
	mStructureMenuSelect = NULL;


	mPosition.x = Graphics::Instance()->SCREEN_WIDTH * 9 / 10;
	mPosition.y = Graphics::Instance()->SCREEN_HEIGHT * 7 / 10;



	//Structure Menu Button Positions
	/*
	mStructureMenuMovementPosition.x = 735;
	mStructureMenuMovementPosition.y = 740;

	mStructureMenuActionPosition.x = 735;
	mStructureMenuActionPosition.y = 780;

	mStructureMenuItemPosition.x = 735;
	mStructureMenuItemPosition.y = 820;

	mStructureMenuStatusPosition.x = 735;

	mStructureMenuStatusPosition.y = 860;
     */


	//Textures for allowed actions after hitting menu button Action
	mActionIndicator = NULL;

	mActionTrue = new Texture("actiontrue.png");
	mActionTrue->Parent(this);


	mActionFalse = new Texture("actionfalse.png");
	mActionFalse->Parent(this);



	//UNIT MENU

	mStructurePositionValue = NULL;
	mStructurePositionSelect = NULL;
	mStructurePositionSelectX = NULL;
	mStructurePositionSelectY = NULL;
	mStructurePositionTargetX = NULL;
	mStructurePositionTargetY = NULL;

	mStructureActionSelectValue = NULL;
	mStructureActionTargetValue = NULL;
	mStructureActionSelect = NULL;
	mStructureActionSelectX = NULL;
	mStructureActionSelectY = NULL;
	mStructureActionTargetX = NULL;
	mStructureActionTargetY = NULL;

	mChangeStructureMenuMovementMouseOver = false;
	mChangeStructureMenuMovementSelect = false;

	mChangeStructureMenuActionMouseOver = false;
	mChangeStructureMenuActionSelect = false;

	mChangeStructureMenuItemMouseOver = false;
	mChangeStructureMenuItemSelect = false;

	mChangeStructureMenuStatusMouseOver = false;
	mChangeStructureMenuStatusSelect = false;

	mStructureMenuTotal = NULL;

	mStructureMenuMovementText = NULL;
	mStructureMenuActionText = NULL;
	mStructureMenuItemText = NULL;
	mStructureMenuStatusText = NULL;


	mStructureMenuBackground = new Texture("unitmenubackground.png");
	mStructureMenuBackground->Parent(this);
	mStructureMenuBackground->Pos(Vector2(735, 740));
	mStructureMenuBackground->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuBackgroundHighlight = new Texture("unitmenubackgroundhighlight.png");
	mStructureMenuBackgroundHighlight->Parent(this);
	mStructureMenuBackgroundHighlight->Pos(Vector2(735, 740));
	mStructureMenuBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuBackgroundSelect = new Texture("unitmenubackgroundselect.png");
	mStructureMenuBackgroundSelect->Parent(this);
	mStructureMenuBackgroundSelect->Pos(Vector2(735, 740));
	mStructureMenuBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//MOVEMENT
	mStructureMenuMovementBackground = new Texture("unitmenubackground.png");
	mStructureMenuMovementBackground->Parent(this);
	mStructureMenuMovementBackground->Pos(Vector2(735, 740));
	mStructureMenuMovementBackground->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuMovementBackgroundHighlight = new Texture("unitmenubackgroundhighlight.png");
	mStructureMenuMovementBackgroundHighlight->Parent(this);
	mStructureMenuMovementBackgroundHighlight->Pos(Vector2(735, 740));
	mStructureMenuMovementBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuMovementBackgroundSelect = new Texture("unitmenubackgroundselect.png");
	mStructureMenuMovementBackgroundSelect->Parent(this);
	mStructureMenuMovementBackgroundSelect->Pos(Vector2(735, 740));
	mStructureMenuMovementBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//ACTION
	mStructureMenuActionBackground = new Texture("unitmenubackground.png");
	mStructureMenuActionBackground->Parent(this);
	mStructureMenuActionBackground->Pos(Vector2(735, 780));
	mStructureMenuActionBackground->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuActionBackgroundHighlight = new Texture("unitmenubackgroundhighlight.png");
	mStructureMenuActionBackgroundHighlight->Parent(this);
	mStructureMenuActionBackgroundHighlight->Pos(Vector2(735, 780));
	mStructureMenuActionBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuActionBackgroundSelect = new Texture("unitmenubackgroundselect.png");
	mStructureMenuActionBackgroundSelect->Parent(this);
	mStructureMenuActionBackgroundSelect->Pos(Vector2(735, 780));
	mStructureMenuActionBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//ITEM
	mStructureMenuItemBackground = new Texture("unitmenubackground.png");
	mStructureMenuItemBackground->Parent(this);
	mStructureMenuItemBackground->Pos(Vector2(735, 820));
	mStructureMenuItemBackground->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuItemBackgroundHighlight = new Texture("unitmenubackgroundhighlight.png");
	mStructureMenuItemBackgroundHighlight->Parent(this);
	mStructureMenuItemBackgroundHighlight->Pos(Vector2(735, 820));
	mStructureMenuItemBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuItemBackgroundSelect = new Texture("unitmenubackgroundselect.png");
	mStructureMenuItemBackgroundSelect->Parent(this);
	mStructureMenuItemBackgroundSelect->Pos(Vector2(735, 820));
	mStructureMenuItemBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//STATUS
	mStructureMenuStatusBackground = new Texture("unitmenubackground.png");
	mStructureMenuStatusBackground->Parent(this);
	mStructureMenuStatusBackground->Pos(Vector2(735, 860));
	mStructureMenuStatusBackground->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuStatusBackgroundHighlight = new Texture("unitmenubackgroundhighlight.png");
	mStructureMenuStatusBackgroundHighlight->Parent(this);
	mStructureMenuStatusBackgroundHighlight->Pos(Vector2(735, 860));
	mStructureMenuStatusBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mStructureMenuStatusBackgroundSelect = new Texture("unitmenubackgroundselect.png");
	mStructureMenuStatusBackgroundSelect->Parent(this);
	mStructureMenuStatusBackgroundSelect->Pos(Vector2(735, 860));
	mStructureMenuStatusBackgroundSelect->Scale(Vector2(2.0f, 0.5f));





	//SHOP AND PIPES




	//PIPE TEXTURES

	//Pipe Position and Textures
	mPipe = NULL;

	mWaterTreatmentPlant = new Texture("watertreatmentplant.png");
	mWaterTreatmentPlant->Parent(this);



	//PIPE Display Texture
	mDrainagePipeInterface = new Texture("drainagepipehup.png");
	mDrainagePipeInterface->Parent(this);
	mDrainagePipeInterface->Pos(Vector2(105, 751));



	mDrainagePipeText = new Texture("Drainage Pipe", "unispace.ttf", 12, { 150, 0, 0 });
	mDrainagePipeText->Parent(this);
	mDrainagePipeText->Pos(Vector2(785, 720));








	mPipeShopBackground = new Texture("pipeshopbackground.png");
	mPipeShopBackground->Parent(this);
	mPipeShopBackground->Pos(Vector2(207, 802));



	//Pipe Shop
	mDrainageInterface = NULL;
	//mDrainageInterface->Parent(this);
	//DrainageInterface->Pos(Vector2(105, 751));

	mDrainageText = NULL;



	mDrainageMenuSellText = NULL;
	mDrainageMenuToggleText = NULL;


	mChangeDrainageSelect = NULL;

	mDrainagePositionSelectX = NULL;
	mDrainagePositionSelectY = NULL;


	



	//Pipe Menu Button Positions
	mPipeMenuPosition.x = 40;
	mPipeMenuPosition.y = 740;

	mPipeMenuMouseOver = NULL;
	mPipeMenuSelect = NULL;


	//VERTICAL PIPE
	mDrainagePipeVUp = new Texture("drainagepipevup.png");
	mDrainagePipeVUpFlood = new Texture("drainagepipevupflood.png");
	mDrainagePipeVUpNONSelect = new Texture("drainagepipevup.png");
	mDrainagePipeVUpNONSelect->Parent(this);
	mDrainagePipeVUpNONSelect->Pos(Vector2(105, 751));
	mDrainagePipeVUpMouseOver = new Texture("drainagepipevupmouseover.png");
	mDrainagePipeVUpMouseOver->Parent(this);
	mDrainagePipeVUpMouseOver->Pos(Vector2(105, 751));
	mDrainagePipeVUpSelect = new Texture("drainagepipevupselect.png");
	mDrainagePipeVUpSelect->Parent(this);
	mDrainagePipeVUpSelect->Pos(Vector2(105, 751));


	mDrainagePipeVDown = new Texture("drainagepipevdown.png");
	mDrainagePipeVDownFlood = new Texture("drainagepipevdownflood.png");
	mDrainagePipeVDownNONSelect = new Texture("drainagepipevdown.png");
	mDrainagePipeVDownNONSelect->Parent(this);
	mDrainagePipeVDownNONSelect-> Pos(Vector2(139, 751));
	mDrainagePipeVDownMouseOver = new Texture("drainagepipevdownmouseover.png");
	mDrainagePipeVDownMouseOver->Parent(this);
	mDrainagePipeVDownMouseOver->Pos(Vector2(139, 751));
	mDrainagePipeVDownSelect = new Texture("drainagepipevdownselect.png");
	mDrainagePipeVDownSelect->Parent(this);
	mDrainagePipeVDownSelect->Pos(Vector2(139, 751));



	//HORIZONTAL PIPE
	mDrainagePipeHRight = new Texture("drainagepipehright.png");
	mDrainagePipeHRightFlood = new Texture("drainagepipehrightflood.png");
	mDrainagePipeHRightNONSelect = new Texture("drainagepipehright.png");
	mDrainagePipeHRightNONSelect->Parent(this);
	mDrainagePipeHRightNONSelect->Pos(Vector2(173, 751));
	mDrainagePipeHRightMouseOver = new Texture("drainagepipehrightmouseover.png");
	mDrainagePipeHRightMouseOver->Parent(this);
	mDrainagePipeHRightMouseOver->Pos(Vector2(173, 751));
	mDrainagePipeHRightSelect = new Texture("drainagepipehrightselect.png");
	mDrainagePipeHRightSelect->Parent(this);
	mDrainagePipeHRightSelect->Pos(Vector2(173, 751));


	mDrainagePipeHLeft = new Texture("drainagepipehleft.png");
	mDrainagePipeHLeftFlood = new Texture("drainagepipehleftflood.png");
	mDrainagePipeHLeftNONSelect = new Texture("drainagepipehleft.png");
	mDrainagePipeHLeftNONSelect->Parent(this);
	mDrainagePipeHLeftNONSelect->Pos(Vector2(207, 751));
	mDrainagePipeHLeftMouseOver = new Texture("drainagepipehleftmouseover.png");
	mDrainagePipeHLeftMouseOver->Parent(this);
	mDrainagePipeHLeftMouseOver->Pos(Vector2(207, 751));
	mDrainagePipeHLeftSelect = new Texture("drainagepipehleftselect.png");
	mDrainagePipeHLeftSelect->Parent(this);
	mDrainagePipeHLeftSelect->Pos(Vector2(207, 751));



	 //CORNER ONE PIPE
     mDrainagePipeCROneDown = new Texture("drainagepipeCRonedown.png");
	 mDrainagePipeCROneDownFlood = new Texture("drainagepipeCRonedownflood.png");
	 mDrainagePipeCROneDownNONSelect = new Texture("drainagepipeCRonedownNONselect.png");
	 mDrainagePipeCROneDownNONSelect->Parent(this);
	 mDrainagePipeCROneDownNONSelect->Pos(Vector2(241, 751));
	 mDrainagePipeCROneDownMouseOver = new Texture("drainagepipeCRonedownmouseover.png");
	 mDrainagePipeCROneDownMouseOver->Parent(this);
	 mDrainagePipeCROneDownMouseOver->Pos(Vector2(241, 751));
	 mDrainagePipeCROneDownSelect = new Texture("drainagepipeCRonedownselect.png");
	 mDrainagePipeCROneDownSelect->Parent(this);
	 mDrainagePipeCROneDownSelect->Pos(Vector2(241, 751));


	 mDrainagePipeCROneRight = new Texture("drainagepipeCRoneright.png");
	 mDrainagePipeCROneRightFlood = new Texture("drainagepipeCRonerightflood.png");
	 mDrainagePipeCROneRightNONSelect = new Texture("drainagepipeCRonerightNONselect.png");
	 mDrainagePipeCROneRightNONSelect->Parent(this);
	 mDrainagePipeCROneRightNONSelect->Pos(Vector2(275, 751));
	 mDrainagePipeCROneRightMouseOver = new Texture("drainagepipeCRonerightmouseover.png");
	 mDrainagePipeCROneRightMouseOver->Parent(this);
	 mDrainagePipeCROneRightMouseOver->Pos(Vector2(275, 751));
	 mDrainagePipeCROneRightSelect = new Texture("drainagepipeCRonerightselect.png");
	 mDrainagePipeCROneRightSelect->Parent(this);
	 mDrainagePipeCROneRightSelect->Pos(Vector2(275, 751));




	 //CORNER TWO PIPE
	 mDrainagePipeCRTwoDown = new Texture("drainagepipeCRtwodown.png");
	 mDrainagePipeCRTwoDownFlood = new Texture("drainagepipeCRtwodownflood.png");
	 mDrainagePipeCRTwoDownNONSelect = new Texture("drainagepipeCRtwodownNONselect.png");
	 mDrainagePipeCRTwoDownNONSelect->Parent(this);
	 mDrainagePipeCRTwoDownNONSelect->Pos(Vector2(309, 751));
	 mDrainagePipeCRTwoDownMouseOver = new Texture("drainagepipeCRtwodownmouseover.png");
	 mDrainagePipeCRTwoDownMouseOver->Parent(this);
	 mDrainagePipeCRTwoDownMouseOver->Pos(Vector2(309, 751));
	 mDrainagePipeCRTwoDownSelect = new Texture("drainagepipeCRtwodownselect.png");
	 mDrainagePipeCRTwoDownSelect->Parent(this);
	 mDrainagePipeCRTwoDownSelect->Pos(Vector2(309, 751));

	 mDrainagePipeCRTwoLeft = new Texture("drainagepipeCRtwoleft.png");
	 mDrainagePipeCRTwoLeftFlood = new Texture("drainagepipeCRtwoleftflood.png");
	 mDrainagePipeCRTwoLeftNONSelect = new Texture("drainagepipeCRtwoleftNONselect.png");
	 mDrainagePipeCRTwoLeftNONSelect->Parent(this);
	 mDrainagePipeCRTwoLeftNONSelect->Pos(Vector2(105, 785));
	 mDrainagePipeCRTwoLeftMouseOver = new Texture("drainagepipeCRtwoleftmouseover.png");
	 mDrainagePipeCRTwoLeftMouseOver->Parent(this);
	 mDrainagePipeCRTwoLeftMouseOver->Pos(Vector2(105, 785));
	 mDrainagePipeCRTwoLeftSelect = new Texture("drainagepipeCRtwoleftselect.png");
	 mDrainagePipeCRTwoLeftSelect->Parent(this);
	 mDrainagePipeCRTwoLeftSelect->Pos(Vector2(105, 785));



	 //CORNER THREE PIPE
	 mDrainagePipeCRThreeUp = new Texture("drainagepipeCRthreeup.png");
	 mDrainagePipeCRThreeUpFlood = new Texture("drainagepipeCRthreeupflood.png");
	 mDrainagePipeCRThreeUpNONSelect = new Texture("drainagepipeCRthreeupNONselect.png");
	 mDrainagePipeCRThreeUpNONSelect->Parent(this);
	 mDrainagePipeCRThreeUpNONSelect->Pos(Vector2(139, 785));
	 mDrainagePipeCRThreeUpMouseOver = new Texture("drainagepipeCRthreeupmouseover.png");
	 mDrainagePipeCRThreeUpMouseOver->Parent(this);
	 mDrainagePipeCRThreeUpMouseOver->Pos(Vector2(139, 785));
	 mDrainagePipeCRThreeUpSelect = new Texture("drainagepipeCRthreeupselect.png");
	 mDrainagePipeCRThreeUpSelect->Parent(this);
	 mDrainagePipeCRThreeUpSelect->Pos(Vector2(139, 785));

	 mDrainagePipeCRThreeLeft = new Texture("drainagepipeCRthreeleft.png");
	 mDrainagePipeCRThreeLeftFlood = new Texture("drainagepipeCRthreeleftflood.png");
	 mDrainagePipeCRThreeLeftNONSelect = new Texture("drainagepipeCRthreeleftNONselect.png");
	 mDrainagePipeCRThreeLeftNONSelect->Parent(this);
	 mDrainagePipeCRThreeLeftNONSelect->Pos(Vector2(173, 785));
	 mDrainagePipeCRThreeLeftMouseOver = new Texture("drainagepipeCRthreeleftmouseover.png");
	 mDrainagePipeCRThreeLeftMouseOver->Parent(this);
	 mDrainagePipeCRThreeLeftMouseOver->Pos(Vector2(173, 785));
	 mDrainagePipeCRThreeLeftSelect = new Texture("drainagepipeCRthreeleftselect.png");
	 mDrainagePipeCRThreeLeftSelect->Parent(this);
	 mDrainagePipeCRThreeLeftSelect->Pos(Vector2(173, 785));



	//CORNER FOUR PIPE
	 mDrainagePipeCRFourUp = new Texture("drainagepipeCRfourup.png");
	 mDrainagePipeCRFourUpFlood = new Texture("drainagepipeCRfourupflood.png");
	 mDrainagePipeCRFourUpNONSelect = new Texture("drainagepipeCRfourupNONselect.png");
	 mDrainagePipeCRFourUpNONSelect->Parent(this);
	 mDrainagePipeCRFourUpNONSelect->Pos(Vector2(207, 785));
	 mDrainagePipeCRFourUpMouseOver = new Texture("drainagepipeCRfourupmouseover.png");
	 mDrainagePipeCRFourUpMouseOver->Parent(this);
	 mDrainagePipeCRFourUpMouseOver->Pos(Vector2(207, 785));
	 mDrainagePipeCRFourUpSelect = new Texture("drainagepipeCRfourupselect.png");
	 mDrainagePipeCRFourUpSelect->Parent(this);
	 mDrainagePipeCRFourUpSelect->Pos(Vector2(207, 785));

	 mDrainagePipeCRFourRight = new Texture("drainagepipeCRfourright.png");
	 mDrainagePipeCRFourRightFlood = new Texture("drainagepipeCRfourrightflood.png");
	 mDrainagePipeCRFourRightNONSelect = new Texture("drainagepipeCRfourrightNONselect.png");
	 mDrainagePipeCRFourRightNONSelect->Parent(this);
	 mDrainagePipeCRFourRightNONSelect->Pos(Vector2(241, 785));
	 mDrainagePipeCRFourRightMouseOver = new Texture("drainagepipeCRfourrightmouseover.png");
	 mDrainagePipeCRFourRightMouseOver->Parent(this);
	 mDrainagePipeCRFourRightMouseOver->Pos(Vector2(241, 785));
	 mDrainagePipeCRFourRightSelect = new Texture("drainagepipeCRfourrightselect.png");
	 mDrainagePipeCRFourRightSelect->Parent(this);
	 mDrainagePipeCRFourRightSelect->Pos(Vector2(241, 785));


	 //T SHAPE ONE PIPE
	 mDrainagePipeTOneDown = new Texture("drainagepipeTonedown.png");
	 mDrainagePipeTOneDownFlood = new Texture("drainagepipeTonedownflood.png");
	 mDrainagePipeTOneDownNONSelect = new Texture("drainagepipeTonedownNONselect.png");
	 mDrainagePipeTOneDownNONSelect->Parent(this);
	 mDrainagePipeTOneDownNONSelect->Pos(Vector2(275, 785));
	 mDrainagePipeTOneDownMouseOver = new Texture("drainagepipeTonedownmouseover.png");
	 mDrainagePipeTOneDownMouseOver->Parent(this);
	 mDrainagePipeTOneDownMouseOver->Pos(Vector2(275, 785));
	 mDrainagePipeTOneDownSelect = new Texture("drainagepipeTonedownselect.png");
	 mDrainagePipeTOneDownSelect->Parent(this);
	 mDrainagePipeTOneDownSelect->Pos(Vector2(275, 785));

	 mDrainagePipeTOneRight = new Texture("drainagepipeToneright.png");
	 mDrainagePipeTOneRightFlood = new Texture("drainagepipeTonerightflood.png");
	 mDrainagePipeTOneRightNONSelect = new Texture("drainagepipeTonerightNONselect.png");
	 mDrainagePipeTOneRightNONSelect->Parent(this);
	 mDrainagePipeTOneRightNONSelect->Pos(Vector2(309, 785));
	 mDrainagePipeTOneRightMouseOver = new Texture("drainagepipeTonerightmouseover.png");
	 mDrainagePipeTOneRightMouseOver->Parent(this);
	 mDrainagePipeTOneRightMouseOver->Pos(Vector2(309, 785));
	 mDrainagePipeTOneRightSelect = new Texture("drainagepipeTonerightselect.png");
	 mDrainagePipeTOneRightSelect->Parent(this);
	 mDrainagePipeTOneRightSelect->Pos(Vector2(309, 785));

	 mDrainagePipeTOneLeft = new Texture("drainagepipeToneleft.png");
	 mDrainagePipeTOneLeftFlood = new Texture("drainagepipeToneleftflood.png");
	 mDrainagePipeTOneLeftNONSelect = new Texture("drainagepipeToneleftNONselect.png");
	 mDrainagePipeTOneLeftNONSelect->Parent(this);
	 mDrainagePipeTOneLeftNONSelect->Pos(Vector2(105, 819));
	 mDrainagePipeTOneLeftMouseOver = new Texture("drainagepipeToneleftmouseover.png");
	 mDrainagePipeTOneLeftMouseOver->Parent(this);
	 mDrainagePipeTOneLeftMouseOver->Pos(Vector2(105, 819));
	 mDrainagePipeTOneLeftSelect = new Texture("drainagepipeToneleftselect.png");
	 mDrainagePipeTOneLeftSelect->Parent(this);
	 mDrainagePipeTOneLeftSelect->Pos(Vector2(105, 819));


	 //T SHAPE TWO PIPE
	 mDrainagePipeTTwoDown = new Texture("drainagepipeTtwodown.png");
	 mDrainagePipeTTwoDownFlood = new Texture("drainagepipeTtwodownflood.png");
	 mDrainagePipeTTwoDownNONSelect = new Texture("drainagepipeTtwodownNONselect.png");
	 mDrainagePipeTTwoDownNONSelect->Parent(this);
	 mDrainagePipeTTwoDownNONSelect->Pos(Vector2(139, 819));
	 mDrainagePipeTTwoDownMouseOver = new Texture("drainagepipeTtwodownmouseover.png");
	 mDrainagePipeTTwoDownMouseOver->Parent(this);
	 mDrainagePipeTTwoDownMouseOver->Pos(Vector2(139, 819));
	 mDrainagePipeTTwoDownSelect = new Texture("drainagepipeTtwodownselect.png");
	 mDrainagePipeTTwoDownSelect->Parent(this);
	 mDrainagePipeTTwoDownSelect->Pos(Vector2(139, 819));

	 mDrainagePipeTTwoUp = new Texture("drainagepipeTtwoup.png");
	 mDrainagePipeTTwoUpFlood = new Texture("drainagepipeTtwoupflood.png");
	 mDrainagePipeTTwoUpNONSelect = new Texture("drainagepipeTtwoupNONselect.png");
	 mDrainagePipeTTwoUpNONSelect->Parent(this);
	 mDrainagePipeTTwoUpNONSelect->Pos(Vector2(173, 819));
	 mDrainagePipeTTwoUpMouseOver = new Texture("drainagepipeTtwoupmouseover.png");
	 mDrainagePipeTTwoUpMouseOver->Parent(this);
	 mDrainagePipeTTwoUpMouseOver->Pos(Vector2(173, 819));
	 mDrainagePipeTTwoUpSelect = new Texture("drainagepipeTtwoupselect.png");
	 mDrainagePipeTTwoUpSelect->Parent(this);
	 mDrainagePipeTTwoUpSelect->Pos(Vector2(173, 819));

	 mDrainagePipeTTwoLeft = new Texture("drainagepipeTtwoleft.png");
	 mDrainagePipeTTwoLeftFlood = new Texture("drainagepipeTtwoleftflood.png");
	 mDrainagePipeTTwoLeftNONSelect = new Texture("drainagepipeTtwoleftNONselect.png");
	 mDrainagePipeTTwoLeftNONSelect->Parent(this);
	 mDrainagePipeTTwoLeftNONSelect->Pos(Vector2(207, 819));
	 mDrainagePipeTTwoLeftMouseOver = new Texture("drainagepipeTtwoleftmouseover.png");
	 mDrainagePipeTTwoLeftMouseOver->Parent(this);
	 mDrainagePipeTTwoLeftMouseOver->Pos(Vector2(207, 819));
	 mDrainagePipeTTwoLeftSelect = new Texture("drainagepipeTtwoleftselect.png");
	 mDrainagePipeTTwoLeftSelect->Parent(this);
	 mDrainagePipeTTwoLeftSelect->Pos(Vector2(207, 819));




	 //T SHAPE THREE PIPE
	 mDrainagePipeTThreeDown = new Texture("drainagepipeTthreedown.png");
	 mDrainagePipeTThreeDownFlood = new Texture("drainagepipeTthreedownflood.png");
	 mDrainagePipeTThreeDownNONSelect = new Texture("drainagepipeTthreedownNONselect.png");
	 mDrainagePipeTThreeDownNONSelect->Parent(this);
	 mDrainagePipeTThreeDownNONSelect->Pos(Vector2(241, 819));
	 mDrainagePipeTThreeDownMouseOver = new Texture("drainagepipeTthreedownmouseover.png");
	 mDrainagePipeTThreeDownMouseOver->Parent(this);
	 mDrainagePipeTThreeDownMouseOver->Pos(Vector2(241, 819));
	 mDrainagePipeTThreeDownSelect = new Texture("drainagepipeTthreedownselect.png");
	 mDrainagePipeTThreeDownSelect->Parent(this);
	 mDrainagePipeTThreeDownSelect->Pos(Vector2(241, 819));

	 mDrainagePipeTThreeUp = new Texture("drainagepipeTthreeup.png");
	 mDrainagePipeTThreeUpFlood = new Texture("drainagepipeTthreeupflood.png");
	 mDrainagePipeTThreeUpNONSelect = new Texture("drainagepipeTthreeupNONselect.png");
	 mDrainagePipeTThreeUpNONSelect->Parent(this);
	 mDrainagePipeTThreeUpNONSelect->Pos(Vector2(275, 819));
	 mDrainagePipeTThreeUpMouseOver = new Texture("drainagepipeTthreeupmouseover.png");
	 mDrainagePipeTThreeUpMouseOver->Parent(this);
	 mDrainagePipeTThreeUpMouseOver->Pos(Vector2(275, 819));
	 mDrainagePipeTThreeUpSelect = new Texture("drainagepipeTthreeupselect.png");
	 mDrainagePipeTThreeUpSelect->Parent(this);
	 mDrainagePipeTThreeUpSelect->Pos(Vector2(275, 819));

	 mDrainagePipeTThreeRight = new Texture("drainagepipeTthreeright.png");
	 mDrainagePipeTThreeRightFlood = new Texture("drainagepipeTthreerightflood.png");
	 mDrainagePipeTThreeRightNONSelect = new Texture("drainagepipeTthreerightNONselect.png");
	 mDrainagePipeTThreeRightNONSelect->Parent(this);
	 mDrainagePipeTThreeRightNONSelect->Pos(Vector2(309, 819));
	 mDrainagePipeTThreeRightMouseOver = new Texture("drainagepipeTthreerightmouseover.png");
	 mDrainagePipeTThreeRightMouseOver->Parent(this);
	 mDrainagePipeTThreeRightMouseOver->Pos(Vector2(309, 819));
	 mDrainagePipeTThreeRightSelect = new Texture("drainagepipeTthreerightselect.png");
	 mDrainagePipeTThreeRightSelect->Parent(this);
	 mDrainagePipeTThreeRightSelect->Pos(Vector2(309, 819));

	 


	 //T SHAPE FOUR PIPE
	 mDrainagePipeTFourLeft = new Texture("drainagepipeTfourleft.png");
	 mDrainagePipeTFourLeftFlood = new Texture("drainagepipeTfourleftflood.png");
	 mDrainagePipeTFourLeftNONSelect = new Texture("drainagepipeTfourleftNONselect.png");
	 mDrainagePipeTFourLeftNONSelect->Parent(this);
	 mDrainagePipeTFourLeftNONSelect->Pos(Vector2(105, 853));
	 mDrainagePipeTFourLeftMouseOver = new Texture("drainagepipeTfourleftmouseover.png");
	 mDrainagePipeTFourLeftMouseOver->Parent(this);
	 mDrainagePipeTFourLeftMouseOver->Pos(Vector2(105, 853));
	 mDrainagePipeTFourLeftSelect = new Texture("drainagepipeTfourleftselect.png");
	 mDrainagePipeTFourLeftSelect->Parent(this);
	 mDrainagePipeTFourLeftSelect->Pos(Vector2(105, 853));

	 mDrainagePipeTFourUp = new Texture("drainagepipeTfourup.png");
	 mDrainagePipeTFourUpFlood = new Texture("drainagepipeTfourupflood.png");
	 mDrainagePipeTFourUpNONSelect = new Texture("drainagepipeTfourupNONselect.png");
	 mDrainagePipeTFourUpNONSelect->Parent(this);
	 mDrainagePipeTFourUpNONSelect->Pos(Vector2(139, 853));
	 mDrainagePipeTFourUpMouseOver = new Texture("drainagepipeTfourupmouseover.png");
	 mDrainagePipeTFourUpMouseOver->Parent(this);
	 mDrainagePipeTFourUpMouseOver->Pos(Vector2(139, 853));
	 mDrainagePipeTFourUpSelect = new Texture("drainagepipeTfourupselect.png");
	 mDrainagePipeTFourUpSelect->Parent(this);
	 mDrainagePipeTFourUpSelect->Pos(Vector2(139, 853));

	 mDrainagePipeTFourRight = new Texture("drainagepipeTfourright.png");
	 mDrainagePipeTFourRightFlood = new Texture("drainagepipeTfourrightflood.png");
	 mDrainagePipeTFourRightNONSelect = new Texture("drainagepipeTfourrightNONselect.png");
	 mDrainagePipeTFourRightNONSelect->Parent(this);
	 mDrainagePipeTFourRightNONSelect->Pos(Vector2(173, 853));
	 mDrainagePipeTFourRightMouseOver = new Texture("drainagepipeTfourrightmouseover.png");
	 mDrainagePipeTFourRightMouseOver->Parent(this);
	 mDrainagePipeTFourRightMouseOver->Pos(Vector2(173, 853));
	 mDrainagePipeTFourRightSelect = new Texture("drainagepipeTfourrightselect.png");
	 mDrainagePipeTFourRightSelect->Parent(this);
	 mDrainagePipeTFourRightSelect->Pos(Vector2(173, 853));


	 

	 //SQUARE PIPE UP
	 mDrainagePipeSquareUp = new Texture("drainagepipesquareup.png");
	 mDrainagePipeSquareUpFlood = new Texture("drainagepipesquareupflood.png");
	 mDrainagePipeSquareUpNONSelect = new Texture("drainagepipesquareup.png");
	 mDrainagePipeSquareUpNONSelect->Parent(this);
	 mDrainagePipeSquareUpNONSelect->Pos(Vector2(207, 853));
	 mDrainagePipeSquareUpMouseOver = new Texture("drainagepipesquareupmouseover.png");
	 mDrainagePipeSquareUpMouseOver->Parent(this);
	 mDrainagePipeSquareUpMouseOver->Pos(Vector2(207, 853));
	 mDrainagePipeSquareUpSelect = new Texture("drainagepipesquareupselect.png");
	 mDrainagePipeSquareUpSelect->Parent(this);
	 mDrainagePipeSquareUpSelect->Pos(Vector2(207, 853));



	 mDrainagePipeSquareDown = new Texture("drainagepipesquaredown.png");
	 mDrainagePipeSquareDownFlood = new Texture("drainagepipesquaredownflood.png");
	 mDrainagePipeSquareDownNONSelect = new Texture("drainagepipesquaredown.png");
	 mDrainagePipeSquareDownNONSelect->Parent(this);
	 mDrainagePipeSquareDownNONSelect->Pos(Vector2(241, 853));
	 mDrainagePipeSquareDownMouseOver = new Texture("drainagepipesquaredownmouseover.png");
	 mDrainagePipeSquareDownMouseOver->Parent(this);
	 mDrainagePipeSquareDownMouseOver->Pos(Vector2(241, 853));
	 mDrainagePipeSquareDownSelect = new Texture("drainagepipesquaredownselect.png");
	 mDrainagePipeSquareDownSelect->Parent(this);
	 mDrainagePipeSquareDownSelect->Pos(Vector2(241, 853));



	 mDrainagePipeSquareLeft = new Texture("drainagepipesquareleft.png");
	 mDrainagePipeSquareLeftFlood = new Texture("drainagepipesquareleftflood.png");
	 mDrainagePipeSquareLeftNONSelect = new Texture("drainagepipesquareleft.png");
	 mDrainagePipeSquareLeftNONSelect->Parent(this);
	 mDrainagePipeSquareLeftNONSelect->Pos(Vector2(275, 853));
	 mDrainagePipeSquareLeftMouseOver = new Texture("drainagepipesquareleftmouseover.png");
	 mDrainagePipeSquareLeftMouseOver->Parent(this);
	 mDrainagePipeSquareLeftMouseOver->Pos(Vector2(275, 853));
	 mDrainagePipeSquareLeftSelect = new Texture("drainagepipesquareleftselect.png");
	 mDrainagePipeSquareLeftSelect->Parent(this);
	 mDrainagePipeSquareLeftSelect->Pos(Vector2(275, 853));



	 mDrainagePipeSquareRight = new Texture("drainagepipesquareright.png");
	 mDrainagePipeSquareRightFlood = new Texture("drainagepipesquarerightflood.png");
	 mDrainagePipeSquareRightNONSelect = new Texture("drainagepipesquareright.png");
	 mDrainagePipeSquareRightNONSelect->Parent(this);
	 mDrainagePipeSquareRightNONSelect->Pos(Vector2(309, 853));
	 mDrainagePipeSquareRightMouseOver = new Texture("drainagepipesquarerightmouseover.png");
	 mDrainagePipeSquareRightMouseOver->Parent(this);
	 mDrainagePipeSquareRightMouseOver->Pos(Vector2(309, 853));
	 mDrainagePipeSquareRightSelect = new Texture("drainagepipesquarerightselect.png");
	 mDrainagePipeSquareRightSelect->Parent(this);
	 mDrainagePipeSquareRightSelect->Pos(Vector2(309, 853));



	 //Pipe  Button Positions
	 mDrainagePipeVUpPosition.x = 105;
	 mDrainagePipeVUpPosition.y = 751;

	 mDrainagePipeVDownPosition.x = 139;
	 mDrainagePipeVDownPosition.y = 751;

	 mDrainagePipeHRightPosition.x = 173;
	 mDrainagePipeHRightPosition.y = 751;

	 mDrainagePipeHLeftPosition.x = 207;
	 mDrainagePipeHLeftPosition.y = 751;

	 mDrainagePipeCROneDownPosition.x = 241;
	 mDrainagePipeCROneDownPosition.y = 751;
	 mDrainagePipeCROneRightPosition.x = 275;
	 mDrainagePipeCROneRightPosition.y = 751;

	 mDrainagePipeCRTwoDownPosition.x = 309;
	 mDrainagePipeCRTwoDownPosition.y = 751;
	 mDrainagePipeCRTwoLeftPosition.x = 105;
	 mDrainagePipeCRTwoLeftPosition.y = 785;

	 mDrainagePipeCRThreeUpPosition.x = 139;
	 mDrainagePipeCRThreeUpPosition.y = 785;
	 mDrainagePipeCRThreeLeftPosition.x = 173;
	 mDrainagePipeCRThreeLeftPosition.y = 785;

	 mDrainagePipeCRFourUpPosition.x = 207;
	 mDrainagePipeCRFourUpPosition.y = 785;
	 mDrainagePipeCRFourRightPosition.x = 241;
	 mDrainagePipeCRFourRightPosition.y = 785;


	 mDrainagePipeTOneDownPosition.x = 275;
	 mDrainagePipeTOneDownPosition.y = 785;
	 mDrainagePipeTOneRightPosition.x = 309;
	 mDrainagePipeTOneRightPosition.y = 785;
	 mDrainagePipeTOneLeftPosition.x = 105;
	 mDrainagePipeTOneLeftPosition.y = 819;


	 mDrainagePipeTTwoDownPosition.x = 139;
	 mDrainagePipeTTwoDownPosition.y = 819;
	 mDrainagePipeTTwoUpPosition.x = 173;
	 mDrainagePipeTTwoUpPosition.y = 819;
	 mDrainagePipeTTwoLeftPosition.x = 207;
	 mDrainagePipeTTwoLeftPosition.y = 819;


	 mDrainagePipeTThreeDownPosition.x = 241;
	 mDrainagePipeTThreeDownPosition.y = 819;
	 mDrainagePipeTThreeUpPosition.x = 275;
	 mDrainagePipeTThreeUpPosition.y = 819;
	 mDrainagePipeTThreeRightPosition.x = 309;
	 mDrainagePipeTThreeRightPosition.y = 819;

	 mDrainagePipeTFourLeftPosition.x = 105;
	 mDrainagePipeTFourLeftPosition.y = 853;
	 mDrainagePipeTFourUpPosition.x = 139;
	 mDrainagePipeTFourUpPosition.y = 853;
	 mDrainagePipeTFourRightPosition.x = 175;
	 mDrainagePipeTFourRightPosition.y = 853;


	 mDrainagePipeSquareUpPosition.x = 207;
	 mDrainagePipeSquareUpPosition.y = 853;
	 mDrainagePipeSquareDownPosition.x = 241;
	 mDrainagePipeSquareDownPosition.y = 853;
	 mDrainagePipeSquareLeftPosition.x = 275;
	 mDrainagePipeSquareLeftPosition.y = 853;
	 mDrainagePipeSquareRightPosition.x = 309;
	 mDrainagePipeSquareRightPosition.y = 853;





	 mChangeDrainagePipeVUpMouseOver = NULL;
	 mChangeDrainagePipeVUpSelect = NULL;
	 mChangeDrainagePipeVDownMouseOver = NULL;
	 mChangeDrainagePipeVDownSelect = NULL;

	 mChangeDrainagePipeHLeftMouseOver = NULL;
	 mChangeDrainagePipeHLeftSelect = NULL;
	 mChangeDrainagePipeHRightMouseOver = NULL;
	 mChangeDrainagePipeHRightSelect = NULL;

	 mChangeDrainagePipeCROneDownMouseOver = NULL;
	 mChangeDrainagePipeCROneDownSelect = NULL;
	 mChangeDrainagePipeCROneRightMouseOver = NULL;
	 mChangeDrainagePipeCROneRightSelect = NULL;

	 mChangeDrainagePipeCRTwoDownMouseOver = NULL;
	 mChangeDrainagePipeCRTwoDownSelect = NULL;
	 mChangeDrainagePipeCRTwoLeftMouseOver = NULL;
	 mChangeDrainagePipeCRTwoLeftSelect = NULL;

	 mChangeDrainagePipeCRThreeUpMouseOver = NULL;
	 mChangeDrainagePipeCRThreeUpSelect = NULL;
	 mChangeDrainagePipeCRThreeLeftMouseOver = NULL;
	 mChangeDrainagePipeCRThreeLeftSelect = NULL;

	 mChangeDrainagePipeCRFourUpMouseOver = NULL;
	 mChangeDrainagePipeCRFourUpSelect = NULL;
	 mChangeDrainagePipeCRFourRightMouseOver = NULL;
	 mChangeDrainagePipeCRFourRightSelect = NULL;

	 mChangeDrainagePipeTOneDownMouseOver = NULL;
	 mChangeDrainagePipeTOneDownSelect = NULL;
	 mChangeDrainagePipeTOneLeftMouseOver = NULL;
	 mChangeDrainagePipeTOneLeftSelect = NULL;
	 mChangeDrainagePipeTOneRightMouseOver = NULL;
	 mChangeDrainagePipeTOneRightSelect = NULL;

	 mChangeDrainagePipeTTwoDownMouseOver = NULL;
	 mChangeDrainagePipeTTwoDownSelect = NULL;
	 mChangeDrainagePipeTTwoUpMouseOver = NULL;
	 mChangeDrainagePipeTTwoUpSelect = NULL;
	 mChangeDrainagePipeTTwoLeftMouseOver = NULL;
	 mChangeDrainagePipeTTwoLeftSelect = NULL;


	 mChangeDrainagePipeTThreeDownMouseOver = NULL;
	 mChangeDrainagePipeTThreeDownSelect = NULL;
	 mChangeDrainagePipeTThreeRightMouseOver = NULL;
	 mChangeDrainagePipeTThreeRightSelect = NULL;
	 mChangeDrainagePipeTThreeUpMouseOver = NULL;
	 mChangeDrainagePipeTThreeUpSelect = NULL;

	 mChangeDrainagePipeTFourRightMouseOver = NULL;
	 mChangeDrainagePipeTFourRightSelect = NULL;
	 mChangeDrainagePipeTFourLeftMouseOver = NULL;
	 mChangeDrainagePipeTFourLeftSelect = NULL;
	 mChangeDrainagePipeTFourUpMouseOver = NULL;
	 mChangeDrainagePipeTFourUpSelect = NULL;

	 mChangeDrainagePipeSquareUpMouseOver = NULL;
	 mChangeDrainagePipeSquareUpSelect = NULL;
	 mChangeDrainagePipeSquareDownMouseOver = NULL;
	 mChangeDrainagePipeSquareDownSelect = NULL;
	 mChangeDrainagePipeSquareLeftMouseOver = NULL;
	 mChangeDrainagePipeSquareLeftSelect = NULL;
	 mChangeDrainagePipeSquareRightMouseOver = NULL;
	 mChangeDrainagePipeSquareRightSelect = NULL;


	 mPipeMenuBackground = new Texture("pipemenubackground.png");
	 mPipeMenuBackground->Parent(this);
	 mPipeMenuBackground->Pos(Vector2(35, 740));
	 //mPipeMenuBackground->Scale(Vector2(0.5f, 0.5f));

	 mPipeMenuBackgroundHighlight = new Texture("pipemenubackgroundhighlight.png");
	 mPipeMenuBackgroundHighlight->Parent(this);
	 mPipeMenuBackgroundHighlight->Pos(Vector2(35, 740));
	// mPipeMenuBackgroundHighlight->Scale(Vector2(0.5f, 0.5f));

	 mPipeMenuBackgroundSelect = new Texture("pipemenubackgroundselect.png");
	 mPipeMenuBackgroundSelect->Parent(this);
	 mPipeMenuBackgroundSelect->Pos(Vector2(35, 740));
	// mPipeMenuBackgroundSelect->Scale(Vector2(0.5f, 0.5f));

	


	 //CONTAMINANT MENU



	 mSewage = NULL;

	 mFilter = new Texture("filter.png");


	 mFilterNONSelect = new Texture("filter.png");
	 mFilterNONSelect->Parent(this);
	 mFilterNONSelect->Pos(Vector2(105, 751));
	 mFilterMouseOver = new Texture("filtermouseover.png");
	 mFilterMouseOver->Parent(this);
	 mFilterMouseOver->Pos(Vector2(105, 751));
	 mFilterSelect = new Texture("filterselect.png");
	 mFilterSelect->Parent(this);
	 mFilterSelect->Pos(Vector2(105, 751));

	 mFilterPosition.x = 105;
	 mFilterPosition.y = 751;


	 mChangeFilterMouseOver = NULL;
	 mChangeFilterSelect = NULL;





	 mContaminantMenuPosition.x = 40;
	 mContaminantMenuPosition.y = 800;

	 mContaminantMenuMouseOver = NULL;
	 mContaminantMenuSelect = NULL;


	 mContaminantMenuBackground = new Texture("contaminantpoopmenubackground.png");
	 mContaminantMenuBackground->Parent(this);
	 mContaminantMenuBackground->Pos(Vector2(35, 795));
	 // mContaminantMenuBackground->Scale(Vector2(0.5f, 0.5f));



	 mContaminantMenuBackgroundHighlight = new Texture("contaminantpoopmenubackgroundhighlight.png");
	 mContaminantMenuBackgroundHighlight->Parent(this);
	 mContaminantMenuBackgroundHighlight->Pos(Vector2(35, 795));


	 mContaminantMenuBackgroundSelect = new Texture("contaminantpoopmenubackgroundselect.png");
	 mContaminantMenuBackgroundSelect->Parent(this);
	 mContaminantMenuBackgroundSelect->Pos(Vector2(35, 795));











	//POWER MENU

	 mPower = NULL;

	 mGenerator = new Texture("generator.png");


	 mGeneratorNONSelect = new Texture("generator.png");
	 mGeneratorNONSelect->Parent(this);
	 mGeneratorNONSelect->Pos(Vector2(105, 751));
	 mGeneratorMouseOver = new Texture("generatormouseover.png");
	 mGeneratorMouseOver->Parent(this);
	 mGeneratorMouseOver->Pos(Vector2(105, 751));
	 mGeneratorSelect = new Texture("generatorselect.png");
	 mGeneratorSelect->Parent(this);
	 mGeneratorSelect->Pos(Vector2(105, 751));

	 mGeneratorPosition.x = 105;
	 mGeneratorPosition.y = 751;


	 mChangeGeneratorMouseOver = NULL;
	 mChangeGeneratorSelect = NULL;




	 mPowerMenuPosition.x = 40;
	 mPowerMenuPosition.y = 860;

	 mPowerMenuMouseOver = NULL;
	 mPowerMenuSelect = NULL;

	 mPowerMenuBackground = new Texture("powermenubackground.png");
	 mPowerMenuBackground->Parent(this);
	 mPowerMenuBackground->Pos(Vector2(35, 850));



	 mPowerMenuBackgroundHighlight = new Texture("powermenubackgroundhighlight.png");
	 mPowerMenuBackgroundHighlight->Parent(this);
	 mPowerMenuBackgroundHighlight->Pos(Vector2(35, 850));


	 mPowerMenuBackgroundSelect = new Texture("powermenubackgroundselect.png");
	 mPowerMenuBackgroundSelect->Parent(this);
	 mPowerMenuBackgroundSelect->Pos(Vector2(35, 850));









}



InteractionMap::~InteractionMap() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;
	
	mStageTimer = NULL;

	mCarSpawnTimer = NULL;
	mCarSpawnTimerInterval = NULL;

	mHouseSpawnTimer = NULL;
	mHouseSpawnTimerInterval = NULL;

	mRainSpawnTimer = NULL;
	mRainSpawnTimerInterval = NULL;

	mFloodTimer = NULL;
	mFloodTimerInterval = NULL;

	mDrainTimer = NULL;
	mDrainTimerInterval = NULL;

	mWaterMovementTimer = NULL;
	mWaterMovementTimerInterval = NULL;

	mGameOverTimer = NULL;
	mGameOverDelay = NULL;

	//mTestText1 = NULL;
	//mTestText2 = NULL;

	mHouseFloodedLose = NULL;
	mGameOverLabel = NULL;
	mGameOverLabelOnScreen = NULL;

	mFundingText = NULL;
	mDollarSignInterface = NULL;
	mDollarValue = NULL;
	mDollarInterface = NULL;


	mTileHorizontal = NULL;
	mTileVertical = NULL;

	mChangeTileSelect = NULL;
	mTileSelect = NULL;

	mTileText = NULL;


	mWaterText = NULL;
	mDirtText = NULL;
	mGrassText = NULL;
	mStreetText = NULL;

	mTileHighlight = NULL;
	mTileHighlightOn = NULL;

	///
	///        EMPTY ARRAYS OUT?????????????????
	///
	//delete[] mTileMap;
	//delete[] mPipeMap;

	//delete[] mFloodValueMap;

	delete mSewageMap;
	delete mPowerMap;


	mUtilityManInterface = NULL;
	mAnimatedUtilityManInterface = NULL;
	mCarSideways = NULL;

	mCar = NULL;
	mCarTwo = NULL;
	mCarSpawned = NULL;
	mLitterRow = NULL;
	mLitterColumn = NULL;
	mDropTime = NULL;
	mDropTimeTwo = NULL;
	mLitter = NULL;
	mTrashCan = NULL;

	mUnitNotPlaced = NULL;
	mRainNotPlaced = NULL;
	mFloodNotDrained = NULL;


	mRaindrops = NULL;
	mRaindropsTwo = NULL;
	mRainInitialX = NULL;
	mRainInitialY = NULL;
	mRainPositionX = NULL;
	mRainPositionY = NULL;
	mRainTwoPositionX = NULL;
	mRainTwoPositionY = NULL;
	mIsRaining = NULL;
	mFloodReduce = NULL;
	mFloodLevelOne = NULL;
	mFloodLevelTwo = NULL;
	mFloodLevelThree = NULL;
	mFloodLevelOneAnimation = NULL;
	mFloodLevelTwoAnimation = NULL;
	mFloodLevelThreeAnimation = NULL;

	mFloodLabelText = NULL;
	mFloodValue = NULL;

	mContaminantLabelText = NULL;
	mContaminantValue = NULL;


	 mContour = NULL;
	 mCliffTileCheck = NULL;

	 mElevationOneLeft = NULL;
	 mElevationOneRight = NULL;
	 mElevationOneTop = NULL;
	 mElevationOneBottom = NULL;
	 mElevationOneLeftTopCorner = NULL;
	 mElevationOneLeftBottomCorner = NULL;
	 mElevationOneRightTopCorner = NULL;
	 mElevationOneRightBottomCorner = NULL;
	 mElevationOneUShapeLeft = NULL;
	 mElevationOneUShapeRight = NULL;
	 mElevationOneUShapeTop = NULL;
	 mElevationOneUShapeBottom = NULL;
	 mElevationOneVerticalTunnel = NULL;
	 mElevationOneHorizontalTunnel = NULL;
	 mElevationOneSquare = NULL;


	 //MENU VARIABLES
	 mStructureMenuTotal = NULL;
	 mStructureMenuBackground = NULL;
	 mStructureMenuBackgroundHighlight = NULL;
	 mStructureMenuBackgroundSelect = NULL;

	 //Movement
	 mStructureMenuMovementBackground = NULL;
	 mStructureMenuMovementBackgroundHighlight = NULL;
	 mStructureMenuMovementBackgroundSelect = NULL;
	 mChangeStructureMenuMovementMouseOver = NULL;
	 mChangeStructureMenuMovementSelect = NULL;

	 //Action
	 mStructureMenuActionBackground = NULL;
	 mStructureMenuActionBackgroundHighlight = NULL;
	 mStructureMenuActionBackgroundSelect = NULL;
	 mChangeStructureMenuActionMouseOver = NULL;
	 mChangeStructureMenuActionSelect = NULL;

	 //Item
	 mStructureMenuItemBackground = NULL;
	 mStructureMenuItemBackgroundHighlight = NULL;
	 mStructureMenuItemBackgroundSelect = NULL;
	 mChangeStructureMenuItemMouseOver = NULL;
	 mChangeStructureMenuItemSelect = NULL;

	 //Status
	 mStructureMenuStatusBackground = NULL;
	 mStructureMenuStatusBackgroundHighlight = NULL;
	 mStructureMenuStatusBackgroundSelect = NULL;
	 mChangeStructureMenuStatusMouseOver = NULL;
	 mChangeStructureMenuStatusSelect = NULL;

	 //Text for each kind of unit
	 mStructureMenuMovementText = NULL;
	 mStructureMenuActionText = NULL;
	 mStructureMenuItemText = NULL;
	 mStructureMenuStatusText = NULL;

	 mStructurePositionValue = NULL;
	 mStructurePositionSelect = NULL;
	 mStructurePositionSelectX = NULL;
	 mStructurePositionSelectY = NULL;
	 mStructurePositionTargetX = NULL;
	 mStructurePositionTargetY = NULL;

	 mStructureActionSelectValue = NULL;
	 mStructureActionTargetValue = NULL;
	 mStructureActionSelect = NULL;
	 mStructureActionSelectX = NULL;
	 mStructureActionSelectY = NULL;
	 mStructureActionTargetX = NULL;
	 mStructureActionTargetY = NULL;





	mPipe = NULL;

	mWaterTreatmentPlant = NULL;

	mHouse = NULL;




	 mDrainagePipeVUp = NULL;
	 mDrainagePipeVUpFlood = NULL;
	 mDrainagePipeVUpNONSelect = NULL;
	 mDrainagePipeVUpMouseOver = NULL;
	 mDrainagePipeVUpSelect = NULL;


	 mDrainagePipeVDown = NULL;
	 mDrainagePipeVDownFlood = NULL;
	 mDrainagePipeVDownNONSelect = NULL;
	 mDrainagePipeVDownMouseOver = NULL;
	 mDrainagePipeVDownSelect = NULL;


	 mDrainagePipeHLeft = NULL;
	 mDrainagePipeHLeftFlood = NULL;
	 mDrainagePipeHLeftNONSelect = NULL;
	 mDrainagePipeHLeftMouseOver = NULL;
	 mDrainagePipeHLeftSelect = NULL;


	 mDrainagePipeHRight = NULL;
	 mDrainagePipeHRightFlood = NULL;
	 mDrainagePipeHRightNONSelect = NULL;
	 mDrainagePipeHRightMouseOver = NULL;
	 mDrainagePipeHRightSelect = NULL;

	 mDrainagePipeCROneRight = NULL;
	 mDrainagePipeCROneRightFlood = NULL;
	 mDrainagePipeCROneRightNONSelect = NULL;
	 mDrainagePipeCROneRightMouseOver = NULL;
	 mDrainagePipeCROneRightSelect = NULL;
	 mDrainagePipeCROneDown = NULL;
	 mDrainagePipeCROneDownFlood = NULL;
	 mDrainagePipeCROneDownNONSelect = NULL;
	 mDrainagePipeCROneDownMouseOver = NULL;
	 mDrainagePipeCROneDownSelect = NULL;

	 mDrainagePipeCRTwoLeft = NULL;
	 mDrainagePipeCRTwoLeftFlood = NULL;
	 mDrainagePipeCRTwoLeftNONSelect = NULL;
	 mDrainagePipeCRTwoLeftMouseOver = NULL;
	 mDrainagePipeCRTwoLeftSelect = NULL;
	 mDrainagePipeCRTwoDown = NULL;
	 mDrainagePipeCRTwoDownFlood = NULL;
	 mDrainagePipeCRTwoDownNONSelect = NULL;
	 mDrainagePipeCRTwoDownMouseOver = NULL;
	 mDrainagePipeCRTwoDownSelect = NULL;

	 mDrainagePipeCRThreeLeft = NULL;
	 mDrainagePipeCRThreeLeftFlood = NULL;
	 mDrainagePipeCRThreeLeftNONSelect = NULL;
	 mDrainagePipeCRThreeLeftMouseOver = NULL;
	 mDrainagePipeCRThreeLeftSelect = NULL;
	 mDrainagePipeCRThreeUp = NULL;
	 mDrainagePipeCRThreeUpFlood = NULL;
	 mDrainagePipeCRThreeUpNONSelect = NULL;
	 mDrainagePipeCRThreeUpMouseOver = NULL;
	 mDrainagePipeCRThreeUpSelect = NULL;

	 mDrainagePipeCRFourRight = NULL;
	 mDrainagePipeCRFourRightFlood = NULL;
	 mDrainagePipeCRFourRightNONSelect = NULL;
	 mDrainagePipeCRFourRightMouseOver = NULL;
	 mDrainagePipeCRFourRightSelect = NULL;
	 mDrainagePipeCRFourUp = NULL;
	 mDrainagePipeCRFourUpFlood = NULL;
	 mDrainagePipeCRFourUpNONSelect = NULL;
	 mDrainagePipeCRFourUpMouseOver = NULL;
	 mDrainagePipeCRFourUpSelect = NULL;

	 mDrainagePipeTOneRight = NULL;
	 mDrainagePipeTOneRightFlood = NULL;
	 mDrainagePipeTOneRightNONSelect = NULL;
	 mDrainagePipeTOneRightMouseOver = NULL;
	 mDrainagePipeTOneRightSelect = NULL;
	 mDrainagePipeTOneDown = NULL;
	 mDrainagePipeTOneDownFlood = NULL;
	 mDrainagePipeTOneDownNONSelect = NULL;
	 mDrainagePipeTOneDownMouseOver = NULL;
	 mDrainagePipeTOneDownSelect = NULL;
	 mDrainagePipeTOneLeft = NULL;
	 mDrainagePipeTOneLeftFlood = NULL;
	 mDrainagePipeTOneLeftNONSelect = NULL;
	 mDrainagePipeTOneLeftMouseOver = NULL;
	 mDrainagePipeTOneLeftSelect = NULL;

	 mDrainagePipeTTwoUp = NULL;
	 mDrainagePipeTTwoUpFlood = NULL;
	 mDrainagePipeTTwoUpNONSelect = NULL;
	 mDrainagePipeTTwoUpMouseOver = NULL;
	 mDrainagePipeTTwoUpSelect = NULL;
	 mDrainagePipeTTwoDown = NULL;
	 mDrainagePipeTTwoDownFlood = NULL;
	 mDrainagePipeTTwoDownNONSelect = NULL;
	 mDrainagePipeTTwoDownMouseOver = NULL;
	 mDrainagePipeTTwoDownSelect = NULL;
	 mDrainagePipeTTwoLeft = NULL;
	 mDrainagePipeTTwoLeftFlood = NULL;
	 mDrainagePipeTTwoLeftNONSelect = NULL;
	 mDrainagePipeTTwoLeftMouseOver = NULL;
	 mDrainagePipeTTwoLeftSelect = NULL;

	 mDrainagePipeTThreeUp = NULL;
	 mDrainagePipeTThreeUpFlood = NULL;
	 mDrainagePipeTThreeUpNONSelect = NULL;
	 mDrainagePipeTThreeUpMouseOver = NULL;
	 mDrainagePipeTThreeUpSelect = NULL;
	 mDrainagePipeTThreeDown = NULL;
	 mDrainagePipeTThreeDownFlood = NULL;
	 mDrainagePipeTThreeDownNONSelect = NULL;
	 mDrainagePipeTThreeDownMouseOver = NULL;
	 mDrainagePipeTThreeDownSelect = NULL;
	 mDrainagePipeTThreeRight = NULL;
	 mDrainagePipeTThreeRightFlood = NULL;
	 mDrainagePipeTThreeRightNONSelect = NULL;
	 mDrainagePipeTThreeRightMouseOver = NULL;
	 mDrainagePipeTThreeRightSelect = NULL;

	 mDrainagePipeTFourUp = NULL;
	 mDrainagePipeTFourUpFlood = NULL;
	 mDrainagePipeTFourUpNONSelect = NULL;
	 mDrainagePipeTFourUpMouseOver = NULL;
	 mDrainagePipeTFourUpSelect = NULL;
	 mDrainagePipeTFourLeft = NULL;
	 mDrainagePipeTFourLeftFlood = NULL;
	 mDrainagePipeTFourLeftNONSelect = NULL;
	 mDrainagePipeTFourLeftMouseOver = NULL;
	 mDrainagePipeTFourLeftSelect = NULL;
	 mDrainagePipeTFourRight = NULL;
	 mDrainagePipeTFourRightFlood = NULL;
	 mDrainagePipeTFourRightNONSelect = NULL;
	 mDrainagePipeTFourRightMouseOver = NULL;
	 mDrainagePipeTFourRightSelect = NULL;

	 mDrainagePipeSquareUp = NULL;
	 mDrainagePipeSquareUpFlood = NULL;
	 mDrainagePipeSquareUpMouseOver = NULL;
	 mDrainagePipeSquareUpSelect = NULL;

	 mDrainagePipeSquareLeft = NULL;
	 mDrainagePipeSquareLeftFlood = NULL;
	 mDrainagePipeSquareLeftMouseOver = NULL;
	 mDrainagePipeSquareLeftSelect = NULL;

	 mDrainagePipeSquareDown = NULL;
	 mDrainagePipeSquareDownFlood = NULL;
	 mDrainagePipeSquareDownMouseOver = NULL;
	 mDrainagePipeSquareDownSelect = NULL;

	 mDrainagePipeSquareRight = NULL;
	 mDrainagePipeSquareRightFlood = NULL;
	 mDrainagePipeSquareRightMouseOver = NULL;
	 mDrainagePipeSquareRightSelect = NULL;

	 mChangeDrainagePipeVUpMouseOver = NULL;
	 mChangeDrainagePipeVUpSelect = NULL;
	 mChangeDrainagePipeVDownMouseOver = NULL;
	 mChangeDrainagePipeVDownSelect = NULL;

	 mChangeDrainagePipeHRightMouseOver = NULL;
	 mChangeDrainagePipeHRightSelect = NULL;
	 mChangeDrainagePipeHLeftMouseOver = NULL;
	 mChangeDrainagePipeHLeftSelect = NULL;

	 mChangeDrainagePipeCROneDownMouseOver = NULL;
	 mChangeDrainagePipeCROneDownSelect = NULL;
	 mChangeDrainagePipeCROneRightMouseOver = NULL;
	 mChangeDrainagePipeCROneRightSelect = NULL;

	 mChangeDrainagePipeCRTwoDownMouseOver = NULL;
	 mChangeDrainagePipeCRTwoDownSelect = NULL;
	 mChangeDrainagePipeCRTwoLeftMouseOver = NULL;
	 mChangeDrainagePipeCRTwoLeftSelect = NULL;

	 mChangeDrainagePipeCRThreeUpMouseOver = NULL;
	 mChangeDrainagePipeCRThreeUpSelect = NULL;
	 mChangeDrainagePipeCRThreeLeftMouseOver = NULL;
	 mChangeDrainagePipeCRThreeLeftSelect = NULL;

	 mChangeDrainagePipeCRFourUpMouseOver = NULL;
	 mChangeDrainagePipeCRFourUpSelect = NULL;
	 mChangeDrainagePipeCRFourRightMouseOver = NULL;
	 mChangeDrainagePipeCRFourRightSelect = NULL;

	 mChangeDrainagePipeTOneDownMouseOver = NULL;
	 mChangeDrainagePipeTOneDownSelect = NULL;
	 mChangeDrainagePipeTOneRightMouseOver = NULL;
	 mChangeDrainagePipeTOneRightSelect = NULL;
	 mChangeDrainagePipeTOneLeftMouseOver = NULL;
	 mChangeDrainagePipeTOneLeftSelect = NULL;

	 mChangeDrainagePipeTTwoDownMouseOver = NULL;
	 mChangeDrainagePipeTTwoDownSelect = NULL;
	 mChangeDrainagePipeTTwoUpMouseOver = NULL;
	 mChangeDrainagePipeTTwoUpSelect = NULL;
	 mChangeDrainagePipeTTwoLeftMouseOver = NULL;
	 mChangeDrainagePipeTTwoLeftSelect = NULL;

	 mChangeDrainagePipeTThreeDownMouseOver = NULL;
	 mChangeDrainagePipeTThreeDownSelect = NULL;
	 mChangeDrainagePipeTThreeUpMouseOver = NULL;
	 mChangeDrainagePipeTThreeUpSelect = NULL;
	 mChangeDrainagePipeTThreeRightMouseOver = NULL;
	 mChangeDrainagePipeTThreeRightSelect = NULL;


	 mChangeDrainagePipeTFourUpMouseOver = NULL;
	 mChangeDrainagePipeTFourUpSelect = NULL;
	 mChangeDrainagePipeTFourLeftMouseOver = NULL;
	 mChangeDrainagePipeTFourLeftSelect = NULL;
	 mChangeDrainagePipeTFourRightMouseOver = NULL;
	 mChangeDrainagePipeTFourRightSelect = NULL;


	 mChangeDrainagePipeSquareUpMouseOver = NULL;
	 mChangeDrainagePipeSquareUpSelect = NULL;
	 mChangeDrainagePipeSquareDownMouseOver = NULL;
	 mChangeDrainagePipeSquareDownSelect = NULL;
	 mChangeDrainagePipeSquareLeftMouseOver = NULL;
	 mChangeDrainagePipeSquareLeftSelect = NULL;
	 mChangeDrainagePipeSquareRightMouseOver = NULL;
	 mChangeDrainagePipeSquareRightSelect = NULL;




	mStructureInterface = NULL;
	mStructureInterfaceOn = NULL;

	mWaterTreatmentInterface = NULL;
	mHouseInterface = NULL;
	mDrainagePipeInterface = NULL;


	mStructureText = NULL;

	mHouseText = NULL;
	mWaterTreatmentText = NULL;
	mDrainagePipeText = NULL;

	mStructureSubText = NULL;


	mChangeStructureSelect = NULL;


	mStructureMenuMouseOver = NULL;
	mStructureMenuSelect = NULL;




	//DELETE SDL POINTS???????????
	mPosition.x = NULL;
	mPosition.y = NULL;

	

	//Action indicator variables
	mActionIndicator = NULL;
	mActionTrue = NULL;
	mActionFalse = NULL;







	//Pipe Menu

	mDrainageInterface = NULL;
	mDrainageText = NULL;

	mDrainageMenuSellText = NULL;
	mDrainageMenuToggleText = NULL;


	mPipeShopBackground = NULL;


	mPipeMenuMouseOver = NULL;
	mPipeMenuSelect = NULL;

	mPipeMenuBackground = NULL;
	mPipeMenuBackgroundHighlight = NULL;
	mPipeMenuBackgroundSelect = NULL;

	mPipeMenuText = NULL;






	 mContaminantMenuPosition.x = NULL;
	 mContaminantMenuPosition.y = NULL;

	 mContaminantMenuBackground = NULL;
	 mContaminantMenuBackgroundHighlight = NULL;
	 mContaminantMenuBackgroundSelect = NULL;




	 mSewage = NULL;
	 mFilter = NULL;

	 mChangeFilterMouseOver = NULL;
	 mChangeFilterSelect = NULL;

	 mFilterPosition.x = NULL;
	 mFilterPosition.y = NULL;

	 mPower = NULL;
	 mGenerator = NULL;

	 mChangeGeneratorMouseOver = NULL;
	 mChangeGeneratorSelect = NULL;

	 mGeneratorPosition.x = NULL;
	 mGeneratorPosition.y = NULL;


	 mPowerMenuPosition.x = NULL;
	 mPowerMenuPosition.y = NULL;

	 mPowerMenuBackground = NULL;
	 mPowerMenuBackgroundHighlight = NULL;
	 mPowerMenuBackgroundSelect = NULL;

}


InteractionMap::LEVEL_STATES InteractionMap::State() {

	return mCurrentState;

}

int InteractionMap::RandomVertical(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 15);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int InteractionMap::RandomHorizontal(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 24);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}




int InteractionMap::RandomCount(int count) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, (count - 1));

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}



int InteractionMap::RandomFiftyFifty(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 1);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}



void InteractionMap::LoadTileMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mTileMap[row][column] = arr[row][column];
		}
	}

}


void InteractionMap::LoadContourMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mContourMap[row][column] = arr[row][column];
		}
	}

}


void InteractionMap::LoadCarMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mCarMap[row][column] = arr[row][column];
		}
	}

}


void InteractionMap::LoadStructureMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mStructureMap[row][column] = arr[row][column];
		}
	}

}

void InteractionMap::LoadUnitMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mUnitMap[row][column] = arr[row][column];
		}
	}

}


void InteractionMap::LoadUnitValueMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mUnitValueMap[row][column] = arr[row][column];
		}
	}

}




void InteractionMap::LoadPipeMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mPipeMap[row][column] = arr[row][column];
		}
	}

}



                                                                                                                                                                                                                 
void InteractionMap::LoadFloodValueMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{

			mFloodValueMap[row][column] = arr[row][column];

			//int value = mFloodValueMap[row][column];

			//if (mPipeMap[row][column] > 29 && mPipeMap[row][column] < 40) {

				// (value > 0) {

					//mFloodNotDrained = false;
					//HandleDrain(value, row, column);

				//


			//}


		}
	}

}






void InteractionMap::LoadContaminantValueMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mContaminantValueMap[row][column] = arr[row][column];
		}
	}

}





void InteractionMap::LoadChargeValueMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mContaminantValueMap[row][column] = arr[row][column];
		}
	}

}



void InteractionMap::LoadValueMovementMap() {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mValueMovementMap[row][column] = 0;
		}
	}

}



void InteractionMap::DrawContourMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Structure Type Value
			int contourTypeValue = mContourMap[row][column];


			switch (contourTypeValue)
			{
			case 0:

				mContour = NULL;
				break;

			case 1:

				mContour = mElevationOneLeft;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;


			case 2:

				mContour = mElevationOneRight;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 3:

				mContour = mElevationOneTop;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 4:

				mContour = mElevationOneBottom;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 5:

				mContour = mElevationOneLeftTopCorner;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 6:

				mContour = mElevationOneLeftBottomCorner;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 7:

				mContour = mElevationOneRightTopCorner;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 8:

				mContour = mElevationOneRightBottomCorner;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 9:

				mContour = mElevationOneUShapeLeft;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 10:

				mContour = mElevationOneUShapeRight;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 11:

				mContour = mElevationOneUShapeTop;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 12:

				mContour = mElevationOneUShapeBottom;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 13:

				mContour = mElevationOneVerticalTunnel;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 14:

				mContour = mElevationOneHorizontalTunnel;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;

			case 15:

				mContour = mElevationOneSquare;
				mContour->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mContour->Render();
				break;


			default:
				break;
			}











		}
	}
}









void InteractionMap::DrawStructureMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Structure Type Value
			int structureTypeValue = mStructureMap[row][column];


			switch (structureTypeValue)
			{
			case 0:

				mPipe = NULL;
				break;

			case 1:

				mPipe = mHouse;
				mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mPipe->Render();
				break;


			default:
				break;
			}











		}
	}
}











void InteractionMap::DrawPipeMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Structure Type Value
			int pipeTypeValue = mPipeMap[row][column];

			//Structure Value
			int floodValue = mFloodValueMap[row][column];

			//Structure Type Value
			int structureValue = mStructureMap[row][column];

			switch (pipeTypeValue)
			{
			case 0:

				mPipe = NULL;
				break;

			case 1:

				if (floodValue != 0) {

					mPipe = mDrainagePipeVUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeVUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 2:

				if (floodValue != 0) {

					mPipe = mDrainagePipeVDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeVDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 3:

				if (floodValue != 0) {

					mPipe = mDrainagePipeHRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeHRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;
				}

			case 4:

				if (floodValue != 0) {

					mPipe = mDrainagePipeHLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeHLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;
				}









			case 5:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCROneDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCROneDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}



			case 6:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCROneRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCROneRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}








			case 7:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRTwoDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRTwoDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}



			case 8:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRTwoLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRTwoLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}




			case 9:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRThreeUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRThreeUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}



			case 10:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRThreeLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRThreeLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 11:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRFourUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRFourUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 12:

				if (floodValue != 0) {

					mPipe = mDrainagePipeCRFourRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeCRFourRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 13:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTOneDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTOneDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}



			case 14:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTOneRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTOneRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 15:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTOneLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTOneLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 16:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTTwoDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTTwoDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 17:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTTwoUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTTwoUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 18:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTTwoLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTTwoLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}




			case 19:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTThreeUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTThreeUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 20:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTThreeDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTThreeDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 21:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTThreeRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTThreeRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}



			case 22:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTFourLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTFourLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 23:

				if (floodValue != 0) {

					mPipe = mDrainagePipeTFourUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTFourUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 24:


				if (floodValue != 0) {

					mPipe = mDrainagePipeTFourRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeTFourRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 25:

				if (floodValue != 0) {

					mPipe = mDrainagePipeSquareUpFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeSquareUp;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}

			case 26:

				if (floodValue != 0) {

					mPipe = mDrainagePipeSquareDownFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeSquareDown;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 27:

				if (floodValue != 0) {

					mPipe = mDrainagePipeSquareLeftFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeSquareLeft;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}


			case 28:

				if (floodValue != 0) {

					mPipe = mDrainagePipeSquareRightFlood;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}
				else {

					mPipe = mDrainagePipeSquareRight;
					mPipe->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mPipe->Render();
					break;

				}




			default:
				break;
			}



		


	




				

				if (floodValue != 0) {

					if (floodValue > 0) {

						mFloodLevelOne = mFloodLevelOneAnimation;
						mFloodLevelOne->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
						mFloodLevelOne->Render();
					}

					if (floodValue > 10) {

						mFloodLevelTwo = mFloodLevelTwoAnimation;
						mFloodLevelTwo->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
						mFloodLevelTwo->Render();
					}

					if (floodValue > 15) {

						mFloodLevelThree = mFloodLevelThreeAnimation;
						mFloodLevelThree->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
						mFloodLevelThree->Render();



						if (structureValue == 1) {
							
							mHouseFloodedLose = true;

						}

						 
					}

				}


	

			

		}
	}
}


void InteractionMap::DrawContaminantMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Structure Type Value
			int contaminantTypeValue = mContaminantValueMap[row][column];


			switch (contaminantTypeValue)
			{
			case 0:

				mLitter = NULL;
				break;

			case 1:

				mLitter = mTrashCan;
				mLitter->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mLitter->Render();
				break;


			default:
				break;
			}











		}
	}
}










void InteractionMap::DrawMovementTiles() {

	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{

			mStructurePositionTargetX = row;
			mStructurePositionTargetY = column;

			int tile = mTileMap[row][column];

			if (mPipeMap[row][column] != 0) {

				tile = 0;
			}

			if (mStructurePositionTargetX == mStructurePositionSelectX && mStructurePositionTargetY == mStructurePositionSelectY) {

				tile = 50;
			}


			int modifier = 5;

			if (

				!(mStructurePositionTargetX < (mStructurePositionSelectX - modifier)) &&
				!(mStructurePositionTargetX > (mStructurePositionSelectX + modifier)) &&
				!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier)) &&
				!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier)) &&
				!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier) && mStructurePositionTargetX < mStructurePositionSelectX - modifier) &&
				!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier) && mStructurePositionTargetX > mStructurePositionSelectX + modifier) &&
				!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier) && mStructurePositionTargetX > mStructurePositionSelectX + modifier) &&
				!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier) && mStructurePositionTargetX < mStructurePositionSelectX - modifier)

				)



			{





				switch (tile)
				{
				case 0:

					mActionIndicator = mActionFalse;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;

				case 1:

					mActionIndicator = mActionTrue;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;

				case 2:

					mActionIndicator = mActionTrue;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;
				case 50:

					break;

				default:
					break;

				}
				

			}

		}

	}

}

void InteractionMap::DrawActionTiles() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{

			mStructureActionTargetX = row;
			mStructureActionTargetY = column;

			int unit = mPipeMap[row][column];

			//int selectrow = mStructurePositionSelectX;
			//int selectcolumn = mStructurePositionSelectY;

			if (

				(mStructureActionTargetY == mStructurePositionSelectY && mStructureActionTargetX == (mStructurePositionSelectX - 1)) ||
				(mStructureActionTargetY == mStructurePositionSelectY && mStructureActionTargetX == (mStructurePositionSelectX + 1)) ||
				(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX) ||
				(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX) ||
				(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX - 1) ||
				(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX + 1) ||
				(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX + 1) ||
				(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX - 1)

				)



			{
				switch (unit)
				{
				case 0:

					mActionIndicator = mActionFalse;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;

				case 1:

					mActionIndicator = mActionFalse;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;

				case 2:

					mActionIndicator = mActionTrue;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;
				case 3:

					mActionIndicator = mActionTrue;
					mActionIndicator->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mActionIndicator->Render();
					break;
				default:
					break;

				}

			}

		}

	}

}

void InteractionMap::HandleRainSpawn() {


	mRainSpawnTimer += mTimer->DeltaTime();



	while (mRainSpawnTimer >= mRainSpawnTimerInterval) {

		mRainPositionY = RandomVertical();
		mRainPositionX = RandomHorizontal();

		//mRainTwoPositionY = RandomVertical();
		//mRainTwoPositionX = RandomHorizontal();

		//printf("Raining at ");
		//printf(" %d ", mRainPositionY);
		//printf(" %d \n", mRainPositionX);


		if (mRainPositionY < 15 && mRainPositionX < 25) {

			RainEffect::Release();
			mRaindrops = RainEffect::Instance(mRainPositionY, mRainPositionX);
			mRaindrops->Scroll(true);

			//mRaindropsTwo = RainEffect::Instance(mRainTwoPositionY, mRainTwoPositionX);
			//mRaindrops->Scroll(true);

			mIsRaining = true;
			mRainSpawnTimer = 0.0f;


		}
	


	}
	
	if (mRainSpawnTimer == 0.0f) {

		mFloodReduce = true;
		//printf("wtf");
	}

	mRaindrops->Update();
	//mRaindropsTwo->Update();

	
}



void InteractionMap::HandleFloodValue() {

	mWaterMovementTimer += mTimer->DeltaTime();

	//THE RAIN ITSELF INCREASING FLOOD VALUE
	//NEEDS CORNER ADJUSTMENT FILTER
	if (mIsRaining == true) {

		if (mRainPositionY && mRainPositionX) {



			mFloodValueMap[mRainPositionX][mRainPositionY] = (mFloodValueMap[mRainPositionX][mRainPositionY] + 1);
			mFloodValueMap[mRainPositionX - 1][mRainPositionY + 1] = (mFloodValueMap[mRainPositionX - 1][mRainPositionY + 1] + 1);
			mFloodValueMap[mRainPositionX - 2][mRainPositionY + 2] = (mFloodValueMap[mRainPositionX - 2][mRainPositionY + 2] + 1);
			mFloodValueMap[mRainPositionX - 1][mRainPositionY] = (mFloodValueMap[mRainPositionX - 1][mRainPositionY] + 1);
			mFloodValueMap[mRainPositionX - 2][mRainPositionY] = (mFloodValueMap[mRainPositionX - 2][mRainPositionY] + 1);
			mFloodValueMap[mRainPositionX][mRainPositionY + 1] = (mFloodValueMap[mRainPositionX][mRainPositionY + 1] + 1);
			mFloodValueMap[mRainPositionX][mRainPositionY + 2] = (mFloodValueMap[mRainPositionX][mRainPositionY + 2] + 1);

			mFloodValueMap[mRainPositionX - 2][mRainPositionY + 1] = (mFloodValueMap[mRainPositionX - 2][mRainPositionY + 1] + 1);
			mFloodValueMap[mRainPositionX - 1][mRainPositionY + 2] = (mFloodValueMap[mRainPositionX - 1][mRainPositionY + 2] + 1);

		}

		/*
		if (mRainTwoPositionY && mRai nTwoPositionX) {

			mFloodValueMap[mRainTwoPositionX][mRainTwoPositionY]++;
			mFloodValueMap[mRainTwoPositionX - 1][mRainTwoPositionY + 1]++;
			mFloodValueMap[mRainTwoPositionX - 2][mRainTwoPositionY + 2]++;
			mFloodValueMap[mRainTwoPositionX - 1][mRainTwoPositionY]++;
			mFloodValueMap[mRainTwoPositionX - 2][mRainTwoPositionY]++;
			mFloodValueMap[mRainTwoPositionX][mRainTwoPositionY + 1]++;
			mFloodValueMap[mRainTwoPositionX][mRainTwoPositionY + 2]++;

			mFloodValueMap[mRainTwoPositionX - 2][mRainTwoPositionY + 1]++;
			mFloodValueMap[mRainTwoPositionX - 1][mRainTwoPositionY + 2]++;



		}
		*/

		//mIsRaining == false;
		//int asd = mFloodValueMap[mRainPositionX][mRainPositionY];
		//printf("%d", mRainPositionX);

	}

	//HANDLE SHIFTING WATER AND CONTAMINANTS AROUND

	//FRESH MOVEMENT MAP TO KEEP TRACK OF WHAT TILES HAVE HAD MOVEMENT PERFORMED ON THEM
	LoadValueMovementMap();


	while (mWaterMovementTimer >= mWaterMovementTimerInterval) {


		for (int row = 0; row < 25; row++)
		{

			for (int column = 0; column < 16; column++)
			{

				//EXCLUDE THE RAIN POSITION
				if (
					(row != mRainPositionX && column != mRainPositionY) ||
					(row != mRainPositionX - 1 && column != mRainPositionY + 1) ||
					(row != mRainPositionX - 2 && column != mRainPositionY + 2) ||
					(row != mRainPositionX - 1 && column != mRainPositionY) ||
					(row != mRainPositionX - 2 && column != mRainPositionY) ||
					(row != mRainPositionX && column != mRainPositionY + 1) ||
					(row != mRainPositionX && column != mRainPositionY) + 2 ||
					(row != mRainPositionX - 1 && column != mRainPositionY + 1) ||
					(row != mRainPositionX - 2 && column != mRainPositionY + 2)

					) {

					//CHECK IF TILE HAS HAD VALUE ALREADY SHIFTED TO IT, THIS AVOIDS MULTIPLE TILE MOVEMENTS
					if (mValueMovementMap[row][column] == 0) {


						//CHECK IF TILE HAS FLOOD
						if (mFloodValueMap[row][column] > 0) {


							//CONDITION THAT RESETS LOOP AND PICKS A NEW DIRECTION IF CHOSEN SIDE HAS A CLIFF
							bool cliffTileCheck = false;

							do {

								//PICK A RANDOM SIDE
								int WaterMovementCount = 4;
								int WaterMovementSelect = RandomCount(WaterMovementCount);
								int cliffvalue = mContourMap[row][column];

								printf("%i            ", cliffvalue);
								printf("%i          \n", WaterMovementSelect);

								if (cliffvalue == 15)
									break;

								//RIGHT SIDE
								if (WaterMovementSelect == 0) {

									//CONTOUR VALUES THAT HAVE RIGHT CLIFF TILE
									if (cliffvalue == 2 || cliffvalue == 7 || cliffvalue == 8 || cliffvalue == 9 || cliffvalue == 11 || cliffvalue == 12 || cliffvalue == 13 || cliffvalue == 15) {

										continue;

									}

									printf("bump \n");

								    //REMOVE ONE FLOOD VALUE FROM CURRENT TILE
									mFloodValueMap[row][column] = mFloodValueMap[row][column] - 1;

									//INCREMENT TARGET TILE FLOOD VALUE, MARK TARGET AS A TILE THAT A MOVE HAVE TAKEN PLACE IN, SWITCH THE CLIFF CONDITION TO EXIT LOOP TO TRUE
									mFloodValueMap[row + 1][column]++;
									mValueMovementMap[row + 1][column] = 1;
									cliffTileCheck = true;

									//CHECK FOR A CONTAMINANT TO MOVE ALSO BEFORE EXITING
									if (mContaminantValueMap[row][column] > 0) {

										//IF THERE IS A CONTAMINANT, REDUCE A CONTAMINANT VALUE FROM CURRENT TILE AND INCREMENT TARGET TILE
										mContaminantValueMap[row][column] = mContaminantValueMap[row][column] - 1;
										mContaminantValueMap[row + 1][column]++;

									}


									



								}
								//LEFT SIDE
								else if (WaterMovementSelect == 1) {

									if (cliffvalue == 1 || cliffvalue == 5 || cliffvalue == 6 || cliffvalue == 10 || cliffvalue == 11 || cliffvalue == 12 || cliffvalue == 13 || cliffvalue == 15) {

										continue;

									}

									printf("bump \n");
									//REMOVE ONE FLOOD VALUE FROM CURRENT TILE
									mFloodValueMap[row][column] = mFloodValueMap[row][column] - 1;

									mFloodValueMap[row - 1][column]++;
									mValueMovementMap[row - 1][column] = 1;
									cliffTileCheck = true;



									if (mContaminantValueMap[row][column] > 0) {


										mContaminantValueMap[row][column] = mContaminantValueMap[row][column] - 1;
										mContaminantValueMap[row - 1][column]++;

									}



									

								}
								//TOP SIDE
								else if (WaterMovementSelect == 2) {

									if (cliffvalue == 3 || cliffvalue == 5 || cliffvalue == 7 || cliffvalue == 9 || cliffvalue == 10 || cliffvalue == 12 || cliffvalue == 14 || cliffvalue == 15) {

										continue;

									}

									printf("bump \n");

									//REMOVE ONE FLOOD VALUE FROM CURRENT TILE
									mFloodValueMap[row][column] = mFloodValueMap[row][column] - 1;

										mFloodValueMap[row][column + 1]++;
										mValueMovementMap[row][column + 1] = 1;
										cliffTileCheck = true;



										if (mContaminantValueMap[row][column] > 0) {


											mContaminantValueMap[row][column] = mContaminantValueMap[row][column] - 1;
											mContaminantValueMap[row][column + 1]++;

										}

									




								}
								//BOTTOM SIDE
								else if (WaterMovementSelect == 3) {


									if (cliffvalue == 4 || cliffvalue == 6 || cliffvalue == 8 || cliffvalue == 9 || cliffvalue == 10 || cliffvalue == 11 || cliffvalue == 14 || cliffvalue == 15) {

										continue;

									}

									printf("bump \n");
									//REMOVE ONE FLOOD VALUE FROM CURRENT TILE
									mFloodValueMap[row][column] = mFloodValueMap[row][column] - 1;

									mFloodValueMap[row][column - 1]++;
									mValueMovementMap[row][column - 1] = 1;
									cliffTileCheck = true;

									if (mContaminantValueMap[row][column] > 0) {


										mContaminantValueMap[row][column] = mContaminantValueMap[row][column] - 1;
										mContaminantValueMap[row][column - 1]++;

										}


									


								}



							}
							while (cliffTileCheck == false);



						}


					}



				}

			}
		}

		mWaterMovementTimer = 0.0f;


	}


}


void InteractionMap::HandleHouseSpawn() {

	mHouseSpawnTimer += mTimer->DeltaTime();

	mUnitNotPlaced = false;

	if (mHouseSpawnTimer >= mHouseSpawnTimerInterval) {





		while (mUnitNotPlaced == false) {

			int randomv = RandomVertical();
			int randomh = RandomHorizontal();



			if (mStructureMap[randomv][randomh] == 0) {

				if (mTileMap[randomv][randomh] != 0 && mTileMap[randomv][randomh] != 3 && mTileMap[randomv][randomh] != 4 && mTileMap[randomv][randomh] != 5) {

					mStructureMap[randomv][randomh] = 1;
					//mFloodValueMap[randomv][randomh] = 1;
					mUnitNotPlaced = true;

				}

			}

		}



		
		mHouseSpawnTimer = 0.0f;

	}

}



void InteractionMap::HandleHouseFloodLoss() {


	//warn player first


	//fuck em
	if (mHouseFloodedLose == true)
	{


		mGameOverTimer += mTimer->DeltaTime();

		if (mGameOverTimer >= mGameOverDelay) {

			mCurrentState = gameover;

		}

	}


}




void InteractionMap::HandleCarSpawn() {

	mCarSpawnTimer += mTimer->DeltaTime();

	//printf("%f", mCarSpawnTimer);


	if (mCar)
		mCar->Update();

	if (mCarTwo)
		mCarTwo->Update();

	if (mCarSpawnTimer >= mCarSpawnTimerInterval) {


		//if (mCarSpawned == false) {

			Car::Release();	

			std::vector<int> matchingIndices;
			std::vector<int> matchingRow;
			std::vector<int> matchingColumn;


			int cartilecount = 0;

			for (int row = 0; row < 25; row++)
			{
				for (int column = 0; column < 16; column++)
				{

					int carvalue = mCarMap[row][column];


					if (carvalue > 0) {


						matchingIndices.push_back(mCarMap[row][column]);
						matchingRow.push_back(row);
						matchingColumn.push_back(column);

						cartilecount++;



					}

				}
			}



			int index = RandomCount(cartilecount);

			int carValue = matchingIndices[index];
			int carRow = matchingRow[index];
			int carColumn = matchingColumn[index];







		mCar = Car::Instance(carValue, carRow, carColumn);




		//LITTERING 

		if (carValue == 1) {

			//Up
			//Random variable of Y, then random fifty fifty to choose an adjacent direction
			int component = RandomVertical();
			int adjacentTile = RandomFiftyFifty();

			if (adjacentTile == 0) {

				mLitterRow = carRow + 1;

			}
			else {

				mLitterRow = carRow - 1;

			}
	

			mLitterColumn = component;


				
			mDropTime =  (component * 0.4);







		}
		else if (carValue == 2) {
			
			//Left


			
		}
		else if (carValue == 3) {

			//Down

		}
		else if (carValue == 4) {

			//Right

		}






		//CAR TWo


		std::vector<int> matchingIndicesTwo;
		std::vector<int> matchingRowTwo;
		std::vector<int> matchingColumnTwo;


		int cartilecountTwo = 0;

		for (int row = 0; row < 25; row++)
		{
			for (int column = 0; column < 16; column++)
			{

				int carvalueTwo = mCarMap[row][column];


				if (carvalueTwo > 0) {


					matchingIndicesTwo.push_back(mCarMap[row][column]);
					matchingRowTwo.push_back(row);
					matchingColumnTwo.push_back(column);

					cartilecountTwo++;



				}

			}
		}



		int indexTwo = RandomCount(cartilecountTwo);

		int carValueTwo = matchingIndicesTwo[indexTwo];
		int carRowTwo = matchingRowTwo[indexTwo];
		int carColumnTwo = matchingColumnTwo[indexTwo];


		




		mCarTwo = Car::Instance(carValueTwo, carRowTwo, carColumnTwo);




		//LITTERING 

		if (carValueTwo == 1) {

			//Up
			//Random variable of Y, then random fifty fifty to choose an adjacent direction
			int componentTwo = RandomVertical();
			int adjacentTileTwo = RandomFiftyFifty();

			if (adjacentTileTwo == 0) {

				mLitterRowTwo = carRowTwo + 1;

			}
			else {

				mLitterRowTwo = carRowTwo - 1;

			}


			mLitterColumnTwo = componentTwo;



			mDropTimeTwo = (componentTwo * 0.4);







		}
		else if (carValueTwo == 2) {

			//Left



		}
		else if (carValue == 3) {

			//Down

		}
		else if (carValue == 4) {

			//Right

		}










		mCarSpawnTimer = 0.0f;






	}





	//Car travels one tile in ~ 0.04 time units  * 0.04;
	if (mCarSpawnTimer > mDropTime) {

		mContaminantValueMap[mLitterRow][mLitterColumn] = 1;


	};

	if (mCarSpawnTimer > mDropTimeTwo) {

		mContaminantValueMap[mLitterRowTwo][mLitterColumnTwo] = 1;


	};


	

	

}



void InteractionMap::HandleDrain() {

	//mDrainTimer += mTimer->DeltaTime();

	//mFloodNotDrained = false;

	//if (mDrainTimer >= mDrainTimerInterval) {

		//printf("\n test");


		//if (mFloodNotDrained == false) {


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			//Check for flood value
			if (mFloodValueMap[row][column] > 0) {



				//Vertical Pipe Up
				if (mPipeMap[row][column] == 1) {




					//Pipe Type Value
					int mPipeTypeValue = mPipeMap[row][column];

					int targetrow = row;
					int targetcolumn = column + 1;


					if (mPipeMap[targetrow][targetcolumn] != 3 && mPipeMap[targetrow][targetcolumn] != 4 && mPipeMap[targetrow][targetcolumn] != 9 && mPipeMap[targetrow][targetcolumn] != 10 && mPipeMap[targetrow][targetcolumn] != 11 && mPipeMap[targetrow][targetcolumn] != 21 && mPipeMap[targetrow][targetcolumn] != 22 && mPipeMap[targetrow][targetcolumn] != 23 ) {

						mFloodValueMap[targetrow][targetcolumn]++;
						mFloodValueMap[row][column]--;


						int contaminants = mContaminantValueMap[row][column];

						if (contaminants > 0 ) {


							mContaminantValueMap[targetrow][targetcolumn]++;
							mContaminantValueMap[row][column]--;

						}




					}




				}

				
				//Vertical Pipe Up
				if (mPipeMap[row][column] == 1) {




					//Pipe Type Value
					int mPipeTypeValue = mPipeMap[row][column];

					int targetrow = row;
					int targetcolumn = column + 1;


					if (mPipeMap[targetrow][targetcolumn] != 3 && mPipeMap[targetrow][targetcolumn] != 4 && mPipeMap[targetrow][targetcolumn] != 9 && mPipeMap[targetrow][targetcolumn] != 10 && mPipeMap[targetrow][targetcolumn] != 11 && mPipeMap[targetrow][targetcolumn] != 21 && mPipeMap[targetrow][targetcolumn] != 22 && mPipeMap[targetrow][targetcolumn] != 23 ) {

						mFloodValueMap[targetrow][targetcolumn]++;
						mFloodValueMap[row][column]--;


						int contaminants = mContaminantValueMap[row][column];

						if (contaminants > 0 ) {


							mContaminantValueMap[targetrow][targetcolumn]++;
							mContaminantValueMap[row][column]--;

						}




					}




				}




				//Vertical Pipe Up
				if (mPipeMap[row][column] == 2) {




					//Pipe Type Value
					int mPipeTypeValue = mPipeMap[row][column];

					int targetrow = row;
					int targetcolumn = column - 1;


					if (mPipeMap[targetrow][targetcolumn] != 3 && mPipeMap[targetrow][targetcolumn] != 4 && mPipeMap[targetrow][targetcolumn] != 5 && mPipeMap[targetrow][targetcolumn] != 6 && mPipeMap[targetrow][targetcolumn] != 7 && mPipeMap[targetrow][targetcolumn] != 13 && mPipeMap[targetrow][targetcolumn] != 14 && mPipeMap[targetrow][targetcolumn] != 15) {

						mFloodValueMap[targetrow][targetcolumn]++;
						mFloodValueMap[row][column]--;


						int contaminants = mContaminantValueMap[row][column];

						if (contaminants > 0) {


							mContaminantValueMap[targetrow][targetcolumn]++;
							mContaminantValueMap[row][column]--;

						}




					}




				}
















			}




		}


	}


}




void InteractionMap::HandleTileSelect() {

	//If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//printf("%d \n", x);
		//printf("%d \n", y);

		int xValue = Graphics::Instance()->SCREEN_WIDTH * 9 / 10 - TILE_SELECT_WIDTH;

		int yValue = Graphics::Instance()->SCREEN_HEIGHT * 7 / 10 - TILE_SELECT_HEIGHT;


		bool mTileSelect = false;

		for (int row = 0; row < 25; row++)
		{


			for (int column = 0; column < 16; column++)
			{


				if (x < 840 && x > 640 && y < 883 && y > 720) {

					break;
				}

				int horizontal = row * 34;
				int vertical = column * 34;

				//Check if mouse is in button
				bool inside = true;


				if (mTileSelect == true) {
					break;
				}

				//Mouse is left of the button
				if (x < mTileHorizontal - TILE_SELECT_WIDTH - horizontal)
				{

					inside = false;

				}
				//Mouse is right of the button
				else if (x > mTileHorizontal + TILE_SELECT_WIDTH - horizontal)
				{

					inside = false;

				}
				//Mouse above the button
				else if (y < mTileVertical - TILE_SELECT_HEIGHT - vertical)
				{

					inside = false;

				}
				//Mouse below the button
				else if (y > mTileVertical + TILE_SELECT_HEIGHT - vertical)
				{

					inside = false;


				}

				if (inside == true) {

					//Mouse is inside tile, change select variable to True; change loop break variable (mTileselect) to True 
					mChangeTileSelect = true;
					mTileSelect = true;

					//Flood Value
					int floodvalue = mFloodValueMap[row][column] / 2;
					int contaminantvalue = mContaminantValueMap[row][column];
					//printf("%d", value);

					//std::string str = std::to_string(value);
					//mStructurePointValue = new Scoreboard();
					//mStructurePointValue->Parent(this);
					//mStructurePointValue->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					//mStructurePointValue->Scoreboard::Score(value);
					//mStructurePointValue->Render();

					mFloodValue = new Scoreboard();
					mFloodValue->Parent(this);
					mFloodValue->Pos(Vector2(785, 885));
					mFloodValue->Scoreboard::Score(floodvalue);
					//mStructurePointValue->Render();

					mFloodLabelText = new Texture("Flood Level", "unispace.ttf", 12, { 72, 31, 228 });
					mFloodLabelText->Parent(this);
					mFloodLabelText->Pos(Vector2(785, 865));
					//mStructurePointValue->Render();


					mContaminantValue = new Scoreboard();
					mContaminantValue->Parent(this);
					mContaminantValue->Pos(Vector2(945, 885));
					mContaminantValue->Scoreboard::Score(contaminantvalue);
					//mStructurePointValue->Render();

					mContaminantLabelText = new Texture("Contaminants", "unispace.ttf", 12, { 72, 31, 228 });
					mContaminantLabelText->Parent(this);
					mContaminantLabelText->Pos(Vector2(945, 865));



					mTileHighlight->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
					mTileHighlightOn = true;

					int tileValue = mTileMap[row][column];

					switch (tileValue)
					{
					case 0:
						mTileText = mWaterText;
						break;
					case 1:
						mTileText = mDirtText;
						break;
					case 2:
						mTileText = mGrassText;
						break;
					case 3:
						mTileText = mStreetText;
						break;
					case 4:
						mTileText = mStreetText;
						break;
					case 5:
						mTileText = mStreetText;
						break;
					default:
						break;
					}



					switch (tileValue)
					{
					case 0:
						mTileInterfaceTexture = mWaterInterfaceTexture;
						break;
					case 1:
						mTileInterfaceTexture = mDirtInterfaceTexture;
						break;
					case 2:
						mTileInterfaceTexture = mGrassInterfaceTexture;
						break;
					case 3:
						mTileInterfaceTexture = mStreetInterfaceTexture;
						break;
					case 4:
						mTileInterfaceTexture = mStreetInterfaceTexture;
						break;
					case 5:
						mTileInterfaceTexture = mStreetInterfaceTexture;
						break;
					default:
						break;
					}

					


				}
				else {
					mChangeTileSelect = false;

				}






			}


		}

	}
}

/*
void InteractionMap::HandleMenuSelect(int x, int y) {


	//MOUSEOVER FOR EACH BUTTON IS FIRST, THEN SIMILARLY BUTTON SELECTION IS NEXT

	//MOUSEOVER FOR BUTTONS BEGINS HERE

	//Get mouse position
	//int x, y;
	//SDL_GetMouseState(&x, &y);



	//MOVEMENT BUTTON

		//Check if mouse is in button
	bool insideunitmenumovement = true;

	//Mouse is left of the button
	if (x < mStructureMenuMovementPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenumovement = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuMovementPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenumovement = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuMovementPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenumovement = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuMovementPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenumovement = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenumovement == true) {

			//mStructureSelect = true;
			mChangeStructureMenuMovementMouseOver = true;

		}
		else {

			mChangeStructureMenuMovementMouseOver = false;

		}
	}



	//ACTION BUTTON

	//Check if mouse is in button
	bool insideunitmenuaction = true;

	//Mouse is left of the button
	if (x < mStructureMenuActionPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuaction = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuActionPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuaction = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuActionPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuaction = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuActionPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuaction = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenuaction == true) {

			mChangeStructureMenuActionMouseOver = true;

		}
		else {

			mChangeStructureMenuActionMouseOver = false;

		}
	}


	//ITEM BUTTON

	//Check if mouse is in button
	bool insideunitmenuitem = true;

	//Mouse is left of the button
	if (x < mStructureMenuItemPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuitem = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuItemPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuitem = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuItemPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuitem = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuItemPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuitem = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenuitem == true) {

			mChangeStructureMenuItemMouseOver = true;

		}
		else {

			mChangeStructureMenuItemMouseOver = false;

		}
	}

	//STATUS BUTTON

	//Check if mouse is in button
	bool insideunitmenustatus = true;

	//Mouse is left of the button
	if (x < mStructureMenuStatusPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenustatus = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuStatusPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenustatus = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuStatusPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenustatus = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuStatusPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenustatus = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenustatus == true) {

			mChangeStructureMenuStatusMouseOver = true;

		}
		else {

			mChangeStructureMenuStatusMouseOver = false;

		}
	}
	//BUTTON MOUSE OVER ENDS HERE


	//BUTTON SELECTION BEGINS HERE


	//If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		//int x, y;
		//SDL_GetMouseState(&x, &y);

		//Check Structure Menu Mouseover





		//Check Structure Menu Selection

		if (mChangeStructureSelect == true) {


			//MOVEMENT BUTTON

			//Check if mouse is in button
			bool insideunitmenumovement = true;

			//Mouse is left of the button
			if (x < mStructureMenuMovementPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenumovement = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuMovementPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenumovement = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuMovementPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenumovement = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuMovementPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenumovement = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenumovement == true) {

					//mStructureSelect = true;
					mChangeStructureMenuMovementSelect = true;

				}
				else {

					mChangeStructureMenuMovementSelect = false;

				}
			}



			//ACTION BUTTON

			//Check if mouse is in button
			bool insideunitmenuaction = true;

			//Mouse is left of the button
			if (x < mStructureMenuActionPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuaction = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuActionPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuaction = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuActionPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuaction = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuActionPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuaction = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenuaction == true) {

					mChangeStructureMenuActionSelect = true;

				}
				else {

					mChangeStructureMenuActionSelect = false;

				}
			}


			//ITEM BUTTON

			//Check if mouse is in button
			bool insideunitmenuitem = true;

			//Mouse is left of the button
			if (x < mStructureMenuItemPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuitem = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuItemPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuitem = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuItemPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuitem = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuItemPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuitem = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenuitem == true) {

					mChangeStructureMenuItemSelect = true;

				}
				else {

					mChangeStructureMenuItemSelect = false;

				}
			}

			//STATUS BUTTON

			//Check if mouse is in button
			bool insideunitmenustatus = true;

			//Mouse is left of the button
			if (x < mStructureMenuStatusPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenustatus = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuStatusPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenustatus = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuStatusPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenustatus = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuStatusPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenustatus = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenustatus == true) {

					mChangeStructureMenuStatusSelect = true;

				}
				else {

					mChangeStructureMenuStatusSelect = false;

				}
			}






		}
		//BUTTON SELECTION ENDS HERE
	}

}
*/

void InteractionMap::HandlePipeSelect() {

	//If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {


		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check Structure Selection
		bool drainageSelect = false;





		for (int row = 0; row < 25; row++)
		{

			for (int column = 0; column < 16; column++)
			{

				if (x < 840 && x > 640 && y < 883 && y > 720) {

					break;
				}

				int horizontal = row * 34;
				int vertical = column * 34;

				//Check if mouse is in button
				bool inside = true;

				//Mouse is left of the button
				if (x < mPosition.x - SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse is right of the button
				else if (x > mPosition.x + SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse above the button
				else if (y < mPosition.y - SELECT_HEIGHT - vertical)
				{
					inside = false;
				}
				//Mouse below the button
				else if (y > mPosition.y + SELECT_HEIGHT - vertical)
				{
					inside = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (inside == true) {

						int pipeTypeValue = mPipeMap[row][column];

						//Structure Interface Display
						switch (pipeTypeValue)
						{
						case 0:
							mDrainageInterface = NULL;
							mDrainageText = NULL;

							mDrainageMenuSellText = NULL;
							mDrainageMenuToggleText = NULL;
							break;

						case 1:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 2:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 3:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 4:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 5:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 6:
							mDrainageInterface = mDrainagePipeInterface;
							mDrainageText = mDrainagePipeText;

							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 7:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 8:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 9:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 10:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 11:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 12:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 13:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 14:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 15:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 16:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 17:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 18:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 19:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 20:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 21:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 22:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 23:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 24:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 25:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 26:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						case 27:
							mDrainageInterface = mWaterTreatmentInterface;
							mDrainageText = mWaterTreatmentText;


							mDrainageMenuSellText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							mDrainageMenuToggleText = new Texture("Water", "unispace.ttf", 14, { 150, 0, 0 });
							break;

						default:
							break;
						}

						mDrainagePositionSelectX = row;
						mDrainagePositionSelectY = column;
						drainageSelect = true;
						mChangeDrainageSelect = true;


					}
					else {

						mChangeDrainageSelect = false;

					}
				}
			}
		}

	}


	





}


void InteractionMap::HandleStructureSelect() {



	if (mInput->MouseButtonPressed(InputManager::left)) {


		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check Structure Selection
		bool structureSelect = false;


		for (int row = 0; row < 25; row++)
		{


			for (int column = 0; column < 16; column++)
			{

				//if (y < 500 && y > 50) {

				//	break;
				//}

				if (x < 840 && x > 640 && y < 883 && y > 720) {

					break;
				}

				int horizontal = row * 34;
				int vertical = column * 34;

				//Check if mouse is in button
				bool inside = true;

				if (structureSelect == true) {
					break;
				}

				//Mouse is left of the button
				if (x < mPosition.x - SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse is right of the button
				else if (x > mPosition.x + SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse above the button
				else if (y < mPosition.y - SELECT_HEIGHT - vertical)
				{
					inside = false;
				}
				//Mouse below the button
				else if (y > mPosition.y + SELECT_HEIGHT - vertical)
				{
					inside = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (inside == true) {

						int structureTypeValue = mStructureMap[row][column];

						//Structure Interface Display
						switch (structureTypeValue)
						{
						case 0:
							mStructureInterface = NULL;
							mStructureText = NULL;
							mStructureSubText = NULL;

							mStructureMenuMovementText = NULL;

							break;
						case 1:
							mStructureInterface = mHouseInterface;
							mStructureText = mHouseText;
							mStructureSubText = NULL;

							mStructureMenuMovementText = NULL;

							break;
						default:
							break;
						}

						mStructurePositionSelectX = row;
						mStructurePositionSelectY = column;
						structureSelect = true;
						mChangeStructureSelect = true;

					}
					else {

						mChangeStructureSelect = false;

					}
				}
			}
		}



	}




}


/*
void InteractionMap::HandleSelect() {


	//MOUSEOVER FOR EACH BUTTON IS FIRST, THEN SIMILARLY BUTTON SELECTION IS NEXT, THEN UNIT SELECTION

	//MOUSEOVER FOR BUTTONS BEGINS HERE

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

		

	//MOVEMENT BUTTON

		//Check if mouse is in button
	bool insideunitmenumovement = true;

	//Mouse is left of the button
	if (x < mStructureMenuMovementPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenumovement = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuMovementPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenumovement = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuMovementPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenumovement = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuMovementPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenumovement = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenumovement == true) {

			//mStructureSelect = true;
			mChangeStructureMenuMovementMouseOver = true;

		}
		else {

			mChangeStructureMenuMovementMouseOver = false;

		}
	}



	//ACTION BUTTON

	//Check if mouse is in button
	bool insideunitmenuaction = true;

	//Mouse is left of the button
	if (x < mStructureMenuActionPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuaction = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuActionPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuaction = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuActionPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuaction = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuActionPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuaction = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenuaction == true) {

			mChangeStructureMenuActionMouseOver = true;

		}
		else {

			mChangeStructureMenuActionMouseOver = false;

		}
	}


	//ITEM BUTTON

	//Check if mouse is in button
	bool insideunitmenuitem = true;

	//Mouse is left of the button
	if (x < mStructureMenuItemPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuitem = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuItemPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenuitem = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuItemPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuitem = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuItemPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenuitem = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenuitem == true) {

			mChangeStructureMenuItemMouseOver = true;

		}
		else {

			mChangeStructureMenuItemMouseOver = false;

		}
	}

	//STATUS BUTTON

	//Check if mouse is in button
	bool insideunitmenustatus = true;

	//Mouse is left of the button
	if (x < mStructureMenuStatusPosition.x - UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenustatus = false;
	}
	//Mouse is right of the button
	else if (x > mStructureMenuStatusPosition.x + UNIT_MENU_SELECT_WIDTH)
	{
		insideunitmenustatus = false;
	}
	//Mouse above the button
	else if (y < mStructureMenuStatusPosition.y - UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenustatus = false;
	}
	//Mouse below the button
	else if (y > mStructureMenuStatusPosition.y + UNIT_MENU_SELECT_HEIGHT)
	{
		insideunitmenustatus = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideunitmenustatus == true) {

			mChangeStructureMenuStatusMouseOver = true;

		}
		else {

			mChangeStructureMenuStatusMouseOver = false;

		}
	}
	//BUTTON MOUSE OVER ENDS HERE


	//BUTTON SELECTION BEGINS HERE


	//If mouse event happened
	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check Structure Menu Mouseover

		



		//Check Structure Menu Selection

		if (mChangeStructureSelect == true) {


			//MOVEMENT BUTTON

			//Check if mouse is in button
			bool insideunitmenumovement = true;

			//Mouse is left of the button
			if (x < mStructureMenuMovementPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenumovement = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuMovementPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenumovement = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuMovementPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenumovement = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuMovementPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenumovement = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenumovement == true) {

					//mStructureSelect = true;
					mChangeStructureMenuMovementSelect = true;

				}
				else {

					mChangeStructureMenuMovementSelect = false;

				}
			}



			//ACTION BUTTON

			//Check if mouse is in button
			bool insideunitmenuaction = true;

			//Mouse is left of the button
			if (x < mStructureMenuActionPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuaction = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuActionPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuaction = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuActionPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuaction = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuActionPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuaction = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenuaction == true) {

					mChangeStructureMenuActionSelect = true;

				}
				else {

					mChangeStructureMenuActionSelect = false;

				}
			}


			//ITEM BUTTON

			//Check if mouse is in button
			bool insideunitmenuitem = true;

			//Mouse is left of the button
			if (x < mStructureMenuItemPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuitem = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuItemPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenuitem = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuItemPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuitem = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuItemPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenuitem = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenuitem == true) {

					mChangeStructureMenuItemSelect = true;

				}
				else {

					mChangeStructureMenuItemSelect = false;

				}
			}
				
			//STATUS BUTTON

			//Check if mouse is in button
			bool insideunitmenustatus = true;

			//Mouse is left of the button
			if (x < mStructureMenuStatusPosition.x - UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenustatus = false;
			}
			//Mouse is right of the button
			else if (x > mStructureMenuStatusPosition.x + UNIT_MENU_SELECT_WIDTH)
			{
				insideunitmenustatus = false;
			}
			//Mouse above the button
			else if (y < mStructureMenuStatusPosition.y - UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenustatus = false;
			}
			//Mouse below the button
			else if (y > mStructureMenuStatusPosition.y + UNIT_MENU_SELECT_HEIGHT)
			{
				insideunitmenustatus = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideunitmenustatus == true) {

					mChangeStructureMenuStatusSelect = true;

				}
				else {

					mChangeStructureMenuStatusSelect = false;

				}
			}

				


			

		}
	//BUTTON SELECTION ENDS HERE
	
	//UNIT SELECTION BEGINS HERE

	//Check Structure Selection
	bool mStructureSelect = false;

	if (mChangeStructureMenuMovementSelect == false) {
	
		for (int row = 0; row < 25; row++)
		{


			for (int column = 0; column < 16; column++)
			{

				//if (y < 500 && y > 50) {

				//	break;
				//}

				if (x < 840 && x > 640 && y < 883 && y > 720) {

					break;
				}

				int horizontal = row * 34;
				int vertical = column * 34;

				//Check if mouse is in button
				bool inside = true;

				if (mStructureSelect == true) {
					break;
				}

				//Mouse is left of the button
				if (x < mPosition.x - SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse is right of the button
				else if (x > mPosition.x + SELECT_WIDTH - horizontal)
				{
					inside = false;
				}
				//Mouse above the button
				else if (y < mPosition.y - SELECT_HEIGHT - vertical)
				{
					inside = false;
				}
				//Mouse below the button
				else if (y > mPosition.y + SELECT_HEIGHT - vertical)
				{
					inside = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (inside == true) {

						mPipeTypeValue = mStructureMap[row][column];

						//Structure Interface Display
						switch (mPipeTypeValue)
						{
						case 0:
							mStructureInterface = NULL;
							mStructureText = NULL;
							mStructureSubText = NULL;

							mStructureMenuMovementText = NULL;
							mStructureMenuActionText = NULL;
							mStructureMenuItemText = NULL;
							mStructureMenuStatusText = NULL;

							break;
						case 1:
							mStructureInterface = mHouseInterface;
							mStructureText = mHouseText;
							mStructureSubText = NULL;

							mStructureMenuMovementText = NULL;
							mStructureMenuActionText = NULL;
							mStructureMenuItemText = NULL;
							mStructureMenuStatusText = NULL;

							break;


						case 30:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 31:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 32:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 33:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 34:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 35:
							mStructureInterface = mDrainagePipeInterface;
							mStructureText = mDrainagePipeText;
							mStructureSubText = mStructureSubText;

							mStructureMenuMovementText = mStructureMenuMovementText;
							mStructureMenuActionText = mStructureMenuActionText;
							mStructureMenuItemText = mStructureMenuItemText;
							mStructureMenuStatusText = mStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						case 69:
							mStructureInterface = mWaterTreatmentInterface;
							mStructureText = mWaterTreatmentText;
							mStructureSubText = NULL;

							//mStructureMenuMovementText = mTradeStructureMenuMovementText;
							//mStructureMenuActionText = mTradeStructureMenuActionText;
							//mStructureMenuItemText = mTradeStructureMenuItemText;
							//mStructureMenuStatusText = mTradeStructureMenuStatusText;

							mStructureMenuTotal = 4;

							break;

						default:
							break;
						}

						mStructurePositionSelectX = row;
						mStructurePositionSelectY = column;
						mStructureSelect = true;
						mChangeStructureSelect = true;

					}
					else {

						mChangeStructureSelect = false;

					}
				}
			}
		}

	}
	
	}




}
*/







void InteractionMap::HandleMovement() {

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Find the targeted tile the player chose to move
	if (mChangeStructureMenuMovementSelect == true) {

		bool structurePositionSelect = false;

		if (mInput->MouseButtonPressed(InputManager::right)) {

		
			for (int row = 0; row < 25; row++)
			{


				for (int column = 0; column < 16; column++)
				{

					//if (y < 500 && y > 50) {

					//	break;
					//}

					if (x < 840 && x > 640 && y < 883 && y > 720) {

						break;
					}

					int horizontal = row * 34;
					int vertical = column * 34;

					//Check if mouse is in button
					bool inside = true;

					if (structurePositionSelect == true) {
						break;
					}

					//Mouse is left of the button
					if (x < mPosition.x - SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse is right of the button
					else if (x > mPosition.x + SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse above the button
					else if (y < mPosition.y - SELECT_HEIGHT - vertical)
					{
						inside = false;
					}
					//Mouse below the button
					else if (y > mPosition.y + SELECT_HEIGHT - vertical)
					{
						inside = false;
					}

					//Mouse is outside button
					if (SDL_MOUSEBUTTONDOWN)
					{
						if (inside == true) {

							structurePositionSelect = true;

							mStructurePositionTargetX = row;
							mStructurePositionTargetY = column;

							int selectrow = mStructurePositionSelectX;
							int selectcolumn = mStructurePositionSelectY;

							mStructurePositionValue = mPipeMap[selectrow][selectcolumn];
							int mStructurePointTransferValue = mFloodValueMap[selectrow][selectcolumn];

							int modifier = 5;

							//FILTER FOR UNITS RESTRICTED MOVEMENT

							if (

								!(mStructurePositionTargetX < (mStructurePositionSelectX - modifier)) &&
								!(mStructurePositionTargetX > (mStructurePositionSelectX + modifier)) &&
								!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier)) &&
								!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier)) &&
								!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier) && mStructurePositionTargetX < mStructurePositionSelectX - modifier) &&
								!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier) && mStructurePositionTargetX > mStructurePositionSelectX + modifier) &&
								!(mStructurePositionTargetY < (mStructurePositionSelectY - modifier) && mStructurePositionTargetX > mStructurePositionSelectX + modifier) &&
								!(mStructurePositionTargetY > (mStructurePositionSelectY + modifier) && mStructurePositionTargetX < mStructurePositionSelectX - modifier)

								)
							{

								if (mTileMap[row][column] != 0 && mPipeMap[row][column] == 0) {


									mPipeMap[row][column] = mStructurePositionValue;
									mPipeMap[selectrow][selectcolumn] = 0;

									mFloodValueMap[row][column] = mStructurePointTransferValue;
									mFloodValueMap[selectrow][selectcolumn] = 0;






									//Select new tile

									mTileHighlight->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
									mTileHighlightOn = true;

									int tileTextValue = mTileMap[row][column];

									switch (tileTextValue)
									{
									case 0:
										mTileText = mWaterText;
										break;
									case 1:
										mTileText = mDirtText;
										break;
									case 2:
										mTileText = mGrassText;
										break;
									default:
										break;
									}

									mStructurePositionSelectX = row;
									mStructurePositionSelectY = column;

									//Unselect Movement Button
									mChangeStructureMenuMovementSelect = false;
									//structureSelect = false;
									// 
									// 
									//mChangeStructureMenuActionSelect = false;
									//mChangeStructureSelect = false;



								}

							}

						}
					}
				}
			}

		}

	}

}

void InteractionMap::HandleAction() {

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Find the targeted tile the player chose to act upon
	if (mChangeStructureMenuActionSelect == true) {

		bool mStructureActionSelect = false;

		if (mInput->MouseButtonPressed(InputManager::right)) {


			for (int row = 0; row < 25; row++)
			{


				for (int column = 0; column < 16; column++)
				{

					
					//Unclickable zone filter
					if (x < 840 && x > 640 && y < 883 && y > 720) {

						break;
					}

					int horizontal = row * 34;
					int vertical = column * 34;

					//Check if mouse is in button
					bool inside = true;

					if (mStructureActionSelect == true) {
						break;
					}

					//Mouse is left of the button
					if (x < mPosition.x - SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse is right of the button
					else if (x > mPosition.x + SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse above the button
					else if (y < mPosition.y - SELECT_HEIGHT - vertical)
					{
						inside = false;
					}
					//Mouse below the button
					else if (y > mPosition.y + SELECT_HEIGHT - vertical)
					{
						inside = false;
					}

					//Mouse is outside button
					if (SDL_MOUSEBUTTONDOWN)
					{
						if (inside == true) {

							mStructureActionSelect = true;

							mStructureActionTargetX = row;
							mStructureActionTargetY = column;

							int selectrow = mStructurePositionSelectX;
							int selectcolumn = mStructurePositionSelectY;

							mStructureActionSelectValue = mFloodValueMap[selectrow][selectcolumn];
							mStructureActionTargetValue = mFloodValueMap[row][column];

							//Check if adjacent

							if (

								(mStructureActionTargetY == mStructurePositionSelectY && mStructureActionTargetX == (mStructurePositionSelectX - 1)) ||
								(mStructureActionTargetY == mStructurePositionSelectY && mStructureActionTargetX == (mStructurePositionSelectX + 1)) ||
								(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX) ||
								(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX) ||
								(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX - 1) ||
								(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX + 1) ||
								(mStructureActionTargetY == (mStructurePositionSelectY - 1) && mStructureActionTargetX == mStructurePositionSelectX + 1) ||
								(mStructureActionTargetY == (mStructurePositionSelectY + 1) && mStructureActionTargetX == mStructurePositionSelectX - 1)

								)

							{

								//PERFORM ACTION

								//Structure Types
								int targetunittype = mPipeMap[row][column];
								int selectunittype = mPipeMap[selectrow][selectcolumn];
								
								//Tile Type Modifiers
								int targettilemodifier = mTileMap[row][column];
								int selecttilemodifier = mTileMap[selectrow][selectcolumn];

								//int targetunitpattern = CheckStructurePattern(targetunittype);
								//int selectunitpattern = CheckStructurePattern(selectunittype);
								//targettilemodifier = CheckTileModifier(targettilemodifier);
								//selecttilemodifier = CheckTileModifier(selecttilemodifier);


								int targetunitpatternarray[8] = {};
								int selectunitpatternarray[8] = {};
								
								
								if (targetunittype == 0 ) {

									break;

								} else if (targetunittype == 1 || targetunittype == -1) {

									break;


								} else if (targetunittype == 2 || targetunittype == -2) {

									//Cooperative
									targetunitpatternarray[7] = (0, 0, 0, 0, 0, 0, 0, 0);

								}
								else if (targetunittype == 3 || targetunittype == -3) {

									//Greedy
									targetunitpatternarray[7] = (1, 1, 1, 1, 1, 1, 1, 1);


								}
								else if (targetunittype == 4 || targetunittype == -4) {

									//Copycat
									targetunitpatternarray[7] = (1, 1, 1, 1, 1, 1, 1, 1);


								}


								if (selectunittype == 0) {

									break;

								}
								else if (selectunittype == 1 || selectunittype == -1) {

									break;

								}
								else if (selectunittype == 2 || selectunittype == -2) {

									//Cooperative
									selectunitpatternarray[7] = (0, 0, 0, 0, 0, 0, 0, 0);

								}
								else if (selectunittype == 3 || selectunittype == -3) {

									//Greedy
									selectunitpatternarray[7] = (1, 1, 1, 1, 1, 1, 1, 1);


								}
								else if (selectunittype == 4 || selectunittype == -4) {

									//Copycat
									selectunitpatternarray[7] = (1, 1, 1, 1, 1, 1, 1, 1);


								}

								
								for (int i = 0; i < 8; i++) {

									int targetdecision = targetunitpatternarray[i];
									int selectdecision = selectunitpatternarray[i];  

									int targetweight = NULL;
									int selectweight = NULL;


									if (targetdecision == 0 && selectdecision == 0) {

										//Both Cooperate
										//Both gain an average amount, 2 or so
										targetweight = 2;
										selectweight = 2;

									}
									else if (targetdecision == 1 && selectdecision == 1 ) {

										//Both Greed
										//Both Gain nothing or very little
										targetweight = 0;
										selectweight = 0;

									}
									else if (targetdecision == 0 && selectdecision == 1) {

										//Target is cooperating, user selected is greedy
										//Target loses some, -1
										//Selected gains a lot, 3 or more
										targetweight = -1;
										selectweight = 3;

									}
									else if (targetdecision == 1 && selectdecision == 0) {

										//Target is greedy, user selected is cooperating
										//Target gains a lot, 3 or more
									    //Selected loses some, -1
										targetweight = 3;
										selectweight = -1;

									}


									mFloodValueMap[row][column] = mStructureActionTargetValue + targetweight;
									mFloodValueMap[selectrow][selectcolumn] = mStructureActionSelectValue + selectweight;

								}

							}
								

						}
					}
				}
			}

		}

	}

}


void InteractionMap::HandlePipeMenuSelect() {

	//MOUSEOVER

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
	bool insidepipemenu = true;

	//Mouse is left of the button
	if (x < mPipeMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
	{
		insidepipemenu = false;
	}
	//Mouse is right of the button
	else if (x > mPipeMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
	{
		insidepipemenu = false;
	}
	//Mouse above the button
	else if (y < mPipeMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
	{
		insidepipemenu = false;
	}
	//Mouse below the button
	else if (y > mPipeMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
	{
		insidepipemenu = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidepipemenu == true) {


			mPipeMenuMouseOver = true;

		}
		else {

			mPipeMenuMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);



		//shrink slightly
		

			

		

				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insidepipemenu = true;

				//Mouse is left of the button
				if (x < mPipeMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
				{
					insidepipemenu = false;
				}
				//Mouse is right of the button
				else if (x > mPipeMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
				{
					insidepipemenu = false;
				}
				//Mouse above the button
				else if (y < mPipeMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
				{
					insidepipemenu = false;
				}
				//Mouse below the button
				else if (y > mPipeMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
				{
					insidepipemenu = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insidepipemenu == true) {


						mPipeMenuSelect = true;


					}
					else {

						if (x > 334 || x < 80 || y > 878 || y < 726) {

							mPipeMenuSelect = false;

						}

					}
				}


			




		


	}


			


			
}

void  InteractionMap::HandlePipeShopSelect() {


	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);



	//Vertical Pipe Up

		//MOUSEOVER

		//Check if mouse is in button
	bool insidefilter = true;

	//Mouse is left of the button
	if (x < mDrainagePipeVUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insidefilter = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeVUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insidefilter = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeVUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insidefilter = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeVUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insidefilter = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidefilter == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeVUpMouseOver = true;

		}
		else {

			mChangeDrainagePipeVUpMouseOver = false;

		}
	}

	

		//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insidefilter = true;

		//Mouse is left of the button
		if (x < mDrainagePipeVUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insidefilter = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeVUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insidefilter = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeVUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insidefilter = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeVUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insidefilter = false;
		}


		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insidefilter == true) {


				mChangeDrainagePipeVUpSelect = true;


			}
			else {

				mChangeDrainagePipeVUpSelect = false;

			}
		}




	}


	//Vertical Pipe Down

	//MOUSEOVER

	//Check if mouse is in button
	bool insideshoppipevdown = true;

	//Mouse is left of the button
	if (x < mDrainagePipeVDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipevdown = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeVDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipevdown = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeVDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipevdown = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeVDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipevdown = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipevdown == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeVDownMouseOver = true;

		}
		else {

			mChangeDrainagePipeVDownMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipevdown = true;

		//Mouse is left of the button
		if (x < mDrainagePipeVDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipevdown = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeVDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipevdown = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeVDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipevdown = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeVDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipevdown = false;
		}


		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipevdown == true) {


				mChangeDrainagePipeVDownSelect = true;


			}
			else {

				mChangeDrainagePipeVDownSelect = false;

			}
		}




	}



	//Horizontal Pipe Right

		//MOUSEOVER

		//Check if mouse is in button
	bool insideshoppipehright = true;

	//Mouse is left of the button
	if (x < mDrainagePipeHRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipehright = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeHRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipehright = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeHRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipehright = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeHRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipehright = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipehright == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeHRightMouseOver = true;

		}
		else {

			mChangeDrainagePipeHRightMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipehright = true;

		//Mouse is left of the button
		if (x < mDrainagePipeHRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipehright = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeHRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipehright = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeHRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipehright = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeHRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipehright = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipehright == true) {


				mChangeDrainagePipeHRightSelect = true;


			}
			else {

				mChangeDrainagePipeHRightSelect = false;

			}
		}




	}


	//Horizontal Pipe Left

		//MOUSEOVER

		//Check if mouse is in button
	bool insideshoppipehrleft = true;

	//Mouse is left of the button
	if (x < mDrainagePipeHLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipehrleft = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeHLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipehrleft = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeHLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipehrleft = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeHLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipehrleft = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipehrleft == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeHLeftMouseOver = true;

		}
		else {

			mChangeDrainagePipeHLeftMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipehrleft = true;

		//Mouse is left of the button
		if (x < mDrainagePipeHLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipehrleft = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeHLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipehrleft = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeHLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipehrleft = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeHLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipehrleft = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipehrleft == true) {


				mChangeDrainagePipeHLeftSelect = true;


			}
			else {

				mChangeDrainagePipeHLeftSelect = false;

			}
		}




	}



	//Corner Pipe One Down

		//MOUSEOVER

		//Check if mouse is in button
	bool insideshoppipecronedown = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCROneDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecronedown = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCROneDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecronedown = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCROneDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecronedown = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCROneDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecronedown = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecronedown == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCROneDownMouseOver = true;

		}
		else {

			mChangeDrainagePipeCROneDownMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecronedown = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCROneDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecronedown = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCROneDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecronedown = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCROneDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecronedown = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCROneDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecronedown = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecronedown == true) {


				mChangeDrainagePipeCROneDownSelect = true;


			}
			else {

				mChangeDrainagePipeCROneDownSelect = false;

			}
		}




	}


	//Corner Pipe One Right

		//MOUSEOVER

		//Check if mouse is in button
	bool insideshoppipecroneright = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCROneRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecroneright = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCROneRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecroneright = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCROneRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecroneright = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCROneRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecroneright = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecroneright == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCROneRightMouseOver = true;

		}
		else {

			mChangeDrainagePipeCROneRightMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecroneright = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCROneRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecroneright = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCROneRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecroneright = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCROneRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecroneright = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCROneRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecroneright = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecroneright == true) {


				mChangeDrainagePipeCROneRightSelect = true;


			}
			else {

				mChangeDrainagePipeCROneRightSelect = false;

			}
		}




	}

	//Corner Pipe Two Down

		//MOUSEOVER

		//Check if mouse is in button
	bool insideshoppipecrtwodown = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCRTwoDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrtwodown = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCRTwoDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrtwodown = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCRTwoDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrtwodown = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCRTwoDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrtwodown = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecrtwodown == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCRTwoDownMouseOver = true;

		}
		else {

			mChangeDrainagePipeCRTwoDownMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecrtwodown = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRTwoDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrtwodown = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRTwoDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrtwodown = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRTwoDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrtwodown = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRTwoDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrtwodown = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrtwodown == true) {


				mChangeDrainagePipeCRTwoDownSelect = true;


			}
			else {

				mChangeDrainagePipeCRTwoDownSelect = false;

			}
		}




	}


	//Corner Pipe Two Left

	//MOUSEOVER

	//Check if mouse is in button
	bool insideshoppipecrtwoleft = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCRTwoLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrtwoleft = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCRTwoLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrtwoleft = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCRTwoLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrtwoleft = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCRTwoLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrtwoleft = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecrtwoleft == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCRTwoLeftMouseOver = true;

		}
		else {

			mChangeDrainagePipeCRTwoLeftMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecrtwoleft = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRTwoLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrtwoleft = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRTwoLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrtwoleft = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRTwoLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrtwoleft = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRTwoLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrtwoleft = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrtwoleft == true) {


				mChangeDrainagePipeCRTwoLeftSelect = true;


			}
			else {

				mChangeDrainagePipeCRTwoLeftSelect = false;

			}
		}




	}


	//Corner Pipe Three Up

	//MOUSEOVER

	//Check if mouse is in button
	bool insideshoppipecrthree = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCRThreeUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrthree = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCRThreeUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrthree = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCRThreeUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrthree = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCRThreeUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrthree = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecrthree == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCRThreeUpMouseOver = true;

		}
		else {

			mChangeDrainagePipeCRThreeUpMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecrthree = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRThreeUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrthree = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRThreeUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrthree = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRThreeUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrthree = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRThreeUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrthree = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrthree == true) {


				mChangeDrainagePipeCRThreeUpSelect = true;


			}
			else {

				mChangeDrainagePipeCRThreeUpSelect = false;

			}
		}




	}



		//Corner Pipe Three Left

	//MOUSEOVER

	//Check if mouse is in button
	bool insideshoppipecrthreeleft = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCRThreeLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrthreeleft = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCRThreeLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrthreeleft = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCRThreeLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrthreeleft = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCRThreeLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrthreeleft = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecrthreeleft == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCRThreeLeftMouseOver = true;

		}
		else {

			mChangeDrainagePipeCRThreeLeftMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecrthreeleft = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRThreeLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrthreeleft = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRThreeLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrthreeleft = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRThreeLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrthreeleft = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRThreeLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrthreeleft = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrthreeleft == true) {


				mChangeDrainagePipeCRThreeLeftSelect = true;


			}
			else {

				mChangeDrainagePipeCRThreeLeftSelect = false;

			}
		}




	}

	//Corner Pipe Four Up

	//MOUSEOVER

	//Check if mouse is in button
	bool insideshoppipecrfourup = true;

	//Mouse is left of the button
	if (x < mDrainagePipeCRFourUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrfourup = false;
	}
	//Mouse is right of the button
	else if (x > mDrainagePipeCRFourUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insideshoppipecrfourup = false;
	}
	//Mouse above the button
	else if (y < mDrainagePipeCRFourUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrfourup = false;
	}
	//Mouse below the button
	else if (y > mDrainagePipeCRFourUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insideshoppipecrfourup = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insideshoppipecrfourup == true) {

			//mStructureSelect = true;
			mChangeDrainagePipeCRFourUpMouseOver = true;

		}
		else {

			mChangeDrainagePipeCRFourUpMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insideshoppipecrfourup = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRFourUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrfourup = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRFourUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrfourup = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRFourUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrfourup = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRFourUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrfourup = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrfourup == true) {


				mChangeDrainagePipeCRFourUpSelect = true;


			}
			else {

				mChangeDrainagePipeCRFourUpSelect = false;

			}
		}

	}

		//Corner Pipe Four Right

		//MOUSEOVER

		//Check if mouse is in button
		bool insideshoppipecrfourright = true;

		//Mouse is left of the button
		if (x < mDrainagePipeCRFourRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrfourright = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeCRFourRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipecrfourright = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeCRFourRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrfourright = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeCRFourRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipecrfourright = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipecrfourright == true) {

				//mStructureSelect = true;
				mChangeDrainagePipeCRFourRightMouseOver = true;

			}
			else {

				mChangeDrainagePipeCRFourRightMouseOver = false;

			}
		}



		//SELECTION

		if (mInput->MouseButtonPressed(InputManager::left)) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);


			//MOVEMENT BUTTON

			//Check if mouse is in button
			bool insideshoppipecrfourright = true;

			//Mouse is left of the button
			if (x < mDrainagePipeCRFourRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipecrfourright = false;
			}
			//Mouse is right of the button
			else if (x > mDrainagePipeCRFourRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipecrfourright = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeCRFourRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipecrfourright = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeCRFourRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipecrfourright = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipecrfourright == true) {


					mChangeDrainagePipeCRFourRightSelect = true;


				}
				else {

					mChangeDrainagePipeCRFourRightSelect = false;

				}
			}

		}




		//T Shape Pipe One Right

		//MOUSEOVER

		//Check if mouse is in button
		bool insideshoppipetoneright = true;

		//Mouse is left of the button
		if (x < mDrainagePipeTOneRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipetoneright = false;
		}
		//Mouse is right of the button
		else if (x > mDrainagePipeTOneRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insideshoppipetoneright = false;
		}
		//Mouse above the button
		else if (y < mDrainagePipeTOneRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipetoneright = false;
		}
		//Mouse below the button
		else if (y > mDrainagePipeTOneRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insideshoppipetoneright = false;
		}

		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insideshoppipetoneright == true) {

				//mStructureSelect = true;
				mChangeDrainagePipeTOneRightMouseOver = true;

			}
			else {

				mChangeDrainagePipeTOneRightMouseOver = false;

			}
		}



		//SELECTION

		if (mInput->MouseButtonPressed(InputManager::left)) {

			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);


			//MOVEMENT BUTTON

			//Check if mouse is in button
			bool insideshoppipetoneright = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTOneRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetoneright = false;
			}
			//Mouse is right of the button
			else if (x > mDrainagePipeTOneRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetoneright = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTOneRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetoneright = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTOneRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetoneright = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetoneright == true) {


					mChangeDrainagePipeTOneRightSelect = true;


				}
				else {

					mChangeDrainagePipeTOneRightSelect = false;

				}
			}

		}


			//T Shape Pipe One Left

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetoneleft = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTOneLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetoneleft = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTOneLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetoneleft = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTOneLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetoneleft = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTOneLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetoneleft = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetoneleft == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTOneLeftMouseOver = true;

				}
				else {

					mChangeDrainagePipeTOneLeftMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetonedown = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTOneLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetonedown = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTOneLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetonedown = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTOneLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetonedown = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTOneLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetonedown = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetonedown == true) {


						mChangeDrainagePipeTOneLeftSelect = true;


					}
					else {

						mChangeDrainagePipeTOneLeftSelect = false;

					}
				}

			}




			//T Shape Pipe One Down

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetonedown = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTOneDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetonedown = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTOneDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetonedown = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTOneDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetonedown = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTOneDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetonedown = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetonedown == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTOneDownMouseOver = true;

				}
				else {

					mChangeDrainagePipeTOneDownMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetonedown = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTOneDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetonedown = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTOneDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetonedown = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTOneDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetonedown = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTOneDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetonedown = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetonedown == true) {


						mChangeDrainagePipeTOneDownSelect = true;


					}
					else {

						mChangeDrainagePipeTOneDownSelect = false;

					}
				}

			}





			//T Shape Pipe Two Left

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipettwoleft = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTTwoLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwoleft = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTTwoLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwoleft = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTTwoLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwoleft = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTTwoLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwoleft = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipettwoleft == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTTwoLeftMouseOver = true;

				}
				else {

					mChangeDrainagePipeTTwoLeftMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipettwoleft = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTTwoLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwoleft = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTTwoLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwoleft = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTTwoLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwoleft = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTTwoLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwoleft = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipettwoleft == true) {


						mChangeDrainagePipeTTwoLeftSelect = true;


					}
					else {

						mChangeDrainagePipeTTwoLeftSelect = false;

					}
				}

			}




			//T Shape Pipe Two Up

			//MOUSEOVER
	
			//Check if mouse is in button
			bool insideshoppipettwoup = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTTwoUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwoup = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTTwoUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwoup = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTTwoUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwoup = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTTwoUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwoup = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipettwoup == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTTwoUpMouseOver = true;

				}
				else {

					mChangeDrainagePipeTTwoUpMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipettwoup = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTTwoUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwoup = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTTwoUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwoup = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTTwoUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwoup = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTTwoUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwoup = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipettwoup == true) {


						mChangeDrainagePipeTTwoUpSelect = true;


					}
					else {

						mChangeDrainagePipeTTwoUpSelect = false;

					}
				}

			}
		


			//T Shape Pipe Two Down

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipettwodown = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTTwoDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwodown = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTTwoDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipettwodown = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTTwoDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwodown = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTTwoDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipettwodown = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipettwodown == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTTwoDownMouseOver = true;

				}
				else {

					mChangeDrainagePipeTTwoDownMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipettwodown = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTTwoDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwodown = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTTwoDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipettwodown = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTTwoDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwodown = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTTwoDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipettwodown = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipettwodown == true) {


						mChangeDrainagePipeTTwoDownSelect = true;


					}
					else {

						mChangeDrainagePipeTTwoDownSelect = false;

					}
				}

			}




			//T Shape Pipe Three Up

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetthreeup = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTThreeUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreeup = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTThreeUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreeup = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTThreeUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreeup = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTThreeUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreeup = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetthreeup == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTThreeUpMouseOver = true;

				}
				else {

					mChangeDrainagePipeTThreeUpMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetthreeup = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTThreeUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreeup = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTThreeUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreeup = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTThreeUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreeup = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTThreeUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreeup = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetthreeup == true) {


						mChangeDrainagePipeTThreeUpSelect = true;


					}
					else {

						mChangeDrainagePipeTThreeUpSelect = false;

					}
				}

			}



			//T Shape Pipe Three Right

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetthreeright = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTThreeRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreeright = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTThreeRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreeright = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTThreeRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreeright = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTThreeRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreeright = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetthreeright == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTThreeRightMouseOver = true;

				}
				else {

					mChangeDrainagePipeTThreeRightMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetthreeright = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTThreeRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreeright = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTThreeRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreeright = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTThreeRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreeright = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTThreeRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreeright = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetthreeright == true) {


						mChangeDrainagePipeTThreeRightSelect = true;


					}
					else {

						mChangeDrainagePipeTThreeRightSelect = false;

					}
				}

			}




			//T Shape Pipe Three Down

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetthreedown = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTThreeDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreedown = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTThreeDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetthreedown = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTThreeDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreedown = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTThreeDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetthreedown = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetthreedown == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTThreeDownMouseOver = true;

				}
				else {

					mChangeDrainagePipeTThreeDownMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetthreedown = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTThreeDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreedown = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTThreeDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetthreedown = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTThreeDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreedown = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTThreeDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetthreedown = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetthreedown == true) {


						mChangeDrainagePipeTThreeDownSelect = true;


					}
					else {

						mChangeDrainagePipeTThreeDownSelect = false;

					}
				}

			}








			//T Shape Pipe Four Up

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetfourup = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTFourUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourup = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTFourUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourup = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTFourUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourup = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTFourUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourup = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetfourup == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTFourUpMouseOver = true;

				}
				else {

					mChangeDrainagePipeTFourUpMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetfourup = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTFourUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourup = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTFourUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourup = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTFourUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourup = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTFourUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourup = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetfourup == true) {


						mChangeDrainagePipeTFourUpSelect = true;


					}
					else {

						mChangeDrainagePipeTFourUpSelect = false;

					}
				}

			}



			//T Shape Pipe Four Right

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetfourright = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTFourRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourright = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTFourRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourright = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTFourRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourright = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTFourRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourright = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetfourright == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTFourRightMouseOver = true;

				}
				else {

					mChangeDrainagePipeTFourRightMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetfourright = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTFourRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourright = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTFourRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourright = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTFourRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourright = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTFourRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourright = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetfourright == true) {


						mChangeDrainagePipeTFourRightSelect = true;


					}
					else {

						mChangeDrainagePipeTFourRightSelect = false;

					}
				}

			}


			//T Shape Pipe Four Left

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipetfourleft = true;

			//Mouse is left of the button
			if (x < mDrainagePipeTFourLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourleft = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeTFourLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipetfourleft = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeTFourLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourleft = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeTFourLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipetfourleft = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipetfourleft == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeTFourLeftMouseOver = true;

				}
				else {

					mChangeDrainagePipeTFourLeftMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipetfourleft = true;

				//Mouse is left of the button
				if (x < mDrainagePipeTFourLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourleft = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeTFourLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipetfourleft = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeTFourLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourleft = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeTFourLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipetfourleft = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipetfourleft == true) {


						mChangeDrainagePipeTFourLeftSelect = true;


					}
					else {

						mChangeDrainagePipeTFourLeftSelect = false;

					}
				}

			}




	



			//Square Up

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipesquareup = true;

			//Mouse is left of the button
			if (x < mDrainagePipeSquareUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareup = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeSquareUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareup = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeSquareUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareup = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeSquareUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareup = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipesquareup == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeSquareUpMouseOver = true;

				}
				else {

					mChangeDrainagePipeSquareUpMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipesquareup = true;

				//Mouse is left of the button
				if (x < mDrainagePipeSquareUpPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareup = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeSquareUpPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareup = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeSquareUpPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareup = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeSquareUpPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareup = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipesquareup == true) {


						mChangeDrainagePipeSquareUpSelect = true;


					}
					else {

						mChangeDrainagePipeSquareUpSelect = false;

					}
				}

			}




			//Square Down

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipesquaredown = true;

			//Mouse is left of the button
			if (x < mDrainagePipeSquareDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquaredown = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeSquareDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquaredown = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeSquareDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquaredown = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeSquareDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquaredown = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipesquaredown == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeSquareDownMouseOver = true;

				}
				else {

					mChangeDrainagePipeSquareDownMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipesquaredown = true;

				//Mouse is left of the button
				if (x < mDrainagePipeSquareDownPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquaredown = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeSquareDownPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquaredown = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeSquareDownPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquaredown = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeSquareDownPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquaredown = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipesquaredown == true) {


						mChangeDrainagePipeSquareDownSelect = true;


					}
					else {

						mChangeDrainagePipeSquareDownSelect = false;

					}
				}

			}





			//Square Left

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipesquareleft = true;

			//Mouse is left of the button
			if (x < mDrainagePipeSquareLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareleft = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeSquareLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareleft = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeSquareLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareleft = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeSquareLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareleft = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipesquareleft == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeSquareLeftMouseOver = true;

				}
				else {

					mChangeDrainagePipeSquareLeftMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);



				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipesquareleft = true;

				//Mouse is left of the button
				if (x < mDrainagePipeSquareLeftPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareleft = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeSquareLeftPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareleft = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeSquareLeftPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareleft = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeSquareLeftPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareleft = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipesquareleft == true) {


						mChangeDrainagePipeSquareLeftSelect = true;


					}
					else {

						mChangeDrainagePipeSquareLeftSelect = false;

					}
				}

			}




			//Square Right

			//MOUSEOVER

			//Check if mouse is in button
			bool insideshoppipesquareright = true;

			//Mouse is right of the button
			if (x < mDrainagePipeSquareRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareright = false;
			}
			//Mouse is  of the button
			else if (x > mDrainagePipeSquareRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
			{
				insideshoppipesquareright = false;
			}
			//Mouse above the button
			else if (y < mDrainagePipeSquareRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareright = false;
			}
			//Mouse below the button
			else if (y > mDrainagePipeSquareRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
			{
				insideshoppipesquareright = false;
			}

			//Mouse is outside button
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (insideshoppipesquareright == true) {

					//mStructureSelect = true;
					mChangeDrainagePipeSquareRightMouseOver = true;

				}
				else {

					mChangeDrainagePipeSquareRightMouseOver = false;

				}
			}



			//SELECTION

			if (mInput->MouseButtonPressed(InputManager::left)) {

				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);



				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insideshoppipesquareright = true;

				//Mouse is right of the button
				if (x < mDrainagePipeSquareRightPosition.x - PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareright = false;
				}
				//Mouse is  of the button
				else if (x > mDrainagePipeSquareRightPosition.x + PIPE_SHOP_SELECT_WIDTH)
				{
					insideshoppipesquareright = false;
				}
				//Mouse above the button
				else if (y < mDrainagePipeSquareRightPosition.y - PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareright = false;
				}
				//Mouse below the button
				else if (y > mDrainagePipeSquareRightPosition.y + PIPE_SHOP_SELECT_HEIGHT)
				{
					insideshoppipesquareright = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insideshoppipesquareright == true) {


						mChangeDrainagePipeSquareRightSelect = true;
						


					}
					else {

						mChangeDrainagePipeSquareRightSelect = false;


					}
				}

			}











}








	







void InteractionMap::HandlePipePlacement() {


	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Find the targeted tile the player chose
	

		bool mPositionSelect = false;

		if (mInput->MouseButtonPressed(InputManager::right)) {


			for (int row = 0; row < 25; row++)
			{


				for (int column = 0; column < 16; column++)
				{


					if (x < 840 && x > 640 && y < 883 && y > 720) {

						break;
					}

					int horizontal = row * 34;
					int vertical = column * 34;

					//Check if mouse is in button
					bool inside = true;

					if (mPositionSelect == true) {
						break;
					}

					//Mouse is left of the button
					if (x < mPosition.x - SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse is right of the button
					else if (x > mPosition.x + SELECT_WIDTH - horizontal)
					{
						inside = false;
					}
					//Mouse above the button
					else if (y < mPosition.y - SELECT_HEIGHT - vertical)
					{
						inside = false;
					}
					//Mouse below the button
					else if (y > mPosition.y + SELECT_HEIGHT - vertical)
					{
						inside = false;
					}

					//Mouse is outside button
					if (SDL_MOUSEBUTTONDOWN)
					{
						if (inside == true) {


							//??????????????????????????
							mStructurePositionSelect = true;
							//??????????????????????????

							mStructurePositionTargetX = row;
							mStructurePositionTargetY = column;

							int selectrow = mStructurePositionSelectX;
							int selectcolumn = mStructurePositionSelectY;

							mStructurePositionValue = mPipeMap[selectrow][selectcolumn];
							int mStructurePointTransferValue = mFloodValueMap[selectrow][selectcolumn];

							//FILTER FOR UNITS RESTRICTED MOVEMENT



							//IF THERE IS NO WATER, AND THERE IS NO UNIT ALREADY PLACED
							if (mTileMap[row][column] != 0 && mPipeMap[row][column] == 0) {





								//CHECK WHICH PIPE IS SELECTED
								if (mChangeDrainagePipeVUpSelect == true) {

									mPipeMap[row][column] = 1;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeVDownSelect == true) {

									mPipeMap[row][column] = 2;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeHRightSelect == true) {

									mPipeMap[row][column] = 3;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeHLeftSelect == true) {

									mPipeMap[row][column] = 4;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCROneDownSelect == true) {

									mPipeMap[row][column] = 5;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCROneRightSelect == true) {

									mPipeMap[row][column] = 6;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRTwoDownSelect == true) {

									mPipeMap[row][column] = 7;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRTwoLeftSelect == true) {

									mPipeMap[row][column] = 8;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRThreeUpSelect == true) {

									mPipeMap[row][column] = 9;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRThreeLeftSelect == true) {

									mPipeMap[row][column] = 10;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRFourUpSelect == true) {

									mPipeMap[row][column] = 11;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeCRFourRightSelect == true) {

									mPipeMap[row][column] = 12;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTOneDownSelect == true) {

									mPipeMap[row][column] = 13;
									mDollarValue = mDollarValue - 40;
									mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTOneRightSelect == true) {

								mPipeMap[row][column] = 14;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTOneLeftSelect == true) {

								mPipeMap[row][column] = 15;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTTwoDownSelect == true) {

								mPipeMap[row][column] = 16;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTTwoUpSelect == true) {

								mPipeMap[row][column] = 17;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTTwoLeftSelect == true) {

								mPipeMap[row][column] = 18;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTThreeDownSelect == true) {

								mPipeMap[row][column] = 19;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTThreeUpSelect == true) {

								mPipeMap[row][column] = 20;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTThreeRightSelect == true) {

								mPipeMap[row][column] = 21;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTFourLeftSelect == true) {

								mPipeMap[row][column] = 22;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTFourUpSelect == true) {

								mPipeMap[row][column] = 23;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeTFourRightSelect == true) {

								mPipeMap[row][column] = 24;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeSquareUpSelect == true) {

								mPipeMap[row][column] = 25;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeSquareDownSelect == true) {

								mPipeMap[row][column] = 26;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeSquareLeftSelect == true) {

								mPipeMap[row][column] = 27;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}
								else if (mChangeDrainagePipeSquareRightSelect == true) {

								mPipeMap[row][column] = 28;
								mDollarValue = mDollarValue - 40;
								mDollarInterface->Scoreboard::Score(mDollarValue);


								}

								//Select new tile

								mTileHighlight->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
								mTileHighlightOn = true;

								int tileTextValue = mTileMap[row][column];

								switch (tileTextValue)
								{
								case 0:
									mTileText = mWaterText;
									break;
								case 1:
									mTileText = mDirtText;
									break;
								case 2:
									mTileText = mGrassText;
									break;
								case 3:
									mTileText = mStreetText;
									break;
								case 4:
									mTileText = mStreetText;
									break;
								case 5:
									mTileText = mStreetText;
									break;
								default:
									break;
								}

								mStructurePositionSelectX = row;
								mStructurePositionSelectY = column;

								//Unselect Shop Buttons
								mChangeDrainagePipeVUpSelect = false;
								mChangeDrainagePipeVDownSelect = false;
								mChangeDrainagePipeHRightSelect = false;
								mChangeDrainagePipeHLeftSelect = false;
								mChangeDrainagePipeCROneDownSelect = false;
								mChangeDrainagePipeCROneRightSelect = false;
								mChangeDrainagePipeCRTwoDownSelect = false;
								mChangeDrainagePipeCRTwoLeftSelect = false;
								mChangeDrainagePipeCRThreeUpSelect = false;
								mChangeDrainagePipeCRThreeLeftSelect = false;
								mChangeDrainagePipeCRFourUpSelect = false;
								mChangeDrainagePipeCRFourRightSelect = false;
								mChangeDrainagePipeTOneDownSelect = false;
								mChangeDrainagePipeTOneLeftSelect = false;
								mChangeDrainagePipeTOneRightSelect = false;
								mChangeDrainagePipeTTwoUpSelect = false;
								mChangeDrainagePipeTTwoDownSelect = false;
								mChangeDrainagePipeTTwoLeftSelect = false;
								mChangeDrainagePipeTThreeUpSelect = false;
								mChangeDrainagePipeTThreeDownSelect = false;
								mChangeDrainagePipeTThreeRightSelect = false;
								mChangeDrainagePipeTFourRightSelect = false;
								mChangeDrainagePipeTFourLeftSelect = false;
								mChangeDrainagePipeTFourUpSelect = false;
								mChangeDrainagePipeSquareUpSelect = false;
								mChangeDrainagePipeSquareDownSelect = false;
								mChangeDrainagePipeSquareLeftSelect = false;
								mChangeDrainagePipeSquareRightSelect = false;

							}



						}
					}
				}
			}

		}

	




}



void InteractionMap::HandleContaminantMenuSelect() {

	//MOUSEOVER

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Check if mouse is in button
	bool insidecontaminantmenu = true;

	//Mouse is left of the button
	if (x < mContaminantMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
	{
		insidecontaminantmenu = false;
	}
	//Mouse is right of the button
	else if (x > mContaminantMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
	{
		insidecontaminantmenu = false;
	}
	//Mouse above the button
	else if (y < mContaminantMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
	{
		insidecontaminantmenu = false;
	}
	//Mouse below the button
	else if (y > mContaminantMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
	{
		insidecontaminantmenu = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidecontaminantmenu == true) {


			mContaminantMenuMouseOver = true;

		}
		else {

			mContaminantMenuMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insidecontaminantmenu = true;

				//Mouse is left of the button
				if (x < mContaminantMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
				{
					insidecontaminantmenu = false;
				}
				//Mouse is right of the button
				else if (x > mContaminantMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
				{
					insidecontaminantmenu = false;
				}
				//Mouse above the button
				else if (y < mContaminantMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
				{
					insidecontaminantmenu = false;
				}
				//Mouse below the button
				else if (y > mContaminantMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
				{
					insidecontaminantmenu = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insidecontaminantmenu == true) {


						mContaminantMenuSelect = true;


					}
					else {

						if (x > 334 || x < 80 || y > 878 || y < 726) {

							mContaminantMenuSelect = false;

						}
					}
				}


			}


}



void  InteractionMap::HandleSewageShopSelect() {


	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);



	//Filter

		//MOUSEOVER

		//Check if mouse is in button
	bool insidefilter = true;

	//Mouse is left of the button
	if (x < mFilterPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insidefilter = false;
	}
	//Mouse is right of the button
	else if (x > mFilterPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insidefilter = false;
	}
	//Mouse above the button
	else if (y < mFilterPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insidefilter = false;
	}
	//Mouse below the button
	else if (y > mFilterPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insidefilter = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidefilter == true) {

			//mStructureSelect = true;
			mChangeFilterMouseOver = true;

		}
		else {

			mChangeFilterMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insidefilter = true;

		//Mouse is left of the button
		if (x < mFilterPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insidefilter = false;
		}
		//Mouse is right of the button
		else if (x > mFilterPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insidefilter = false;
		}
		//Mouse above the button
		else if (y < mFilterPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insidefilter = false;
		}
		//Mouse below the button
		else if (y > mFilterPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insidefilter = false;
		}


		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insidefilter == true) {


				mChangeFilterSelect = true;


			}
			else {

				mChangeFilterSelect = false;

			}
		}


	}




}



void InteractionMap::HandlePowerMenuSelect() {

	//MOUSEOVER

	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Check if mouse is in button
	bool insidepowermenu = true;

	//Mouse is left of the button
	if (x < mPowerMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
	{
		insidepowermenu = false;
	}
	//Mouse is right of the button
	else if (x > mPowerMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
	{
		insidepowermenu = false;
	}
	//Mouse above the button
	else if (y < mPowerMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
	{
		insidepowermenu = false;
	}
	//Mouse below the button
	else if (y > mPowerMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
	{
		insidepowermenu = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidepowermenu == true) {


			mPowerMenuMouseOver = true;

		}
		else {

			mPowerMenuMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


				//MOVEMENT BUTTON

				//Check if mouse is in button
				bool insidepowermenu = true;

				//Mouse is left of the button
				if (x < mPowerMenuPosition.x - PIPE_MENU_SELECT_WIDTH)
				{
					insidepowermenu = false;
				}
				//Mouse is right of the button
				else if (x > mPowerMenuPosition.x + PIPE_MENU_SELECT_WIDTH)
				{
					insidepowermenu = false;
				}
				//Mouse above the button
				else if (y < mPowerMenuPosition.y - PIPE_MENU_SELECT_HEIGHT)
				{
					insidepowermenu = false;
				}
				//Mouse below the button
				else if (y > mPowerMenuPosition.y + PIPE_MENU_SELECT_HEIGHT)
				{
					insidepowermenu = false;
				}

				//Mouse is outside button
				if (SDL_MOUSEBUTTONDOWN)
				{
					if (insidepowermenu == true) {


						mPowerMenuSelect = true;


					}
					else {


						if (x > 334 || x < 80 || y > 878 || y < 726) {

							mPowerMenuSelect = false;

						}

					}
				}


			}



	
		//}


	//}






}



void InteractionMap::HandlePowerShopSelect() {


	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);



	//Generator

		//MOUSEOVER

		//Check if mouse is in button
	bool insidegenerator = true;

	//Mouse is left of the button
	if (x < mGeneratorPosition.x - PIPE_SHOP_SELECT_WIDTH)
	{
		insidegenerator = false;
	}
	//Mouse is right of the button
	else if (x > mGeneratorPosition.x + PIPE_SHOP_SELECT_WIDTH)
	{
		insidegenerator = false;
	}
	//Mouse above the button
	else if (y < mGeneratorPosition.y - PIPE_SHOP_SELECT_HEIGHT)
	{
		insidegenerator = false;
	}
	//Mouse below the button
	else if (y > mGeneratorPosition.y + PIPE_SHOP_SELECT_HEIGHT)
	{
		insidegenerator = false;
	}

	//Mouse is outside button
	if (SDL_MOUSEBUTTONDOWN)
	{
		if (insidegenerator == true) {

			//mStructureSelect = true;
			mChangeGeneratorMouseOver = true;

		}
		else {

			mChangeGeneratorMouseOver = false;

		}
	}



	//SELECTION

	if (mInput->MouseButtonPressed(InputManager::left)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//MOVEMENT BUTTON

		//Check if mouse is in button
		bool insidegenerator = true;

		//Mouse is left of the button
		if (x < mGeneratorPosition.x - PIPE_SHOP_SELECT_WIDTH)
		{
			insidegenerator = false;
		}
		//Mouse is right of the button
		else if (x > mGeneratorPosition.x + PIPE_SHOP_SELECT_WIDTH)
		{
			insidegenerator = false;
		}
		//Mouse above the button
		else if (y < mGeneratorPosition.y - PIPE_SHOP_SELECT_HEIGHT)
		{
			insidegenerator = false;
		}
		//Mouse below the button
		else if (y > mGeneratorPosition.y + PIPE_SHOP_SELECT_HEIGHT)
		{
			insidegenerator = false;
		}


		//Mouse is outside button
		if (SDL_MOUSEBUTTONDOWN)
		{
			if (insidegenerator == true) {


				mChangeGeneratorSelect = true;


			}
			else {

				mChangeGeneratorSelect = false;

			}
		}


	}


















}








void InteractionMap::Update() {




	mStageTimer += mTimer->DeltaTime();
	mFloodTimer += mTimer->DeltaTime();
	mDrainTimer += mTimer->DeltaTime();
	
	mWaterMovementTimer += mTimer->DeltaTime();


	//mPlayLevelData->main();

	HandleHouseFloodLoss();
	

	mAnimatedUtilityManInterface->Update();

	if(mFloodLevelOne)
	mFloodLevelOne->Update();

	if (mFloodLevelTwo)
	mFloodLevelTwo->Update();

	if (mFloodLevelThree)
	mFloodLevelThree->Update();


	


	if (mStageTimer >= 5.0f) {

		
		HandleRainSpawn();



	}



	 
	if (mFloodTimer >= 2.0f) {

		

		HandleFloodValue();
		//printf("Flood value incremented at rain position \n");

		mFloodTimer = 0.0f;

	}

	if (mDrainTimer >= 1.0f) {

		//printf("asd");
		HandleDrain();

		mDrainTimer = 0.0f;


	}
	
	HandleCarSpawn();
	HandleHouseSpawn();
	//Get mouse position
	//int x, y;
	//SDL_GetMouseState(&x, &y);
	//HandleButtonSelect(x, y);
	//HandleStructureSelect(x, y);


	HandleTileSelect();
	HandlePipeSelect();

	HandleStructureSelect();
	HandlePipeMenuSelect();
	HandleContaminantMenuSelect();
	HandlePowerMenuSelect();

	if (mPipeMenuSelect == true) {

		HandlePipeShopSelect();
	}


	if (mContaminantMenuSelect == true) {

		HandleSewageShopSelect();
	}



	if (mPowerMenuSelect == true) {

		HandlePowerShopSelect();
	}

	HandlePipePlacement();
	HandleMovement();
	HandleAction();
	LoadContourMap(mContourMap);
	LoadPipeMap(mPipeMap);
	LoadStructureMap(mStructureMap);
	mSewageMap->Render();
	mPowerMap->Update();
	LoadFloodValueMap(mFloodValueMap);

}


void InteractionMap::Render() {

	if (mStageTimer >= 5.0f) {


		mRaindrops->Render();
		//mRaindropsTwo->Render();
		

	}

	//mTestText1->Render();
	//mTestText2->Render();



	//mUtilityManInterface->Render();
	mAnimatedUtilityManInterface->Render();

	if(mCar)
	mCar->Render();

	if (mCarTwo)
	mCarTwo->Render();


	mDollarInterface->Render();
	mDollarSignInterface->Render();
	mFundingText->Render();

	if (mGameOverTimer >= mGameOverLabelOnScreen)
		mGameOverLabel->Render();



	DrawPipeMap();
	DrawContourMap();
	DrawStructureMap();

	mSewageMap->Render();
	mPowerMap->Render();

	DrawContaminantMap();

	if (mChangeTileSelect == true) {

		mTileText->Render();
		mTileInterfaceTexture->Render();
		mTileHighlight->Render();
		
		mFloodLabelText->Render();
		mFloodValue->Render();

		mContaminantLabelText->Render();
		mContaminantValue->Render();
		
	}


	if (mChangeDrainageSelect == true) {


		if (mDrainageInterface) {

			mDrainageInterface->Render();
		}

		if (mDrainageText) {
			mDrainageText->Render();
		}

		if (mDrainageMenuSellText) {
			mDrainageMenuSellText->Render();
		}

		if (mDrainageMenuToggleText) {
			mDrainageMenuToggleText->Render();
		}


	}

	if (mChangeStructureSelect == true) {

		if (mStructureInterface) {
			mStructureInterface->Render();
		}

		if (mStructureText) {
			mStructureText->Render();
		}

		if (mStructureSubText) {
			mStructureSubText->Render();
		}



	}


	

	//UNIT MENU


	//MOVEMENT

	//Filter for deselecting
	if (mStructureMenuMovementText) {

		//Condition for mouse hover graphic
		if (mChangeStructureMenuMovementMouseOver == true) {

			mStructureMenuMovementBackgroundHighlight->Render();
			DrawMovementTiles();

		}
		//Condition for select graphic
		else if ((mChangeStructureMenuMovementSelect == true)) {

			mStructureMenuMovementBackgroundSelect->Render();
			DrawMovementTiles();

		}
		else {

			mStructureMenuMovementBackground->Render();

		}

	}


	//ACTION

	if (mStructureMenuActionText) {

		//Condition for mouse hover graphic
		if (mChangeStructureMenuActionMouseOver == true) {

			mStructureMenuActionBackgroundHighlight->Render();
			DrawActionTiles();

		}
		//Condition for select graphic
		else if ((mChangeStructureMenuActionSelect == true)) {

			mStructureMenuActionBackgroundSelect->Render();
			DrawActionTiles();

		}
		else {

			mStructureMenuActionBackground->Render();

		}


	}

	//ITEM

	if (mStructureMenuItemText) {

		//Condition for mouse hover graphic
		if (mChangeStructureMenuItemMouseOver == true) {

			mStructureMenuItemBackgroundHighlight->Render();

		}
		//Condition for select graphic
		else if ((mChangeStructureMenuItemSelect == true)) {

			mStructureMenuItemBackgroundSelect->Render();

		}
		else {

			mStructureMenuItemBackground->Render();
		}

	}


	//STATUS

	if (mStructureMenuStatusText) {

		//Condition for mouse hover graphic
		if (mChangeStructureMenuStatusMouseOver == true) {

			mStructureMenuStatusBackgroundHighlight->Render();

		}
		//Condition for select graphic
		else if ((mChangeStructureMenuStatusSelect == true)) {

			mStructureMenuStatusBackgroundSelect->Render();

		}
		else {

			mStructureMenuStatusBackground->Render();
		}

	}


	if (mStructureMenuMovementText) {

		if (mStructureMenuTotal == 4) {

			mStructureMenuMovementText->Render();

			mStructureMenuActionText->Render();

			mStructureMenuStatusText->Render();

			mStructureMenuItemText->Render();
		}


	}



		
	//PIPE MENU

	//Condition for mouse hover graphic
	if (mPipeMenuMouseOver == true) {

		mPipeMenuBackgroundHighlight->Render();

	}
	//Condition for select graphic
	else if ((mPipeMenuSelect == true)) {

		mPipeMenuBackgroundSelect->Render();

	}
	else {

		mPipeMenuBackground->Render();
	}
		



	if (mPipeMenuSelect == true) {


		mPipeShopBackground->Render();





		
		//PIPE SHOP


		//Vertical Pipe Up

		//Condition for mouse hover graphic
		if (mChangeDrainagePipeVUpMouseOver == true) {

			mDrainagePipeVUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeVUpSelect == true)) {

			mDrainagePipeVUpSelect->Render();

		}
		else {

			mDrainagePipeVUpNONSelect->Render();
		}

		
		//Vertical Pipe Down

		//Condition for mouse hover graphic
		if (mChangeDrainagePipeVDownMouseOver == true) {

			mDrainagePipeVDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeVDownSelect == true)) {

			mDrainagePipeVDownSelect->Render();

		}
		else {

			mDrainagePipeVDownNONSelect->Render();
		}




		//Horizontal Pipe Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeHRightMouseOver == true) {

			mDrainagePipeHRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeHRightSelect == true)) {

			mDrainagePipeHRightSelect->Render();

		}
		else {

			mDrainagePipeHRightNONSelect->Render();
		}


		//Horizontal Pipe Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeHLeftMouseOver == true) {

			mDrainagePipeHLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeHLeftSelect == true)) {

			mDrainagePipeHLeftSelect->Render();

		}
		else {

			mDrainagePipeHLeftNONSelect->Render();
		}




		//Corner 1 Down



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCROneDownMouseOver == true) {

			mDrainagePipeCROneDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCROneDownSelect == true)) {

			mDrainagePipeCROneDownSelect->Render();

		}
		else {

			mDrainagePipeCROneDownNONSelect->Render();
		}

	
		//Corner 1 Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCROneRightMouseOver == true) {

			mDrainagePipeCROneRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCROneRightSelect == true)) {

			mDrainagePipeCROneRightSelect->Render();

		}
		else {

			mDrainagePipeCROneRightNONSelect->Render();
		}





		//Corner 2 Down



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRTwoDownMouseOver == true) {

			mDrainagePipeCRTwoDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRTwoDownSelect == true)) {

			mDrainagePipeCRTwoDownSelect->Render();

		}
		else {

			mDrainagePipeCRTwoDownNONSelect->Render();
		}





		//Corner 2 Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRTwoLeftMouseOver == true) {

			mDrainagePipeCRTwoLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRTwoLeftSelect == true)) {

			mDrainagePipeCRTwoLeftSelect->Render();

		}
		else {

			mDrainagePipeCRTwoLeftNONSelect->Render();
		}





		//Corner 3 Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRThreeUpMouseOver == true) {

			mDrainagePipeCRThreeUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRThreeUpSelect == true)) {

			mDrainagePipeCRThreeUpSelect->Render();

		}
		else {

			mDrainagePipeCRThreeUpNONSelect->Render();
		}




		//Corner 3 Left	



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRThreeLeftMouseOver == true) {

			mDrainagePipeCRThreeLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRThreeLeftSelect == true)) {

			mDrainagePipeCRThreeLeftSelect->Render();

		}
		else {

			mDrainagePipeCRThreeLeftNONSelect->Render();
		}






		//Corner 4 Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRFourUpMouseOver == true) {

			mDrainagePipeCRFourUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRFourUpSelect == true)) {

			mDrainagePipeCRFourUpSelect->Render();

		}
		else {

			mDrainagePipeCRFourUpNONSelect->Render();
		}




		//Corner 4 Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeCRFourRightMouseOver == true) {

			mDrainagePipeCRFourRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeCRFourRightSelect == true)) {

			mDrainagePipeCRFourRightSelect->Render();

		}
		else {

			mDrainagePipeCRFourRightNONSelect->Render();
		}



		//T Shape One Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTOneRightMouseOver == true) {

			mDrainagePipeTOneRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTOneRightSelect == true)) {

			mDrainagePipeTOneRightSelect->Render();

		}
		else {

			mDrainagePipeTOneRightNONSelect->Render();
		}



		//T Shape One Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTOneLeftMouseOver == true) {

			mDrainagePipeTOneLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTOneLeftSelect == true)) {

			mDrainagePipeTOneLeftSelect->Render();

		}
		else {

			mDrainagePipeTOneLeftNONSelect->Render();
		}



		//T Shape One Down



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTOneDownMouseOver == true) {

			mDrainagePipeTOneDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTOneDownSelect == true)) {

			mDrainagePipeTOneDownSelect->Render();

		}
		else {

			mDrainagePipeTOneDownNONSelect->Render();
		}





		//T Shape Two Down 



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTTwoDownMouseOver == true) {

			mDrainagePipeTTwoDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTTwoDownSelect == true)) {

			mDrainagePipeTTwoDownSelect->Render();

		}
		else {

			mDrainagePipeTTwoDownNONSelect->Render();
		}






		//T Shape Two Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTTwoLeftMouseOver == true) {

			mDrainagePipeTTwoLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTTwoLeftSelect == true)) {

			mDrainagePipeTTwoLeftSelect->Render();

		}
		else {

			mDrainagePipeTTwoLeftNONSelect->Render();
		}




		//T Shape Two Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTTwoUpMouseOver == true) {

			mDrainagePipeTTwoUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTTwoUpSelect == true)) {

			mDrainagePipeTTwoUpSelect->Render();

		}
		else {

			mDrainagePipeTTwoUpNONSelect->Render();
		}




		//T Shape Three Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTThreeUpMouseOver == true) {

			mDrainagePipeTThreeUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTThreeUpSelect == true)) {

			mDrainagePipeTThreeUpSelect->Render();

		}
		else {

			mDrainagePipeTThreeUpNONSelect->Render();
		}






		//T Shape Three Down



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTThreeDownMouseOver == true) {

			mDrainagePipeTThreeDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTThreeDownSelect == true)) {

			mDrainagePipeTThreeDownSelect->Render();

		}
		else {

			mDrainagePipeTThreeDownNONSelect->Render();
		}






		//T Shape Three Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTThreeRightMouseOver == true) {

			mDrainagePipeTThreeRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTThreeRightSelect == true)) {

			mDrainagePipeTThreeRightSelect->Render();

		}
		else {

			mDrainagePipeTThreeRightNONSelect->Render();
		}







		//T Shape Four Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTFourUpMouseOver == true) {

			mDrainagePipeTFourUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTFourUpSelect == true)) {

			mDrainagePipeTFourUpSelect->Render();

		}
		else {

			mDrainagePipeTFourUpNONSelect->Render();
		}







		//T Shape Four Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTFourLeftMouseOver == true) {

			mDrainagePipeTFourLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTFourLeftSelect == true)) {

			mDrainagePipeTFourLeftSelect->Render();

		}
		else {

			mDrainagePipeTFourLeftNONSelect->Render();
		}






		//T Shape Four Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeTFourRightMouseOver == true) {

			mDrainagePipeTFourRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeTFourRightSelect == true)) {

			mDrainagePipeTFourRightSelect->Render();

		}
		else {

			mDrainagePipeTFourRightNONSelect->Render();
		}




		//Square Up



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeSquareUpMouseOver == true) {

			mDrainagePipeSquareUpMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeSquareUpSelect == true)) {

			mDrainagePipeSquareUpSelect->Render();

		}
		else {

			mDrainagePipeSquareUpNONSelect->Render();
		}



		//Square Down



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeSquareDownMouseOver == true) {

			mDrainagePipeSquareDownMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeSquareDownSelect == true)) {

			mDrainagePipeSquareDownSelect->Render();

		}
		else {

			mDrainagePipeSquareDownNONSelect->Render();
		}







		//Square Left



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeSquareLeftMouseOver == true) {

			mDrainagePipeSquareLeftMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeSquareLeftSelect == true)) {

			mDrainagePipeSquareLeftSelect->Render();

		}
		else {

			mDrainagePipeSquareLeftNONSelect->Render();
		}




		//Square Right



		//Condition for mouse hover graphic
		if (mChangeDrainagePipeSquareRightMouseOver == true) {

			mDrainagePipeSquareRightMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeDrainagePipeSquareRightSelect == true)) {

	
			mDrainagePipeSquareRightSelect->Render();

		}
		else {

			mDrainagePipeSquareRightNONSelect->Render();
		}







	}



	//Contaminant Shop Menu


	//Condition for mouse hover graphic
	if (mContaminantMenuMouseOver == true) {

		mContaminantMenuBackgroundHighlight->Render();

	}
	//Condition for select graphic
	else if ((mContaminantMenuSelect == true)) {

		mContaminantMenuBackgroundSelect->Render();

	}
	else {

		mContaminantMenuBackground->Render();
	}

	if (mContaminantMenuSelect == true) {


		mPipeShopBackground->Render();






		//Condition for mouse hover graphic
		if (mChangeFilterMouseOver == true) {

			mFilterMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeFilterSelect == true)) {


			mFilterSelect->Render();

		}
		else {

			mFilterNONSelect->Render();
		}












	}







	//Power Shop Menu


	//Condition for mouse hover graphic
	if (mPowerMenuMouseOver == true) {

		mPowerMenuBackgroundHighlight->Render();

	}
	//Condition for select graphic
	else if ((mPowerMenuSelect == true)) {

		mPowerMenuBackgroundSelect->Render();

	}
	else {

		mPowerMenuBackground->Render();
	}


	if (mPowerMenuSelect == true) {


		mPipeShopBackground->Render();








		//Condition for mouse hover graphic
		if (mChangeGeneratorMouseOver == true) {

			mGeneratorMouseOver->Render();

		}
		//Condition for select graphic
		else if ((mChangeGeneratorSelect == true)) {


			mGeneratorSelect->Render();

		}
		else {

			mGeneratorNONSelect->Render();
		}






	}





}