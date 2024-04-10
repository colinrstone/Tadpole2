#ifndef SewageMap_h
#define SewageMap_h

#include "GameEntity2.h"
#include "AnimatedTexture.h"
#include "Texture.h"

using namespace QuickSDL;


class SewageMap : public GameEntity {

private:

	//Power Facility Map
	int mSewageMap[26][17];


	//Texture for each type of power entity
	Texture* mSewage;

	Texture* mFilter;
	Texture* mWaterTreatmentPlant;


public:



private:



public:

	SewageMap();
	~SewageMap();


	void LoadSewageMap(int arr[26][17]);
	void DrawSewageMap();

	void Update();
	void Render();

};

#endif /* SewageMap_h */