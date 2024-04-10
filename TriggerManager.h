#ifndef TriggerManager_h
#define TriggerManager_h

#include <vector>
#include <tuple>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>

class Character;
class Player;
class EventManager;

class Trigger {
public:
    std::string name;
    std::vector<std::string> conditions;
    std::vector<std::string> events;
};

class TriggerManager {

public:

    enum ZONE { OUTSIDE, BUILDING_ONE, BUILDING_TWO };

    TriggerManager();
    ~TriggerManager();

    bool IsTriggerActive(const std::string& triggerName);
    void ActivateTrigger(const std::string& triggerName);
    void DeactivateTrigger(const std::string& triggerName);

    bool IsCharacterTriggerActive(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response);
    void ActivateCharacterTrigger(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response);
    void DeactivateCharacterTrigger(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response);

    std::unordered_map<int, int, int, int> GetCharacterTriggers() const;


    void AddTrigger(std::tuple<int, int, int, int> key, int response);
    int GetPlayerResponse(std::tuple<int, int, int, int> key);
    std::vector<int> GetPlayerResponses(std::tuple<int, int, int, int> key);


private:
    //std::vector<std::array<int, 5>> triggers;
    std::vector<std::tuple<std::tuple<int, int, int, int>, int>> triggers;
    std::unordered_set<std::string> activeTriggers;
    //std::unordered_set<int, int, int, int, int> mCharacterTriggers;

};
#endif /* TriggerManager_h */