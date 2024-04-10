#include "RainEffect.h"


RainEffect* RainEffect::sInstance = NULL;

RainEffect* RainEffect::Instance(int randomv, int randomh) {


	//if (sInstance == NULL)
		sInstance = new RainEffect(randomv, randomh);

	return sInstance;
}


void RainEffect::Release() {

	delete sInstance;
	sInstance = NULL;
}



RainEffect::RainEffect(int randomv, int randomh) {


	for (int i = 0; i < LAYER_COUNT; i++)
		mLayers[i] = new RainLayer(i,randomv, randomh);


}

RainEffect::~RainEffect() {

	for (int i = 0; i < LAYER_COUNT; i++) {

		delete mLayers[i];
		mLayers[i] = NULL;
	}

}



void RainEffect::Scroll(bool b) {

	Rain::Scroll(b);

}


void RainEffect::Update() {

	for (int i = 0; i < LAYER_COUNT; i++)
		mLayers[i]->Update();

}

void RainEffect::Render() {

	for (int i = 0; i < LAYER_COUNT; i++)
		mLayers[i]->Render();

}
