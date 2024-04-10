#include "SewageMap.h"


SewageMap::SewageMap() {


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mSewageMap[row][column] = NULL;
		}
	}



}


SewageMap::~SewageMap() {


	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mSewageMap[row][column] = NULL;
		}
	}



}



void SewageMap::LoadSewageMap(int arr[26][17]) {

	for (int row = 0; row < 25; row++)
	{
		for (int column = 0; column < 16; column++)
		{
			mSewageMap[row][column] = arr[row][column];
		}
	}

}

void SewageMap::DrawSewageMap() {



	for (int row = 0; row < 25; row++)
	{

		for (int column = 0; column < 16; column++)
		{


			//Sewage Type Value
			int sewageTypeValue = mSewageMap[row][column];


			switch (sewageTypeValue)
			{
			case 0:

				mSewage = NULL;
				break;

			case 1:

				mSewage = mFilter;
				mSewage->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mSewage->Render();
				break;



			case 69:

				mSewage = mWaterTreatmentPlant;
				mSewage->Pos(Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * row), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * column))));
				mSewage->Render();
				break;

			default:
				break;
			}











		}
	}
}




void SewageMap::Update() {



	LoadSewageMap(mSewageMap);



}

void SewageMap::Render() {



	DrawSewageMap();


}
