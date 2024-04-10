#ifndef Dialogue_h
#define Dialogue_h

#include "GameEntity2.h"
#include "AnimatedTexture.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace QuickSDL;

class Dialogue : public GameEntity {

private:

	struct DialogueEntry {
		int zone;
		int character;
		int order;
		int textbox;

		std::string text;
	};

	std::vector<DialogueEntry> dialogues;

private:



public:

	Dialogue();
	~Dialogue();

	bool LoadDialogueFromFile(const std::string& filename);
	std::vector<std::string> GetCharacterDialogue(int zone, int character, int order, int textbox);

	void Update();
	void Render();


};

#endif /* Dialogue_h */
