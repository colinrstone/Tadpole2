#include "PowerMap.h"


PowerMap::PowerMap() {


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mPowerMap[row][column] = NULL;
		}
	}

	mPower = NULL;

	mGenerator = NULL;

}


PowerMap::~PowerMap() {


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mPowerMap[row][column] = NULL;
		}
	}

	mPower = NULL;

	mGenerator = NULL;

}



void PowerMap::LoadPowerMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mPowerMap[row][column] = arr[row][column];
		}
	}

}

void PowerMap::DrawPowerMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Power Type Value
			int powerTypeValue = mPowerMap[row][column];


			switch (powerTypeValue)
			{
			case 0:

				mPower = NULL;
				break;

			case 1:

				mPower = mGenerator;
				mPower->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mPower->Render();
				break;



			default:
				break;
			}











		}
	}
}


void PowerMap::Update() {



	LoadPowerMap(mPowerMap);



}

void PowerMap::Render() {



	DrawPowerMap();


}
