#ifndef GameState_h
#define GameState_h

#include <vector>
#include <string>

class GameState {
public:
    int zone; // Current zone or area
    int playerHealth;
    int playerGold;
    // Add other relevant game state variables here

    // Constructor
    GameState(int initialZone, int initialHealth, int initialGold);
};

#endif /* GameState_h */
