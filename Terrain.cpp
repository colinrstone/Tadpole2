#include "Terrain.h"
#include "Level.h"

Terrain::Terrain(int zoneIdentifier) {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mTerrain = NULL;


    // Load terrain texture based on the zone
    switch (zoneIdentifier) {
    case 1:
        mTerrainOne = new Texture("terraintwo.png");
        break;
    case 2:
        mTerrainOne = new Texture("terrainthree.png");
        break;
    case 3:
        mTerrainOne = new Texture("terrainone");
        break;
        // Add more cases for other zones if needed
    }


	//mTerrainOne = new Texture("terraintwo.png");
	mTerrainOne->Parent(this);
	//mTerrainOne->Scale(Vector2(2.0f, 2.0f));
	mTerrainOne->Pos(Vector2(VEC2_ZERO));

	mScrollSpeed = 200.0f;


}

Terrain::~Terrain() {

	mTimer = NULL;
	mInput = NULL;

	//delete mTerrain;
    mTerrain = NULL;

	delete mTerrainOne;
	mTerrainOne = NULL;


}

void Terrain::HandleTerrainShift() {
    Vector2 movement(0, 0); // Initialize a movement vector

    if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
        movement.x += 1;
    }
    if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
        movement.x -= 1;
    }
    if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
        movement.y -= 1;
    }
    if (mInput->KeyDown(SDL_SCANCODE_UP)) {
        movement.y += 1;
    }

    // Normalize the movement vector to ensure consistent speed in all directions
    if (movement.x != 0 || movement.y != 0) {
        movement.Normalized();
    }

    // Update the terrain's position based on the movement vector
    Translate(movement * mScrollSpeed * mTimer->DeltaTime());

    Vector2 pos = Pos(local);
    Pos(pos);
}


void Terrain::AddImpassableArea(const SDL_Rect& area) {
    mImpassableAreas.push_back(area);
}


void Terrain::UpdateImpassableArea(const SDL_Rect& oldArea, const SDL_Rect& newArea) {
    // Remove the old area and add the new one
    //RemoveImpassableArea(oldArea);
    AddImpassableArea(newArea);
}


void Terrain::Update() {

	HandleTerrainShift();

}


void Terrain::Render() {


	mTerrainOne->Render();


}
