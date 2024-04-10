#include "Grid.h"

Grid::Grid() {

    mGridCell = new Texture("gridcell.png");
    mGridCell->Parent(this);
    //mGridCell->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH / 2), (Graphics::Instance()->SCREEN_HEIGHT / 2)));
    mGridSize = NULL;
    mGridIsInitialized = false;
    
}

Grid::~Grid() {
    delete mGridCell;
    mGridCell = nullptr;
    mGridSize = NULL;
}

void Grid::InitializeGrid(Vector2 playerPosition, int gridSize, Party* party) {
    // Store the grid size as a member variable
    mGridSize = gridSize;

    mPlayerPositionX = playerPosition.x;
    mPlayerPositionY = playerPosition.y;
    mParty = party;


    // Clear the grid
    grid.clear();

    // Load the grid cell texture position
    //mGridCell->Pos(Vector2(0.0f, 0.0f));

    // Calculate the grid coordinates based on the player's position
    int playerGridX = static_cast<int>(playerPosition.x) / mGridSize;
    int playerGridY = static_cast<int>(playerPosition.y) / mGridSize;

    // Initialize the grid around the player
    for (int i = -mGridSize / 2; i <= mGridSize / 2; ++i) {

        std::vector<CombatCharacter*> row;

        for (int j = -mGridSize / 2; j <= mGridSize / 2; ++j) {

            // Create a placeholder combat character for each grid cell
            CombatCharacter* placeholderCombatCharacter = new CombatCharacter(/* Initialize with appropriate parameters */);
            row.push_back(placeholderCombatCharacter);

        }
        grid.push_back(row);
    }

    mGridIsInitialized = true;

}

bool Grid::CheckGridInitialization() {

    return mGridIsInitialized;

}


void Grid::SetPlayer(CombatCharacter* player) {
    // Set the player on the grid (assuming it's already initialized)
    // For example, you might want to set the player at the center of the grid
    int gridSizeX = grid.size();
    int gridSizeY = grid[0].size();

    int playerGridX = gridSizeX / 2;
    int playerGridY = gridSizeY / 2;

    grid[playerGridX][playerGridY] = player;
}

void Grid::SetEnemy(CombatCharacter* enemy) {
    // Set an enemy on the grid (assuming it's already initialized)
    // For example, you might want to set enemies randomly on the grid
    int gridSizeX = grid.size();
    int gridSizeY = grid[0].size();

    int enemyGridX = rand() % gridSizeX;
    int enemyGridY = rand() % gridSizeY;

    // Make sure the cell is not already occupied by another character
    while (grid[enemyGridX][enemyGridY] != nullptr) {
        enemyGridX = rand() % gridSizeX;
        enemyGridY = rand() % gridSizeY;
    }

    grid[enemyGridX][enemyGridY] = enemy;
}

int Grid::GetPlayerGridX() const {
    return static_cast<int>(mPlayerPositionX) / mGridSize;
}

int Grid::GetPlayerGridY() const {
    return static_cast<int>(mPlayerPositionY) / mGridSize;
}

void Grid::Render() {

    std::vector<Texture*> cellTextures;
    std::vector<Vector2> cellPositions;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            Texture* cellTexture = new Texture("gridcell.png");
            cellTextures.push_back(cellTexture);

            float cellX = i * 32.0f + mPlayerPositionX;
            float cellY = j * 32.0f + mPlayerPositionY;
            cellPositions.push_back(Vector2(cellX, cellY));
        }
    }

    // Render the initialized textures
    for (size_t i = 0; i < cellTextures.size(); ++i) {
        cellTextures[i]->Pos(cellPositions[i]);
        cellTextures[i]->Render();
        delete cellTextures[i]; // Cleanup
    }

    for (int i = 0; i < mParty->GetPartySize(); ++i) {
        CombatCharacter* character = mParty->GetPartyMember(i);

        int currentGridCellX = character->GetCurrentGridCellX();
        int currentGridCellY = character->GetCurrentGridCellY();

        if (character != nullptr) {
            if (currentGridCellX >= 0 && currentGridCellY >= 0) {
                character->Render(currentGridCellX, currentGridCellY, mPlayerPositionX, mPlayerPositionY);
            }
        }


    }

}