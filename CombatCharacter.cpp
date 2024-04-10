// CombatCharacter.cpp
#include "CombatCharacter.h"

CombatCharacter::CombatCharacter() {
    // Initialization logic
    mCharacterTexture = new Texture("copycat.png");
    mCharacterTexture->Parent(this);
    mCharacterTexture->Pos(Vector2(0.0f, 0.0f));


    ResetHealth();
    mAttack = 5;
}

CombatCharacter::~CombatCharacter() {
    // Cleanup logic
    delete mCharacterTexture;
}

void CombatCharacter::TakeTurn(CombatCharacter& target) {
    // Logic for the character's turn
    Attack(target);
}

void CombatCharacter::Attack(CombatCharacter& target) {
    // Logic for attacking the target
    target.TakeDamage(mAttack);
}

bool CombatCharacter::IsDead() const {
    return mHealth <= 0;
}

void CombatCharacter::ResetHealth() {
    mHealth = 100; // Example starting health
}

void CombatCharacter::TakeDamage(int damage) {
    mHealth -= damage;

    

    // Ensure health doesn't go below 0
    if (mHealth < 0) {
        mHealth = 0;
    }

    // You can add additional logic here, such as checking for character death, playing sound effects, etc.
    if (IsDead()) {
        // Handle character death
        // For example, play death animation, trigger events, etc.
    }
}

void CombatCharacter::SetCurrentGridCell(int gridCellX, int gridCellY) {
    mCurrentGridCellX = gridCellX;
    mCurrentGridCellY = gridCellY;
}

void CombatCharacter::SetTargetGridCell(int gridCellX, int gridCellY) {
    mTargetGridCellX = gridCellX;
    mTargetGridCellY = gridCellY;
}

int CombatCharacter::GetCurrentGridCellX() {
    return mCurrentGridCellX;
}

int CombatCharacter::GetCurrentGridCellY() {
    return mCurrentGridCellY;
}

void CombatCharacter::PerformAction() {
    // Perform the character's action using mCurrentGridCellX, mCurrentGridCellY,
    // mTargetGridCellX, mTargetGridCellY, and other relevant information
    // Implement your combat logic here
}

void CombatCharacter::Render(int currentGridCellX, int currentGridCellY, float playerPositionX, float playerPositionY) {

    if (mCharacterTexture != nullptr) {
        float texturePositionX = mCurrentGridCellX * 1.0f + playerPositionX;
        float texturePositionY = mCurrentGridCellY * 1.0f + playerPositionY;

        printf("\n %f", texturePositionX);
        printf("\n %f", texturePositionY);

        mCharacterTexture->Pos(Vector2(texturePositionX, texturePositionY));
        mCharacterTexture->Render();
    }

  
}

void CombatCharacter::Update() {
    // Rendering logic for the combat character

}

