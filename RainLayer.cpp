#include "RainLayer.h"

RainLayer::RainLayer(int layer, int randomv, int randomh) {


	for (int i = 0; i < RAIN_COUNT; i++)
		mRaindrops[i] = new Rain(layer, randomv, randomh);

}

RainLayer::~RainLayer() {


	for (int i = 0; i < RAIN_COUNT; i++) {

		delete mRaindrops[i];
		mRaindrops[i] = NULL;
	}
}

void RainLayer::Update() {

	for (int i = 0; i < RAIN_COUNT; i++)
		mRaindrops[i]->Update();
}

void RainLayer::Render() {

	for (int i = 0; i < RAIN_COUNT; i++)
		mRaindrops[i]->Render();

}
