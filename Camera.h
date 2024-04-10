#ifndef Camera_h
#define Camera_h
#include "Texture.h"
#include "AnimatedTexture.h"
#include "InputManager.h"






using namespace QuickSDL;

class Camera : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;

	Vector2 mCameraPosition;



private:




public:

	Camera();

	~Camera();

	void SetCameraPosition(float x, float y);
	void SetCameraPosition(Vector2& position);

	Vector2 GetPosition() const;
	Vector2 GetOffset() const;

	void Update();
	void Render();


};






#endif /* Camera_h */
