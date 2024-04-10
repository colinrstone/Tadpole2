#ifndef EventManager_h
#define EventManager_h

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using EventCallback = std::function<void()>;

class Event {
public:
    std::string name;
    std::vector<std::string> actions;
};

class EventManager {
public:
    EventManager();
    ~EventManager();

    void RegisterEvent(const std::string& eventName, EventCallback callback);
    void UnregisterEvent(const std::string& eventName);
    //void ProcessEvents(GameState gameState);
    void ClearAllEvents();

private:
    //std::unordered_map<std::string, Event> events;
    //std::unordered_map<std::string, Trigger> triggers;

    std::unordered_map<std::string, EventCallback> eventCallbacks;
};
#endif /* EventManager_h */