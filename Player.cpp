#include "Player.h"

Player& Player::Instance() {
	static Player instance;
	return instance;
}

Player::Player() : mPlayerPosition(Vector2(960.0f, 540.0f)) {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = true;

	mScore = 0;
	mLives = 0;
	
	//mPlayerPosition = ;


	mPlayerIdle = new AnimatedTexture("pocketmanidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mPlayerIdle->Parent(this); 
    mPlayerIdle->Pos(local);

	mPlayerIdleUp = new AnimatedTexture("pocketmanidleup.png", 0, 0, 12, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerIdleUp->Parent(this);
	mPlayerIdleUp->Pos(local);

	mPlayerIdleDown = new AnimatedTexture("pocketmanidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mPlayerIdleDown->Parent(this);
	mPlayerIdleDown->Pos(local);

	mPlayerIdleLeft = new AnimatedTexture("pocketmanidleleft.png", 0, 0, 12, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerIdleLeft->Parent(this);
	mPlayerIdleLeft->Pos(local);

	mPlayerIdleRight = new AnimatedTexture("pocketmanidleright.png", 0, 0, 12, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerIdleRight->Parent(this);
	mPlayerIdleRight->Pos(local);

	mPlayerAnimate = NULL;
	mIsAnimating = false;

	mPlayerRunDown = new AnimatedTexture("pocketmanrundown.png", 0, 0, 12, 23, 4, 1, AnimatedTexture::vertical);
	mPlayerRunDown->Parent(this);
	mPlayerRunDown->Pos(local);

	mPlayerRunUp = new AnimatedTexture("pocketmanrunup.png", 0, 0, 12, 23, 4, 1, AnimatedTexture::vertical);
	mPlayerRunUp->Parent(this);
	mPlayerRunUp->Pos(local);

	mPlayerRunRight = new AnimatedTexture("pocketmanrunright.png", 0, 0, 12, 23, 4, 1, AnimatedTexture::vertical);
	mPlayerRunRight->Parent(this);
	mPlayerRunRight->Pos(local);

	mPlayerRunLeft = new AnimatedTexture("pocketmanrunleft.png", 0, 0, 12, 23, 4, 1, AnimatedTexture::vertical);
	mPlayerRunLeft->Parent(this);
	mPlayerRunLeft->Pos(local);


	mPlayerJump = new AnimatedTexture("pocketmanjump.png", 0, 0, 32, 32, 8, 1, AnimatedTexture::horizontal);
	mPlayerJump->Parent(this);
	mPlayerJump->Pos(local);

	mIsInteracting = false;

	mInteractionRange = 10.0f;

	mPlayerInteractDown = new AnimatedTexture("pocketmanattackdown.png", 0, 0, 11, 24, 1, 1, AnimatedTexture::vertical);
	mPlayerInteractDown->Parent(this);
	mPlayerInteractDown->Pos(local);

	mPlayerInteract = mPlayerInteractDown;

	mPlayerInteractUp = new AnimatedTexture("pocketmanattackup.png", 0, 0, 12, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerInteractUp->Parent(this);
	mPlayerInteractUp->Pos(local);

	mPlayerInteractRight = new AnimatedTexture("pocketmanattackright.png", 0, 0, 12, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerInteractRight->Parent(this);
	mPlayerInteractRight->Pos(local);

	mPlayerInteractLeft = new AnimatedTexture("pocketmanattackleft.png", 0, 0, 14, 23, 1, 1, AnimatedTexture::vertical);
	mPlayerInteractLeft->Parent(this);
	mPlayerInteractLeft->Pos(local);


	mMoveSpeed = 100.0f;
	mMoveLowerBounds = Vector2(0.0f, 0.0f);
	mMoveUpperBounds = Vector2(1920.0f, 1080.0f);

	mJumpTimer = 0.0f;
	mJumpTimerInterval = 1.0f;

	mInteractionTimer = 0.0f;
	mInteractionTimerInterval = 0.40f;

	mSetIdleDelayTimer = 0.0f;
	mSetIdleDelayTimerInterval = 0.4f;


}

Player::~Player() {

	mTimer = NULL;
	mInput = NULL;

	delete mPlayerIdle;
	mPlayerIdle = NULL;
}

void Player::HandleMovement() {
	Vector2 movement(0.0f, 0.0f);
	float moveSpeed = 1.0f; // Adjust this value as needed

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		movement.x += 1.0f;;
		mPlayerAnimate = mPlayerRunRight;
		mPlayerIdle = mPlayerIdleRight;
		mPlayerPosition.x++;
	}

	if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		movement.x -= 1.0f;;
		mPlayerAnimate = mPlayerRunLeft;
		mPlayerIdle = mPlayerIdleLeft;
		mPlayerPosition.x--;
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP)) {
		movement.y -= 1.0f;;
		mPlayerAnimate = mPlayerRunUp;
		mPlayerIdle = mPlayerIdleUp;
		mPlayerPosition.y++;
	}

	if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
		movement.y += 1.0f;;
		mPlayerAnimate = mPlayerRunDown;
		mPlayerIdle = mPlayerIdleDown;
		mPlayerPosition.y--;

	}

	// Check if any movement keys are pressed
	if (movement.x != 0.0f || movement.y != 0.0f) {
		movement.Normalized(); // Ensure diagonal movement is at the same speed

		// Calculate new position with floating-point values
		Vector2 newPosition = mPlayerPosition + movement * moveSpeed * mTimer->DeltaTime();

		//newPosition.x = std::max(mMoveLowerBounds.x, std::min(newPosition.x, mMoveUpperBounds.x));
		//newPosition.y = std::max(mMoveLowerBounds.y, std::min(newPosition.y, mMoveUpperBounds.y));

		// Update player position with floating-point values
		mPlayerPosition = newPosition;


		// Indicate that the player is animating
		mIsAnimating = true;
	}
	else {
		// No movement keys are pressed, player is not animating
		mIsAnimating = false;
	}


	// Update the enemy's position based on the movement vector
	//Translate(movement * moveSpeed * mTimer->DeltaTime());

	//Vector2 pos = Pos(local);
	//Pos(pos);

	//mPlayerPosition = pos;
}


void Player::HandleJump() {

	if (mInput->KeyDown(SDL_SCANCODE_SPACE) && !mIsAnimating) {
		mJumpTimer = 0.0f;
		mIsAnimating = true;
	}

	if (mIsAnimating) {
		mJumpTimer += mTimer->DeltaTime();

		// Perform the jumping behavior for the specified time interval
		if (mJumpTimer < mJumpTimerInterval) {

			// Apply upward movement or any other desired behavior
			//Translate(-VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
			mPlayerAnimate = mPlayerJump;
		}
		else {

			// End the jump after the time interval has passed
			mIsAnimating = false;
			mPlayerAnimate = NULL;
		}
	}
}


void Player::HandleInteract() {

	if (mInput->KeyDown(SDL_SCANCODE_SPACE) && !mIsInteracting) {
		mInteractionTimer = 0.0f;
		mIsInteracting = true;

	}

	if (mIsInteracting) {
		mInteractionTimer += mTimer->DeltaTime();
		

		// Perform the attacking behavior for the specified time interval
		if (mInteractionTimer < mInteractionTimerInterval) {

			if (mPlayerIdle == mPlayerIdleRight) {

				mPlayerInteract = mPlayerInteractRight;
				//printf("test");

			}
			else if (mPlayerIdle == mPlayerIdleLeft) {

				mPlayerInteract = mPlayerInteractLeft;
				//printf("test");
			}
			else if (mPlayerIdle == mPlayerIdleUp) {

			mPlayerInteract = mPlayerInteractUp;
				//printf("test");
			}
			else if (mPlayerIdle == mPlayerIdleDown) {

				mPlayerInteract = mPlayerInteractDown;
				//printf("test");
			}




	
		}
		else {

			// End the attack after the time interval has passed
			mIsInteracting = false;
			//mPlayerInteract = NULL;
		}
	}






}




Vector2 Player::GetPosition() const {

	return mPlayerPosition;
}

float Player::GetInteractionRange() const {

	return mInteractionRange;
}

void Player::SetPlayerIdle() {


	mSetIdleDelayTimer += mTimer->DeltaTime();

	if (mSetIdleDelayTimer > mSetIdleDelayTimerInterval) {

		mIsInteracting = false;
		mIsAnimating = false;

		mSetIdleDelayTimer = 0.0f;

	}

}


void Player::Visible(bool visible) {

	mVisible = visible;

}


int Player::Score() {

	return mScore;
}

int Player::Lives() {

	return mLives;
}


void Player::AddScore(int change) {

	mScore += change;
}


/*
void Player::SetPlayerPosition(float x, float y) {

	mPlayerPosition.x = x;
	mPlayerPosition.y = y;

}

void Player::SetPlayerPosition(const Vector2& position) {

	mPlayerPosition = position;

}
*/




void Player::Update() {

	//if (mIsJumping)
		//mPlayerJump->Update();

	//HandleJump();
	HandleInteract();
	HandleMovement();

	if (mPlayerInteract)
		mPlayerInteract->Update();

	if(mPlayerAnimate)
	  mPlayerAnimate->Update();

	mPlayerIdle->Update();

	int x = mPlayerPosition.x;
	int y = mPlayerPosition.y;

	//printf(" %i", x);
	//printf(",%i" , y);

	//if (mInput->KeyPressed(SDL_SCANCODE_P)) {
	//	int x = static_cast<int>(mPlayerPosition.x);
	//	int y = static_cast<int>(mPlayerPosition.y);
	//	printf("Player Position: (%i, %i)\n", x, y);
	//}

}


void Player::Render() {


	if (mIsInteracting)
		mPlayerInteract->Render();
	else if (mIsAnimating)
		mPlayerAnimate->Render();
	else
		mPlayerIdle->Render();


	
}
	