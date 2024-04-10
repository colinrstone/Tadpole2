#ifndef ConversationState_h
#define ConversationState_h

#include <vector>
#include <string>

class ConversationState {
public:
    int zone; // Current zone or area for the conversation
    int characterValue; // Character value
    int progress; // Conversation progress
    std::vector<int> activeTriggers; // List of active triggers for this conversation

    // Constructor
    ConversationState(int initialZone, int characterValue);

    // Function to update active triggers
    void UpdateActiveTriggers(const std::vector<int>& newActiveTriggers);
};

#endif /* ConversationState_h */

