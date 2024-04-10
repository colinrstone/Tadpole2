#include "Character.h"

Character::Character(int characternumber) {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
  
    mCharacterIsSpeak = false;
    mIsSpeaking = false;

    mCharacterValue = characternumber;
    const std::string TriggerName1 = "TriggerName1";


    switch (characternumber) {
    case 1:  // Tom the Guy One
         
        mCharacter = new AnimatedTexture("enemy.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacter->Parent(this);
        //This is a value relative to the screen origin at the top left being (0,0) and downwards increasing the Y and right increasing the X
        mCharacter->Pos(Vector2(1000.0f, 1000.0f));

        mCharacterIdle = new AnimatedTexture("enemy.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacterIdle->Parent(this);
        mCharacterIdle->Pos(Vector2(1000.0f, 1000.0f));

        mCharacterSpeak = new AnimatedTexture("enemyhit.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacterSpeak->Parent(this);
        mCharacterSpeak->Pos(Vector2(1000.0f, 1000.0f));

        mCharacterSpeakTimer = 0.0f;
        mCharacterSpeakTimerInterval = 1.0f;

        //This is a value relative to where the player starts the level from
        mCharacterPosition = Vector2(971.0f, 407.0f);
        mCharacterRange = 10;

        break;

    case 2:  // Chet the Guy Two
     
        mCharacter = new AnimatedTexture("copycat.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacter->Parent(this);
        mCharacter->Pos(Vector2(500.0f, 500.0f));

        mCharacterIdle = new AnimatedTexture("copycat.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacterIdle->Parent(this);
        mCharacterIdle->Pos(Vector2(500.0f, 500.0f));

        mCharacterSpeak = new AnimatedTexture("copycathit.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
        mCharacterSpeak->Parent(this);
        mCharacterSpeak->Pos(Vector2(500.0f, 500.0f));


        mCharacterSpeakTimer = 0.0f;
        mCharacterSpeakTimerInterval = 1.0f;

        mCharacterPosition = Vector2(842.0f, 545.0f);
        mCharacterRange = 10;

        break;

    default:

        break;
    }




    mScrollSpeed = 200.0f;

}


int Character::GetCharacterValue() {

    return mCharacterValue;
}

Vector2 Character::GetPosition() const {

	return mCharacterPosition;
}
	

float Character::GetInteractRange() const {

	return mCharacterRange;

}

bool Character::IsSpeaking() const {

    return mCharacterIsSpeak;
}

std::vector<std::string> Character::GetDialogue(int zoneValue, int characterValue, int characterOrder, int textboxProgress) {
    Dialogue dialogue;

    if (dialogue.LoadDialogueFromFile("dialogue.csv")) {
        mCharacterDialogue = dialogue.GetCharacterDialogue(zoneValue, characterValue, characterOrder, textboxProgress);

        return mCharacterDialogue;
    }


    // Return an empty vector if loading fails
    return std::vector<std::string>();
}

std::vector<std::string> Character::GetResponses(int zoneValue, int characterValue, int characterOrder, int textboxProgress) {


    //make this a member variable
    Response response;
    if (response.LoadResponsesFromFile("response.csv")) {
        mCharacterResponses = response.GetCharacterResponses(zoneValue, characterValue, characterOrder, textboxProgress); // Assuming character ID is 1

       //std::string test = mCharacterResponses[0];
       //std::cout << test << std::endl;

    }

    return mCharacterResponses;
}



void Character::HandleInteraction() {

    // Change texture to Character talking and set the timer
    mCharacterIsSpeak = true;
    mCharacterSpeakTimer = 0.0f;

}


void Character::HandleCharacterShift() {


    Vector2 movement(0.0f, 0.0f); // Initialize a movement vector

    if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
        movement.x += 1.0f;
        //mCharacterPosition.x++;
    }
    if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
        movement.x -= 1.0f;
       // mCharacterPosition.x--;
    }
    if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
        movement.y -= 1.0f;
        //mCharacterPosition.y++;
    }
    if (mInput->KeyDown(SDL_SCANCODE_UP)) {
        movement.y += 1.0f;
        //mCharacterPosition.y--;
    }

    // Normalize the movement vector to ensure consistent speed in all directions
   	if (movement.x != 0.0f || movement.y != 0.0f) {
        movement.Normalized();
    }

                   Vector2 newPosition = mCharacterPosition + movement * mScrollSpeed * mTimer->DeltaTime();

    // Update player position with floating-point values
    //mCharacterPosition = newPosition;

    // Update the enemy's position based on the movement vector
    Translate(movement * mScrollSpeed * mTimer->DeltaTime());

    Vector2 pos = Pos(local);
    Pos(pos);
}




void Character::StartBattle() {

    // Change texture to Character talking and set the timer
    mCharacterIsSpeak = true;
    mCharacterSpeakTimer = 0.0f;

}


void Character::TakeDamage() {

    mCharacterHealth--;
    printf("Character health is %i/n", mCharacterHealth);

    // Change texture to Character Speak and set the timer
    mCharacterIsSpeak = true;
    mCharacterSpeakTimer = 0.0f;

}

void Character::PlayAttackAnimation() {
    // Switch to the attack animation
    // You can use mCharacterSpeak or mCharacterSpeak to display the attack animation
}


void Character::Update() {

    HandleCharacterShift();

    // Check if the enemy is in hit state
    if (mCharacterIsSpeak) {
        // Update the hit texture
        mCharacterSpeak->Update();


        // Increment the hit timer
        mCharacterSpeakTimer += mTimer->DeltaTime();

        // Check if it's time to reset the hit state
        if (mCharacterSpeakTimer >= mCharacterSpeakTimerInterval) {
            mCharacterIsSpeak = false;
            mCharacterSpeakTimer = 0.0f;
        }
    }
    else {
        // Update the normal texture
        mCharacter->Update();
    }

}

void Character::Render() {

    if (mCharacterIsSpeak == true) 
      mCharacterSpeak->Render();
    else
      mCharacter->Render();
    

}
