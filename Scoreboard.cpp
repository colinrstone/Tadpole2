#include "Scoreboard.h"
#include "GameEntity2.h"


Scoreboard::Scoreboard()
	: Scoreboard({ 72, 31, 228 })
{
	
}

Scoreboard::Scoreboard(SDL_Color color) {
	
	mColor = color;
	Score(0);
}

Scoreboard::~Scoreboard() {
	
	ClearBoard();
}

void Scoreboard::ClearBoard() {
	
	for(int i = 0; i < mScore.size(); i++) {
		delete mScore[i];
		mScore[i] = NULL;
	}
	
	mScore.clear();
}

void Scoreboard::Score(int score) {
	
	ClearBoard();
	
	if(score == 0) {
		
		for(int i = 0; i <1; i++) {
			
			mScore.push_back(new Texture("0", "unispace bold.ttf", 12, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f*i, 0.0f));
			
		}
	
	}
	else {

		std::string str = std::to_string(score);
		//int lastIndex = (int)str.length() - 2;

		for (int i = 0; i <= 0; i++) {
			mScore.push_back(new Texture(str.substr(i, score), "unispace bold.ttf", 12, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(0.0f, 0.0f));

		}
		
	}


	/*
	
	
	
	
	*/



	
}


void Scoreboard::Render() {
	for(int i = 0; i < mScore.size(); i++)
		mScore[i]->Render();
}

