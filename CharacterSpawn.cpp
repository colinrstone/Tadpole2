#include "CharacterSpawn.h"
#include "Character.h"
#include "Level.h"
#include "TedTheGuy.h"

std::vector<Character*> CharacterSpawn::mAllCharacters; // Initialize the static member variable

void CharacterSpawn::LoadCharactersForZone(Level* level, Level::ZONE zone) {
    // Clear any existing characters
    for (Character* character : mAllCharacters) {
        delete character;
    }
    mAllCharacters.clear();

    // Load characters for the specified zone
    switch (zone) {
    case Level::ZONE::OUTSIDE:
        // Fill in the constructor parameters for Character
        mAllCharacters.push_back(new Character(1));
        mAllCharacters.push_back(new TedTheGuy());

        break;

    case Level::ZONE::BUILDING_ONE:
        // Fill in the constructor parameters for Character
        mAllCharacters.push_back(new Character(2));
        // mAllCharacters.push_back(new Character(/* parameters for character 2 in Zone 2 */));
        break;

    default:
        // Handle unknown zones or load a default set of characters
        break;
    }

    // Assign these characters to the level
    level->SetCharacters(mAllCharacters);
}

CharacterSpawn::CharacterSpawn() {

	//mTimer = Timer::Instance();
	//Input = InputManager::Instance();

	mCharacter = NULL;


}

CharacterSpawn::~CharacterSpawn() {


}


void CharacterSpawn::Update() {

    //for (Character* enemy : mAllCharacters) {

    //    enemy->Update();

    //}


}

void CharacterSpawn::Render() {

    //for (Character* enemy : mAllCharacters) {

    //    enemy->Render();

   // }

}
