#include "SideBar.h"


SideBar::SideBar() {


	//mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBottomBackground = new Texture("background.png");
	mBottomBackground->Parent(this);
	mBottomBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.0f, Graphics::Instance()->SCREEN_HEIGHT * 0.90));
	mBottomBackground->Scale(Vector2(20.0f, 1.0f));


	mTopBackground = new Texture("topbackground.png");
	mTopBackground->Parent(this);
	mTopBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.0f, -22.0f));
	mTopBackground->Scale(Vector2(20.0f, 2.0f));

}

SideBar::~SideBar() {

	//mTimer = NULL;
	mAudio = NULL;

	delete mBottomBackground;
	mBottomBackground = NULL;

	delete mTopBackground;
	mTopBackground = NULL;

}


void SideBar::Update() {

}

void SideBar::Render() {

	mBottomBackground->Render();
	mTopBackground->Render();

}
