#   include "TriggerManager.h"

TriggerManager::TriggerManager() {


}

TriggerManager::~TriggerManager() {
 


}

bool TriggerManager::IsTriggerActive(const std::string& triggerName) {
    return activeTriggers.find(triggerName) != activeTriggers.end();
}

void TriggerManager::ActivateTrigger(const std::string& triggerName) {
    activeTriggers.insert(triggerName);
}

void TriggerManager::DeactivateTrigger(const std::string& triggerName) {
    activeTriggers.erase(triggerName);
}

bool TriggerManager::IsCharacterTriggerActive(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response) {

    return true;
}

void TriggerManager::ActivateCharacterTrigger(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response) {


}

void TriggerManager::DeactivateCharacterTrigger(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response) {

}


void TriggerManager::AddTrigger(std::tuple<int, int, int, int> key, int response) {
    triggers.emplace_back(key, response);
}




int TriggerManager::GetPlayerResponse(std::tuple<int, int, int, int> key) {

    for (const auto& trigger : triggers) {

        if (std::get<0>(trigger) == key) {

            return std::get<1>(trigger);

        }
    }

    return 0;
}



std::vector<int> TriggerManager::GetPlayerResponses(std::tuple<int, int, int, int> key) {
    std::vector<int> matchingResponses;

    for (const auto& trigger : triggers) {
        if (std::get<0>(trigger) == key) {
            matchingResponses.push_back(std::get<1>(trigger));
        }
    }

    return matchingResponses;
}