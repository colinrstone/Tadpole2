#include "ConversationState.h"

// Constructor implementation
ConversationState::ConversationState(int initialZone, int characterValue) :
    zone(initialZone),
    characterValue(characterValue),
    progress(0) {
    // Initialize other conversation state variables 
    //needs order number
}

// Function to update active triggers
void ConversationState::UpdateActiveTriggers(const std::vector<int>& newActiveTriggers) {
    activeTriggers = newActiveTriggers;
}