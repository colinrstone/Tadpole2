// CombatManager.cpp
#include "CombatManager.h"

CombatManager::CombatManager(Party* party) {
    // Initialization logic

    mCombatState.SetCurrentTurn(CombatTurn::PLAYER);
	mParty = party;

	//Party party;

	/*
	mCombatMenuBackground = new Texture("combatmenubackground.png");
	mCombatMenuBackground->Pos(Vector2(735, 740));
	mCombatMenuBackground->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuBackgroundHighlight = new Texture("combatmenubackgroundhighlight.png");
	mCombatMenuBackgroundHighlight->Pos(Vector2(735, 740));
	mCombatMenuBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuBackgroundSelect = new Texture("combatmenubackgroundselect.png");
	mCombatMenuBackgroundSelect->Pos(Vector2(735, 740));
	mCombatMenuBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//MOVEMENT
	mCombatMenuMovementBackground = new Texture("combatmenubackground.png");
	mCombatMenuMovementBackground->Pos(Vector2(735, 740));
	mCombatMenuMovementBackground->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuMovementBackgroundHighlight = new Texture("combatmenubackgroundhighlight.png");
	mCombatMenuMovementBackgroundHighlight->Pos(Vector2(735, 740));
	mCombatMenuMovementBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuMovementBackgroundSelect = new Texture("combatmenubackgroundselect.png");
	mCombatMenuMovementBackgroundSelect->Pos(Vector2(735, 740));
	mCombatMenuMovementBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//ACTION
	mCombatMenuActionBackground = new Texture("combatmenubackground.png");
	mCombatMenuActionBackground->Pos(Vector2(735, 780));
	mCombatMenuActionBackground->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuActionBackgroundHighlight = new Texture("combatmenubackgroundhighlight.png");
	mCombatMenuActionBackgroundHighlight->Pos(Vector2(735, 780));
	mCombatMenuActionBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuActionBackgroundSelect = new Texture("combatmenubackgroundselect.png");
	mCombatMenuActionBackgroundSelect->Pos(Vector2(735, 780));
	mCombatMenuActionBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//ITEM
	mCombatMenuItemBackground = new Texture("combatmenubackground.png");
	mCombatMenuItemBackground->Pos(Vector2(735, 820));
	mCombatMenuItemBackground->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuItemBackgroundHighlight = new Texture("combatmenubackgroundhighlight.png");
	mCombatMenuItemBackgroundHighlight->Pos(Vector2(735, 820));
	mCombatMenuItemBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuItemBackgroundSelect = new Texture("combatmenubackgroundselect.png");
	mCombatMenuItemBackgroundSelect->Pos(Vector2(735, 820));
	mCombatMenuItemBackgroundSelect->Scale(Vector2(2.0f, 0.5f));

	//STATUS
	mCombatMenuStatusBackground = new Texture("combatmenubackground.png");
	mCombatMenuStatusBackground->Pos(Vector2(735, 860));
	mCombatMenuStatusBackground->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuStatusBackgroundHighlight = new Texture("combatmenubackgroundhighlight.png");
	mCombatMenuStatusBackgroundHighlight->Pos(Vector2(735, 860));
	mCombatMenuStatusBackgroundHighlight->Scale(Vector2(2.0f, 0.5f));

	mCombatMenuStatusBackgroundSelect = new Texture("combatmenubackgroundselect.png");
	mCombatMenuStatusBackgroundSelect->Pos(Vector2(735, 860));
	mCombatMenuStatusBackgroundSelect->Scale(Vector2(2.0f, 0.5f));
	*/
}

CombatManager::~CombatManager() {

	/*
	delete mCombatMenuBackground;
	delete mCombatMenuBackgroundHighlight;
	delete mCombatMenuBackgroundSelect;

	// Cleanup movement textures
	delete mCombatMenuMovementBackground;
	delete mCombatMenuMovementBackgroundHighlight;
	delete mCombatMenuMovementBackgroundSelect;

	// Cleanup action textures
	delete mCombatMenuActionBackground;
	delete mCombatMenuActionBackgroundHighlight;
	delete mCombatMenuActionBackgroundSelect;

	// Cleanup item textures
	delete mCombatMenuItemBackground;
	delete mCombatMenuItemBackgroundHighlight;
	delete mCombatMenuItemBackgroundSelect;

	// Cleanup status textures
	delete mCombatMenuStatusBackground;
	delete mCombatMenuStatusBackgroundHighlight;
	delete mCombatMenuStatusBackgroundSelect;
	*/

	 
}

void CombatManager::StartCombat(Vector2 playerPosition, int gridSize) {

	CombatCharacter* guyface = new CombatCharacter();
	CombatCharacter* guyerface = new CombatCharacter();


	mParty->AddPartyMember(guyface);
	mParty->AddPartyMember(guyerface);


    mGrid.InitializeGrid(playerPosition, gridSize, mParty);
    // Logic to initialize combat





	// Set initial grid cells for party members
	for (int i = 0; i < mParty->GetPartySize(); ++i) {
		// Assuming you want to position party members around the player for simplicity
		int partyMemberGridX = mGrid.GetPlayerGridX() + i;
		int partyMemberGridY = mGrid.GetPlayerGridY();

		int size = mParty->GetPartySize();
		//printf("%i \n", size);

		//printf("\n %i", partyMemberGridX);
		//printf("\n %i", partyMemberGridY);
		

		mParty->GetPartyMember(i)->SetCurrentGridCell(partyMemberGridX, partyMemberGridY);
	}


	


   
    mPlayer.ResetHealth();
    mEnemy.ResetHealth();
}

void CombatManager::EndCombat() {
    // Logic to end combat
}

void CombatManager::Update() {
    // Update logic for combat
    // For simplicity, let's alternate turns between player and enemy
    if (mCombatState.GetCurrentTurn() == CombatTurn::PLAYER) {
        mPlayer.TakeTurn(mEnemy);

        printf("turn1");

        mCombatState.SetCurrentTurn(CombatTurn::ENEMY);
    }
    else {

        mEnemy.TakeTurn(mPlayer);

        printf("turn2");

        mCombatState.SetCurrentTurn(CombatTurn::PLAYER);
    }

    // Check for win/loss conditions
    if (mPlayer.IsDead() || mEnemy.IsDead()) {
        EndCombat();
    }
}

void CombatManager::Render() {
    // Render logic for combat
    // Include rendering of characters, grid, UI, etc.

	if (mGrid.CheckGridInitialization()) {
		mGrid.Render();
	}



}