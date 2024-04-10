#include "Textbox.h"

Textbox::Textbox() : mArrowX(975.0f), mArrowY(750.0f), mSelectedResponseIndex(0), mCurrentLine(0), mMaxCharsPerLine(20), mLineHeight(50.0f) {
    mTimer = Timer::Instance();
    mBackground = nullptr;
    mDialogueText = nullptr;
    mResponseTexts.clear();
    mMaxCharsPerLine = 12;
    mArrow = new Texture("responsearrow.png");
    mArrow->Parent(this);
    mArrow->Pos(Vector2(mArrowX, mArrowY));
    mInputCooldownTimer = 0.0f;
    mInputCooldownInterval = 0.1f;
    mInputDelayTimer = 0.0f;
    mInputDelayInterval = 0.50f;
    mMaxCharsPerLine = 12;
    mLineHeight = 50.0f;      // Set your desired line spacing
}

Textbox::~Textbox() {
    delete mBackground;
    delete mArrow;
    for (Texture* responseText : mResponseTexts) {
        delete responseText;
    }
}

void Textbox::SetBackground() {
    delete mBackground;
    mBackground = new Texture("background.png");
    mBackground->Parent(this);
    mBackground->Pos(Vector2(950.0f, 850.0f));
}


void Textbox::SetDialogueText(const std::vector<std::string>& dialogues, const std::string& fontPath, int fontSize, SDL_Color textColor) {
    for (const std::string& text : dialogues) {
        Texture* paragraphTexture = new Texture(text, fontPath, fontSize, textColor);
        paragraphTexture->Parent(this);
        mDialogueTexts.push_back(paragraphTexture);
    }
}


void Textbox::SetResponseTexts(const std::vector<std::string>& responses, const std::string& fontPath, int fontSize, SDL_Color textColor) {
    for (Texture* responseText : mResponseTexts) {
        delete responseText;
    }
    mResponseTexts.clear();

    float x = 1150.0f;
    float y = 750.0f;
    for (const std::string& text : responses) {
        Texture* responseTexture = new Texture(text, fontPath, fontSize, textColor);
        responseTexture->Parent(this);
        responseTexture->Pos(Vector2(x, y));
        mResponseTexts.push_back(responseTexture);
        y += mLineHeight;
    }
}

void Textbox::SetArrowPosition(float x, float y) {
    mArrowX = x;
    mArrowY = y;
}

void Textbox::UpdateArrowPosition() {
    mArrow->Pos(Vector2(mArrowX, mArrowY));
}

void Textbox::HandleInput() {
    float lineHeight = mLineHeight;
    mInputCooldownTimer += mTimer->DeltaTime();
    mInputDelayTimer += mTimer->DeltaTime();

    if (InputManager::Instance()->KeyDown(SDL_SCANCODE_UP)) {
        if (mArrowHeld) {
            if (mInputCooldownTimer >= mInputCooldownInterval) {
                mInputCooldownTimer = 0.0f;
                if (mSelectedResponseIndex > 0) {
                    mSelectedResponseIndex--;
                    mArrowY -= lineHeight;
                    mCurrentLine--;
                }
            }
        }
        else {
            if (mInputDelayTimer >= mInputDelayInterval) {
                mArrowHeld = true;
                mInputCooldownTimer = 0.0f;
                if (mSelectedResponseIndex > 0) {
                    mSelectedResponseIndex--;
                    mArrowY -= lineHeight;
                    mCurrentLine--;
                }
            }
        }
    }
    else if (InputManager::Instance()->KeyDown(SDL_SCANCODE_DOWN)) {
        if (mArrowHeld) {
            if (mInputCooldownTimer >= mInputCooldownInterval) {
                mInputCooldownTimer = 0.0f;
                if (mSelectedResponseIndex < mResponseTexts.size() - 1) {
                    mSelectedResponseIndex++;
                    mArrowY += lineHeight;
                    mCurrentLine++;
                }
            }
        }
        else {
            if (mInputDelayTimer >= mInputDelayInterval) {
                mArrowHeld = true;
                mInputCooldownTimer = 0.0f;
                if (mSelectedResponseIndex < mResponseTexts.size() - 1) {
                    mSelectedResponseIndex++;
                    mArrowY += lineHeight;
                    mCurrentLine++;
                }
            }
        }
    }
    else {
        mArrowHeld = false;
        mInputCooldownTimer = 0.0f;
    }
}

void Textbox::Update() {
    UpdateArrowPosition();
    HandleInput();
}

void Textbox::Render() {
    if (mBackground) {
        mBackground->Render();
    }

    float currentY = 730.0f;
    for (Texture* dialogueText : mDialogueTexts) {
        dialogueText->Pos(Vector2(700.0f, currentY));
        dialogueText->Render();
        currentY += mLineHeight;
    }

    for (Texture* responseText : mResponseTexts) {
        responseText->Render();
    }

    if (mArrow) {
        mArrow->Render();
    }
}