#pragma once

#include <string>
#include <vector>

class Response {
public:
    struct ResponseEntry {
        int zone;
        int character;
        int order;
        int textbox;

        std::vector<std::string> responses;
    };

    Response();
    ~Response();

    bool LoadResponsesFromFile(const std::string& fileName);
    std::vector<std::string> GetCharacterResponses(int zone, int character, int order, int textbox);


private:
    std::vector<ResponseEntry> responseEntries;
};