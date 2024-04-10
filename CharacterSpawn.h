#ifndef CharacterSpawn_h
#define CharacterSpawn_h

#include "GameEntity2.h"
#include "InputManager.h"
#include "AnimatedTexture.h"

#include <vector>
#include "Character.h"
#include "Level.h"


using namespace QuickSDL;

// Forward declarations 

class Character; 

//class Level; 

//

class CharacterSpawn {

private:


	//* mTimer;
	//InputManager* mInput;

	//Contains Character and Where they go and when they spawn
	Character* mCharacter;

	//Vector of pointers to all enemies
	static std::vector<Character*> mAllCharacters;


private:



public:

	CharacterSpawn();
	~CharacterSpawn();

	void LoadCharactersForZone(Level* level, Level::ZONE zone);

	void Update();
	void Render();


};





#endif /* CharacterSpawn_h */
