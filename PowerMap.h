#ifndef PowerMap_h
#define PowerMap_h

#include "GameEntity2.h"
#include "AnimatedTexture.h"
#include "Texture.h"

using namespace QuickSDL;


class PowerMap : public GameEntity {

private:

	//Power Facility Map
	int mPowerMap[26][17];


	//Texture for each type of power entity
	Texture* mPower;
	Texture* mGenerator;



public:



private:



public:


	PowerMap();
	~PowerMap();


	void LoadPowerMap(int arr[26][17]);
	void DrawPowerMap();

	void Update();
	void Render();


};

#endif /* PowerMap_h */