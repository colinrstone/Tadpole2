// CombatState.cpp
#include "CombatState.h"

CombatState::CombatState() {
    // Initialization logic
}

CombatState::~CombatState() {
    // Cleanup logic
}

CombatTurn CombatState::GetCurrentTurn() const {
    return mCurrentTurn;
}

void CombatState::SetCurrentTurn(CombatTurn turn) {
    mCurrentTurn = turn;
}