#include "Response.h"
#include <iostream>
#include <fstream>
#include <sstream>

Response::Response() {

}

Response::~Response() {

}

bool Response::LoadResponsesFromFile(const std::string& fileName) {
    // Open the CSV file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << " (Error code: " << errno << ")" << std::endl;
        return false; // Failed to open file
    }

    // Read responses from the CSV file
    while (!file.eof()) {
        ResponseEntry entry;
        file >> entry.zone;
        file.ignore(); // Ignore the comma separator
        file >> entry.character;
        file.ignore(); // Ignore the comma separator
        file >> entry.order;
        file.ignore(); // Ignore the comma separator
        file >> entry.textbox;
        file.ignore(); // Ignore the comma separator
        std::string response;
        std::getline(file, response);

        // Split the response string into individual response options
        std::istringstream responseStream(response);
        std::string option;
        while (std::getline(responseStream, option, ',')) {
            entry.responses.push_back(option);
        }

        // Add the response entry to the vector
        responseEntries.push_back(entry);
    }

    // Close the file
    file.close();

    return true; // Responses loaded successfully
}

std::vector<std::string> Response::GetCharacterResponses(int zone, int character, int order, int textbox) {
    for (const ResponseEntry& entry : responseEntries) {
        if (entry.zone == zone && entry.character == character && entry.order == order && entry.textbox == textbox) {
            return entry.responses;
        }
    }


    // Return an empty vector if no matching responses are found
    return {};
}