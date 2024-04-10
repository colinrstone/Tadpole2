#include "PlayLevel.h"






PlayLevel::PlayLevel(int tilemap[26][17]) {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	

	//int mMap[26][17] = tilemap[26][17];
	mType = NULL;


	mDirt = new Texture("dirt.png");
	mDirt->Parent(this);

	mGrass = new Texture("grass.png");
	mGrass->Parent(this);

	mWater = new Texture("water.png");
	mWater->Parent(this);

	mVerticalStreet = new Texture("verticalstreet.png");
	mVerticalStreet->Parent(this);

	mHorizontalStreet = new Texture("horizontalstreet.png");
	mHorizontalStreet->Parent(this);

	mIntersectionStreet = new Texture("intersectionstreet.png");
	mIntersectionStreet->Parent(this);



	mGrassOne = new AnimatedTexture("grassone.png", 0, 0, 32, 32, 2, 0.75f, AnimatedTexture::horizontal);
	mGrassOne->Parent(this);

	//Tile Texture
	mTile = NULL;
	//mTile->Parent(this);

	mAnimatedTile = NULL;

	//Tile Type
	mTileValue = NULL;


	//Tile Name dunno if this is needed
	//mTileName = EMPTY;

	mPassable = false;
	mStatus = NULL;
	mPlayerOccupy = NULL;
	mUnitOccupy = NULL;
	mEnemyOccupy = NULL;

	mAdjacent = false;

	mMinimapVector = NULL;

	LoadMap(tilemap);

}


PlayLevel::~PlayLevel() {

	mTimer = NULL;
	mInput = NULL;

	int mMap = NULL;
	int mType = NULL;

	mStatus = NULL;
	mPlayerOccupy = NULL;
	mUnitOccupy = NULL;
	mEnemyOccupy = NULL;

	mDirt = NULL;
	mWater = NULL;
	mGrass = NULL;
	mHorizontalStreet = NULL;
	mVerticalStreet = NULL;
	mIntersectionStreet = NULL;
}

void PlayLevel::LoadMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mMap[row][column] = arr[row][column];
		}
	}

}

void PlayLevel::DrawMap() {

	//int mType = 0;


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{

			int mType = mMap[row][column];

			//how to position the tiles in the loop take 2

			//int height = row * 32;
			//int width = column * 32;

			//mTile->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.04, Graphics::Instance()->SCREEN_HEIGHT * 0.04));

			//mTilePos.x = Graphics::Instance()->SCREEN_WIDTH * 0.0f;
			//mTilePos.y = Graphics::Instance()->SCREEN_HEIGHT * 0.0f;

			//Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.85f, Graphics::Instance()->SCREEN_HEIGHT * 0.05f));

			switch (mType)
			{
			case 0:
				mTile = mWater;
				mTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mTile->Render();
				break;
			case 1:
				mTile = mDirt;
				mTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mTile->Render();
				break;
			case 2:
				mAnimatedTile = mGrassOne;
				mAnimatedTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mAnimatedTile->Render();
				break;
			case 3:
				mTile = mVerticalStreet;
				mTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mTile->Render();
				break;
			case 4:
				mTile = mHorizontalStreet;
				mTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mTile->Render();
				break;
			case 5:
				mTile = mIntersectionStreet;
				mTile->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mTile->Render();
				break;
			default:
				break;
			}

		}
	}
	
}




void PlayLevel::Update() {

	LoadMap(mMap);
	mAnimatedTile->Update();

}

void PlayLevel::Render() {


	DrawMap();


}