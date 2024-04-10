#include "ConversationBoard.h"
#include <iostream>

ConversationBoard::ConversationBoard() {
    zone = 0;
    order = 0;
    textbox = 0;
    responseID = 0;
}

void ConversationBoard::SetContext(int zone, int order, int textbox, int responseID) {
    this->zone = zone;
    this->order = order;
    this->textbox = textbox;
    this->responseID = responseID;
}

void ConversationBoard::Display() {
    // Display the conversation options
    std::cout << "Options:" << std::endl;
    // Get the response options based on the current context
    std::vector<std::string> responseOptions = response.GetCharacterResponses(zone, order, textbox, responseID);

    int index = 1;
    for (const std::string& option : responseOptions) {
        std::cout << index << ". " << option << std::endl;
        index++;
    }
}

void ConversationBoard::SelectOption(int optionIndex) {
    // Get the options based on the current context
    std::vector<std::string> responseOptions = response.GetCharacterResponses(zone, order, textbox, responseID);

    // Check if the selected index is within the responseOptions vector bounds
    if (optionIndex < responseOptions.size()) {
        std::string selectedOption = responseOptions[optionIndex];
        // Handle the selected option here
        // For example, you can trigger an event based on the selectedOption
        // selectedEvent.TriggerEvent(selectedOption);
    }
}