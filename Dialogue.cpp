#include "Dialogue.h"

Dialogue::Dialogue() {

}

Dialogue::~Dialogue() {

}


bool Dialogue::LoadDialogueFromFile(const std::string& filename) {
    // Open the CSV file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << " (Error code: " << errno << ")" << std::endl;
        return false; // Failed to open file
    }

    // Read dialogues from the CSV file
    while (!file.eof()) {
        DialogueEntry entry;
        file >> entry.zone;
        file.ignore(); // Ignore the comma separator
        file >> entry.character;
        file.ignore(); // Ignore the comma separator
        file >> entry.order;
        file.ignore(); // Ignore the comma separator
        file >> entry.textbox;
        file.ignore(); // Ignore the comma separator
        std::getline(file, entry.text); 

        // Add the dialogue entry to the vector
        dialogues.push_back(entry);

    }

    // Close the file
    file.close();

    return true; // Dialogues loaded successfully
}

std::vector<std::string> Dialogue::GetCharacterDialogue(int zone, int character, int order, int textbox) {
    std::vector<std::string> result;

    // Search for dialogues with the specified criteria
    for (const auto& entry : dialogues) {
        if (entry.zone == zone && entry.character == character && entry.order == order && entry.textbox == textbox ) {

            result.push_back(entry.text);

        }
    }

    return result;
}


void Dialogue::Update() {

}

void Dialogue::Render() {

}
