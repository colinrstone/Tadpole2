#include "Camera.h"

Camera::Camera() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mCameraPosition = Vector2((Graphics::Instance()->SCREEN_WIDTH  / 2 ), (Graphics::Instance()->SCREEN_HEIGHT  / 2 ));

}

Camera::~Camera() {

	
	mTimer = NULL;
	mInput = NULL;

	mCameraPosition = NULL;



}


void Camera::SetCameraPosition(float x, float y) {


	mCameraPosition.x = x;
	mCameraPosition.y = y;
}

void Camera::SetCameraPosition(Vector2& position) {

	mCameraPosition = position;
}


Vector2 Camera::GetPosition() const {

	return mCameraPosition;

}


Vector2 Camera::GetOffset() const {

	return -mCameraPosition;

}




void Camera::Update() {



}


void Camera::Render() {





}
