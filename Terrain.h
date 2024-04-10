#ifndef Terrain_h
#define Terrain_h
#include "Texture.h"
#include "AnimatedTexture.h"
#include "InputManager.h"

#include "vector"


using namespace QuickSDL;

class Terrain : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;

	Texture* mTerrain;
	Texture* mTerrainOne;

	float mScrollSpeed;
	std::vector<SDL_Rect> mImpassableAreas;

private:


	

public:

	Terrain(int zoneIdentifier);
	//const std::string& backgroundImage, const std::vector<SDL_Rect>& initialImpassableAreas

	~Terrain();

	void HandleTerrainShift();

	void AddImpassableArea(const SDL_Rect& area);
	void RemoveImpassableArea(const SDL_Rect& area);
	void UpdateImpassableArea(const SDL_Rect& oldArea, const SDL_Rect& newArea);
	const std::vector<SDL_Rect>& GetImpassableAreas() const;



	void Update();
	void Render();


};






#endif /* Terrain_h */
