#ifndef Textbox_h
#define Textbox_h

#include "Texture.h"
#include "InputManager.h"
#include "Timer.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "AssetManager.h"

using namespace QuickSDL;

class Textbox : public GameEntity {

private:
    Timer* mTimer;
    Texture* mBackground;
    Texture* mDialogueText;
    std::vector<Texture*> mDialogueTexts;
    std::vector<Texture*> mResponseTexts;
    std::vector<std::string> mParagraphs;
    int mMaxCharsPerLine;
    float mLineHeight;

    Texture* mArrow;
    float mArrowX;
    float mArrowY;

    int mSelectedResponseIndex;

    int mCurrentLine;
    float mInputCooldownTimer;
    float mInputCooldownInterval;
    bool mArrowHeld;
    float mInputDelayTimer;
    float mInputDelayInterval;

public:
    Textbox();
    ~Textbox();

    void SetBackground();
    void SetDialogueText(const std::vector<std::string>& dialogues, const std::string& fontPath, int fontSize, SDL_Color textColor);
    void SetResponseTexts(const std::vector<std::string>& responses, const std::string& fontPath, int fontSize, SDL_Color textColor);



    void SetParagraphs(const std::vector<std::string>& paragraphs);
    void NextParagraph();

    void DrawArrow(float arrowX, float arrowY);

    void HandleInput();
    void SetArrowPosition(float x, float y);
    void UpdateArrowPosition();

    void Update();
    void Render();
};

#endif /* Textbox_h */
