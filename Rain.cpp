#include "Rain.h"

bool Rain::sScroll = false;

void Rain::Scroll(bool b) {

	sScroll = b;
}

Rain::Rain(int layer, int randomv, int randomh)
	: Texture("raindrops.png", 0, 0, 2, 8)
{
	mTimer = Timer::Instance();

	int rainColor = rand() % 4;

	mClipRect.x = rainColor * 4;
	
	

	mRandomv = randomv; 
	mRandomh = randomh;


	
	


	//Range
	int range = ((Graphics::Instance()->SCREEN_WIDTH * 0.90) + (34.0f)) - ((Graphics::Instance()->SCREEN_WIDTH * 0.90) - (34.0f)) + 1;

	int width = ((Graphics::Instance()->SCREEN_WIDTH * 0.90) - (34.0f * randomh));

	int height = ((Graphics::Instance()->SCREEN_HEIGHT * 0.70) - (34.0f * randomv));

	//RainPos = rand() % range + width,  height;



	RainPos = Vector2(Vector2(rand() % range + width,  height));



	Pos(RainPos);

	mFlickerTimer = 0.0f;
	mFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f;

	float invLayer = 1.0f / layer;
	Scale(VEC2_ONE * invLayer);

	mScrollSpeed = 4.0f / layer;

	//mAnimationStartPos = Vector2(((Graphics::Instance()->SCREEN_WIDTH) * 0.90) - (34.0f * 2), (((Graphics::Instance()->SCREEN_HEIGHT) * 0.70) - (34.0f * 2)));

	mVisible = true;
}


Rain::~Rain() {

	mTimer = NULL;
}

int Rain::RandomHeight(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 3);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}



void Rain::ScrollRain() {
	Translate(VEC2_UP * mScrollSpeed, world);

	Vector2 pos = Pos(local); 

	int weight = RandomHeight();
	int stopv = mRandomv + weight;

	//Stopping Point
	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT * 0.70 - (34.0f * mRandomv)) {

		//Range
		int range = ((Graphics::Instance()->SCREEN_WIDTH * 0.90) + (34.0f)) - ((Graphics::Instance()->SCREEN_WIDTH * 0.90) - (34.0f)) + 1;

		//New Position after falling
		pos.y = Graphics::Instance()->SCREEN_HEIGHT * 0.70 - (34.0f * stopv);
		pos.x = rand() % range + ((Graphics::Instance()->SCREEN_WIDTH * 0.90) - (34.0f * mRandomh));

		//pos.x = rand() % Graphics::Instance()->SCREEN_WIDTH;
		Pos(pos);
	}
}

void Rain::Update() {


	mFlickerTimer += mTimer->DeltaTime();
	if (mFlickerTimer >= mFlickerSpeed) {

		mVisible = !mVisible;
		mFlickerTimer = 0.0f;
	}

	if (sScroll)
		ScrollRain();
}

void Rain::Render() {

	if (mVisible)
		Texture::Render();
}









