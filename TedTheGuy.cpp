#include "TedTheGuy.h"

TedTheGuy::TedTheGuy() : Character(1) {
    // Call the base class (Character) constructor with character number 1
    // Initialize TedTheGuy-specific properties here

}
TedTheGuy::~TedTheGuy() {
    // Destructor implementation, if needed
}

void TedTheGuy::SetTriggerManager(TriggerManager* triggerManager) {
    mTriggerManager = triggerManager;
}

int TedTheGuy::CheckResponse(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber) {
    //THIS FUNCTION CAN BE SPECIFIED TO INTERCHANGE ORDER AND TEXTBOX NUMBER AS NEEDED FOR THE INDIVIDUAL CHARACTERS NEEDS


    //Use the trigger manager to the get the player's response
    std::tuple<int, int, int, int> key(zoneIdentifier, characterNumber, characterOrder, textboxNumber);


    //Get what the player responded to earlier if there is active triggers
    //int response = mTriggerManager->GetPlayerResponse(key); //might need to be made to sort multiple keys
    std::vector<int> responses = mTriggerManager->GetPlayerResponses(key);


    // Handle the response or perform additional logic.

    // If there are no responses, return 0
    if (responses.empty()) {
        return 0;
    }

    // Find the response with the greatest magnitude
    int greatestMagnitude = responses[0];
    for (int response : responses) {
        if (std::abs(response) > std::abs(greatestMagnitude)) {
            greatestMagnitude = response;
        }
    }

    return greatestMagnitude;
}


std::pair<int, int> TedTheGuy::TedSpecificFunction(int zoneIdentifier, int characterNumber, int characterOrder, int textboxNumber, int response) {
    // Implement TedTheGuy-specific functionality here
    mZoneIdentifier = zoneIdentifier;
    mCharacterValue = characterNumber;
    mCurrentOrder = characterOrder; //This will default as 1 and be changed as necessary on each conversation iteration
    mTextboxProgress = textboxNumber; //Increases after each textbox in a given order until it reaches maxtextbox
    mResponse = response; //Default to 0 on nonresponse textboxes and top row and increase if the player goes down a response item
    
   // printf("asd");
    std::pair<int, int> asd;

    int key = CheckResponse(mZoneIdentifier, mCharacterValue, mCurrentOrder, mTextboxProgress);
    printf("%i \n", mResponse);

    if (key)
      mResponse = key;


    printf("%i \n", mZoneIdentifier);
    printf("%i \n", mCharacterValue);
    printf("%i \n", mCurrentOrder);
    printf("%i \n", mTextboxProgress);



    if (mZoneIdentifier == 1 && mCharacterValue == 1 && mCurrentOrder == 1 && mTextboxProgress == 1 && mResponse == 1) {

        printf("asd");
        //Change dialogue order to 2 and set it to the number of entries in the csv file which is 5
        asd.first = 2;
        asd.second = 5;

    }


    if (mZoneIdentifier == 1 && mCharacterValue == 1 && mCurrentOrder == 2 && mTextboxProgress == 1 && mResponse == 1) {

        printf("asd");
        //Change dialogue order to 2 and set it to the number of entries in the csv file which is 5
        asd.first = 2;
        asd.second = 5;

    }


    int asdone = asd.first;
    int asdtwo = asd.second;
    //printf("%i \n", asdone);
    //printf("%i \n", asdtwo);

    return asd;

}