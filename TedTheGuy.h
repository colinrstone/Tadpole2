#ifndef TedTheGuy_h
#define TedTheGuy_h

#include "Character.h"
#include "TriggerManager.h"
#include <unordered_map>

class TedTheGuy : public Character {

public:

    int mZoneIdentifier;
    int mCharacterValue;
    int mCurrentOrder;
    int mTextboxProgress;
    int mResponse;

    TriggerManager* mTriggerManager;
    

public:



    TedTheGuy();
    ~TedTheGuy();

    void SetTriggerManager(TriggerManager* triggerManager);
    int CheckResponse(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber);

    std::pair<int, int> TedSpecificFunction(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response);


};

#endif /* TedTheGuy_h */