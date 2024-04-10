#include "EventManager.h"

EventManager::EventManager() {
    // Initialize any event-related variables here
}

EventManager::~EventManager() {
    // Clean up event-related resources here
}

void EventManager::RegisterEvent(const std::string& eventName, EventCallback callback) {
    // Register an event with its associated callback function
    eventCallbacks[eventName] = callback;
}

void EventManager::UnregisterEvent(const std::string& eventName) {
    // Unregister an event
    eventCallbacks.erase(eventName);
}
/*
void EventManager::ProcessEvents(GameState gameState) {
    // Process events based on the current game state
    for (const auto& eventName : eventsToProcess) {
        auto it = eventCallbacks.find(eventName);
        if (it != eventCallbacks.end()) {
            EventCallback callback = it->second;
            callback(gameState); // Pass the game state to the event callback
        }
    }
    eventsToProcess.clear();
}
*/
void EventManager::ClearAllEvents() {
    // Clear all registered events
    eventCallbacks.clear();
}