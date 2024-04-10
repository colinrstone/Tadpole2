#include "Car.h"

Car* Car::sInstance = NULL;


Car* Car::Instance(int value, int row, int column) {


	//if (sInstance == NULL)
		sInstance = new Car(value, row, column);

	return sInstance;
}


void Car::Release() {

	delete sInstance;
	sInstance = NULL;
}


Car::Car(int value, int row, int column) {

	mTimer = Timer::Instance();
	mAudio = NULL;



	mCarValue = value;
	mCarRow = row;
	mCarColumn = column;


	mCar = NULL;

	mCarDown = new AnimatedTexture("bluecardownspritesheet.png", 0, 0, 32, 38, 5, 0.95f, AnimatedTexture::horizontal);
	mCarDown->Parent(this);
	mCarDown->Scale(Vector2(0.55f, 0.75f));
	//mCarDown->Pos(Vector2(50, 200));

	mCarUp = new AnimatedTexture("bluecarupspritesheet.png", 0, 0, 32, 38, 5, 0.95f, AnimatedTexture::horizontal);
	mCarUp->Parent(this);
	mCarUp->Scale(Vector2(0.55f, 0.75f));

	mCarLeft = new AnimatedTexture("bluecarleftspritesheet.png", 0, 0, 32, 38, 5, 0.95f, AnimatedTexture::horizontal);
	mCarLeft->Parent(this);
	mCarLeft->Scale(Vector2(0.85f, 0.85f));

	mCarRight = new AnimatedTexture("bluecarrightspritesheet.png", 0, 0, 32, 38, 5, 0.95f, AnimatedTexture::horizontal);
	mCarRight->Parent(this);
	mCarRight->Scale(Vector2(0.85f, 0.85f));

	mCarMovingUp = NULL;
	mCarMovingDown = NULL;
	mCarMovingLeft = NULL;
	mCarMovingRight = NULL;

	mCarSpawned = false;

	
	mCarPosition.x = NULL;
	mCarPosition.y = NULL;


	mVisible = true;
	//mAnimating = false;


	mMoveSpeed = 75.0f;
	mMoveBounds = Vector2(100, 400);

}


Car::~Car() {

	mTimer = NULL;
	mAudio = NULL;

	mCarValue = NULL;
	mCarRow = NULL;
	mCarColumn = NULL;

	mCar = NULL;
	mCarDown = NULL;
	mCarUp = NULL;
	mCarLeft = NULL;
	mCarRight = NULL;

	mCarMovingUp = NULL;
	mCarMovingDown = NULL;
	mCarMovingLeft = NULL;
	mCarMovingRight = NULL;

	mCarSpawned = false;



	mCarPosition.x = NULL;
	mCarPosition.y = NULL;

	mVisible = NULL;

	mMoveSpeed = NULL;
	mMoveBounds = NULL;

}



void Car::HandleCarMovement() {


	if (mCarMovingDown == true) {

		Vector2 turnpoint = Pos();

		if (turnpoint.y > 300)
		{
				
			mCarMovingDown = false;
			mCarMovingLeft = true;
			mCar = mCarLeft;
			mCar->Pos(Vector2(600.0f, 80.0f));
		}
		else {

			Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime());

		}

	}
	else if (mCarMovingUp == true) {

		Translate(-VEC2_UP * mMoveSpeed * mTimer->DeltaTime());


	}
	else if (mCarMovingLeft == true) {

		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());

	}

	else if (mCarMovingRight == true) {

		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());

	}


}


void Car::SpawnCar() {



	switch (mCarValue)
	{
	case 1:

		//Bottom Row
		mCarPosition.x = ((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * mCarRow) + 6.0f;
		mCarPosition.y = ((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * mCarColumn);
		

		mCar = mCarUp;
		mCar->Pos(Vector2(mCarPosition.x, mCarPosition.y));

		mCarMovingUp = true;
		mCarMovingDown = NULL;
		mCarMovingLeft = NULL;
		mCarMovingRight = NULL;

		break;

	case 2:

		//Right Row
		mCarPosition.x = ((Graphics::Instance()->SCREEN_WIDTH) * 0.90);

		mCarPosition.y = ((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * mCarColumn) - 10.0f;


		mCar = mCarLeft;
		mCar->Pos(Vector2(mCarPosition.x, mCarPosition.y));
		mCarMovingUp = NULL;
		mCarMovingDown = NULL;
		mCarMovingLeft = true;
		break;

	case 3:

		//Top Row
		mCarPosition.x = ((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * mCarRow) - 6.0f;
		mCarPosition.y = ((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * mCarColumn);

		mCar = mCarDown;
		mCar->Pos(Vector2(mCarPosition.x, mCarPosition.y));
		mCarMovingUp = NULL;
		mCarMovingDown = true;
		mCarMovingLeft = NULL;
		mCarMovingRight = NULL;
		break;

	case 4:

		//Left Row
		mCarPosition.x = ((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * mCarRow);
		mCarPosition.y = ((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * mCarColumn);

		mCar = mCarRight;
		mCar->Pos(Vector2(mCarPosition.x, mCarPosition.y));
		mCarMovingUp = NULL;
		mCarMovingDown = NULL;
		mCarMovingLeft = NULL;
		mCarMovingRight = true;
		break;

	default:
		break;


	}


	mCarSpawned = true;


}



void Car::Update() {



	if(mCarSpawned == false)
	SpawnCar();


	if (mCar) {

		mCar->Update();


		HandleCarMovement();

	}



}

void Car::Render() {


		
	if (mCar) {

		if(mVisible)
		mCar->Render();


		}


}
    