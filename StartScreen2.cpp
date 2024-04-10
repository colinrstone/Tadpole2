#include "StartScreen2.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();


	//Top bar entities

	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mTopBar->Parent(this);



	// logo entities
	mLogo = new Texture("puntlogo.png", 0, 0, 360, 180);
	mAnimatedLogo = new AnimatedTexture("puntlogo.png", 0, 0, 360, 180, 3, 0.35f, AnimatedTexture::vertical);

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));


	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);





	//Play mode entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("New Game", "unispace.ttf", 32, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("Load Game", "unispace.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Cursor.png");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(-175.0f, -35.0f));

	mPlayModes->Parent(this);


	mCursorStartPos = Vector2(mCursor->Pos(local));
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;


	//Bottom bar entities


	mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mNamco = new Texture("Made by Colin Stone", "unispace.ttf", 24, { 200, 0, 0 });

	mRights = new Texture("ALL RIGHTS RESERVED", "unispace bold.ttf", 32, { 230, 230, 230 });

	mNamco->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mNamco->Pos(Vector2(0.0f, 170.0f));
	mRights->Pos(Vector2(0.0f, 230.0f));


	mBotBar->Parent(this);

	//Screen animation variables
    mAnimationStartPos = Vector2(Graphics::Instance()->SCREEN_WIDTH, Graphics::Instance()->SCREEN_HEIGHT);
    mAnimationEndPos = VEC2_ZERO;
    mAnimationTotalTime = 5.0f;
    mAnimationDone = false;

    Pos(mAnimationStartPos);

	ResetAnimation();




}

StartScreen::~StartScreen() {

	//Freeing top bar entities
	delete mTopBar;
	mTopBar = NULL;


	//freeing logo entities

	delete mLogo;
	mLogo = NULL;

	delete mAnimatedLogo;
	mAnimatedLogo = NULL;



	//Freeing play mode entities

	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mCursor;
	mCursor = NULL;

	//freeing bottom bar entities

	delete mBotBar;
	mBotBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mRights;
	mRights = NULL;

}

void StartScreen::ResetAnimation() {

	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;


	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode() {

	return mSelectedMode;
}





void StartScreen::ChangeSelectedMode(int change) {

	mSelectedMode += change;

	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);

}

void StartScreen::Update() {


	if (!mAnimationDone) {

		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
			mAnimationTimer = mAnimationTotalTime;


	}
	else {

		mAnimatedLogo->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
			ChangeSelectedMode(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP))
			ChangeSelectedMode(-1);
	}

}

void StartScreen::Render() {


	if (!mAnimationDone)
		mLogo->Render();
	else
		mAnimatedLogo->Render();

	mLogo->Render();

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
	mRights->Render();



}
